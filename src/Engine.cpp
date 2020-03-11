/**
 * Name: Engine.cpp
 * Description: Implements a class representing a Neon rendering engine
 * Created on: 26.07.2019
 * Last modified: 11.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include "Engine.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>

#include "log/Logger.hpp"
#include "utility/FileUtils.hpp"
#include "Texture.hpp"
#include "Timer.hpp"

namespace neon
{

const int Engine::DEFAULT_WINDOW_WIDTH = 800;
const int Engine::DEFAULT_WINDOW_HEIGHT = 600;
const Uint32 Engine::DEFAULT_WINDOW_FLAGS = SDL_WINDOW_SHOWN;

Engine::Engine()
: pathAssets_(std::string())
, window_(nullptr)
, windowWidth_(0)
, windowHeight_(0)
, renderer_(nullptr)
, screenSurface_(nullptr)
, clBackgroundFill_(SDL_Color{0, 0, 0, 255})
{
}

Engine::~Engine()
{
  close();
}

bool Engine::init(const std::string& title, int posX, int posY, int width, int height, Uint32 flags)
{
  LOG(log::VERBOSE) << "Trying to locate assets' path...";
  bool result = ::neon::utility::getAssetsPath(pathAssets_);
  if (result) {
    LOG(log::INFO) << "Assets path: " << pathAssets_;
  }
  else {
    LOG(log::ERROR) << "Could not locate assets path.\n";
    return false;
  }

  LOG(log::VERBOSE) << "Initializing the SDL2 library -> SDL_Init()";
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    LOG(log::ERROR) << "Failed to initialize the SDL system.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  LOG(log::VERBOSE) << "Setting SDL hint for linear texture filtering";
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    LOG(log::WARNING) << "Could not enable linear texture filtering.";
  }

  LOG(log::VERBOSE) << "Creating the game window";
  window_ = SDL_CreateWindow(title.c_str(), posX, posY, width, height, flags);
  if (window_ == nullptr)
  {
    LOG(log::ERROR) << "Failed to create the game window.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }
  windowWidth_ = width;
  windowHeight_ = height;

  Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  LOG(log::VERBOSE) << "Creating a renderer for the game window";
  renderer_ = SDL_CreateRenderer(window_, -1, rendererFlags);
  if (renderer_ == nullptr)
  {
    LOG(log::ERROR) << "Failed to create a vsynced renderer.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }
  LOG(log::VERBOSE) << "Created a vsynced window renderer: " << renderer_;

  LOG(log::VERBOSE) << "Initializing the IMG submodule";
  int imgFlags = IMG_INIT_PNG;
  if (!IMG_Init(imgFlags))
  {
    LOG(log::ERROR) << "Failed to initialize SDL_image module.";
    LOG(log::ERROR) << "SDL_image error: " << IMG_GetError();
    return false;
  }

  LOG(log::VERBOSE) << "Initializing the TTF submodule";
  if (TTF_Init() == -1)
  {
    LOG(log::ERROR) << "Failed to initialize SDL_ttf module.";
    LOG(log::ERROR) << "SDL_ttf error: " << TTF_GetError();
    return false;
  }

  screenSurface_ = SDL_GetWindowSurface(window_);
  if (screenSurface_ == nullptr)
  {
    LOG(log::ERROR) << "Failed to obtain a screen surface from the game window.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  return true;
}

void Engine::startMainLoop()
{
  auto millisecondsPerFrame = 1000.0 / 60.0;
  unsigned long long currentFrame = 0ULL;

  LOG(log::VERBOSE) << "Initializing main loop at " << millisecondsPerFrame << " milliseconds per frame";

  Texture neonTexture;
  std::string path = pathAssets_ + "neon_logo.png";
  if (!neonTexture.loadFromFile(path, renderer_))
  {
    LOG(log::ERROR) << "Failed to load the resource [" << path << "]";
    return;
  }
  LOG(log::DEBUG) << "Texture [" << path << "] loaded correctly, size: "
      << neonTexture.width() << " x " << neonTexture.height();

  bool isQuittingMainLoop = false;
  SDL_Event sdlEvent;

  Timer tRealtime;
  Timer tFpsCap; // will be restarted on every game loop iteration.

  tRealtime.start();

  while (!isQuittingMainLoop)
  {
    tFpsCap.start();

    // Processes the incoming events:
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
      if (sdlEvent.type == SDL_QUIT)
      {
        isQuittingMainLoop = true;
      }
    }

    // Applies game logic:
    auto timeNow = tRealtime.time();

    Uint8 blue = std::abs(std::fmod(timeNow, 2.0) - 1.0) * 256;
    this->setBackgroundFillColor({0, 0, blue, 255});

    // Renders the scene:
    SDL_SetRenderDrawColor(
        renderer_,
        clBackgroundFill_.r,
        clBackgroundFill_.g,
        clBackgroundFill_.b,
        clBackgroundFill_.a
    );
    // @TODO define the scene color as set/get-able class member variable.
    // @TODO maybe define a lightweight wrapper on SDL_Color struct?

    SDL_RenderClear(renderer_);

    // @TODO: write code that actually renders the scene.
    auto x = 0.5 * (windowWidth_ - neonTexture.width());
    auto y = 0.5 * (windowHeight_ - neonTexture.height());
    neonTexture.render(x, y);

    SDL_RenderPresent(renderer_);

    currentFrame += 1ULL;
    // Caps the frame rate at target FPS value:
    double frameDurationMilliseconds = tFpsCap.time() * 1000;
    if (frameDurationMilliseconds < millisecondsPerFrame) {
      SDL_Delay(millisecondsPerFrame - frameDurationMilliseconds);
    }
  }
}

void Engine::setBackgroundFillColor(SDL_Color clBackgroundFill)
{
  clBackgroundFill_ = clBackgroundFill;
}

void Engine::close()
{
  LOG(log::DEBUG) << "Engine::close()";
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  SDL_DestroyWindow(window_);
  screenSurface_ = nullptr;
  window_ = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

} // namespace neon
