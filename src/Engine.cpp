/**
 * Name: Engine.cpp
 * Description: Implements a class representing a Neon rendering engine
 * Created on: 26.07.2019
 * Last modified: 10.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include "Engine.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
: m_pathAssets(std::string())
, m_window(nullptr)
, m_windowWidth(0)
, m_windowHeight(0)
, m_renderer(nullptr)
, m_screenSurface(nullptr)
{
}

Engine::~Engine()
{
  close();
}

bool Engine::init(const std::string& title, int posX, int posY, int width, int height, Uint32 flags)
{
  LOG(log::VERBOSE) << "Trying to locate assets' path...";
  bool result = ::neon::utility::getAssetsPath(m_pathAssets);
  if (result) {
    LOG(log::INFO) << "Assets path: " << m_pathAssets;
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
  m_window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, flags);
  if (m_window == nullptr)
  {
    LOG(log::ERROR) << "Failed to create the game window.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }
  m_windowWidth = width;
  m_windowHeight = height;

  Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  LOG(log::VERBOSE) << "Creating a renderer for the game window";
  m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
  if (m_renderer == nullptr)
  {
    LOG(log::ERROR) << "Failed to create a vsynced renderer.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }
  LOG(log::VERBOSE) << "Created a vsynced window renderer: " << m_renderer;

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

  m_screenSurface = SDL_GetWindowSurface(m_window);
  if (m_screenSurface == nullptr)
  {
    LOG(log::ERROR) << "Failed to obtain a screen surface from the game window.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  return true;
}

void Engine::startMainLoop()
{
  Timer fpsCapTimer;
  auto millisecondsPerFrame = 1000.0 / 60.0;
  unsigned long long currentFrame = 0ULL;

  LOG(log::VERBOSE) << "Initializing main loop at " << millisecondsPerFrame << " milliseconds per frame";
  Texture neonTexture;
  std::string path = m_pathAssets + "neon_logo.png";
  if (!neonTexture.loadFromFile(path, m_renderer))
  {
    LOG(log::ERROR) << "Failed to load the resource [" << path << "]";
    return;
  }
  LOG(log::DEBUG) << "Texture [" << path << "] loaded correctly, size: "
      << neonTexture.width() << " x " << neonTexture.height();

  bool isQuittingMainLoop = false;
  SDL_Event sdlEvent;

  while (!isQuittingMainLoop)
  {
    fpsCapTimer.start();

    // Processes the incoming events:
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
      if (sdlEvent.type == SDL_QUIT)
      {
        isQuittingMainLoop = true;
      }
    }

    // Applies game logic:
    // (TODO implement)

    // Renders the scene:
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);
    // @TODO define the scene color as set/get-able class member variable.
    // @TODO maybe define a lightweight wrapper on SDL_Color struct?

    SDL_RenderClear(m_renderer);

    // @TODO: write code that actually renders the scene.
    auto x = 0.5 * (m_windowWidth - neonTexture.width());
    auto y = 0.5 * (m_windowHeight - neonTexture.height());
    neonTexture.render(x, y);

    SDL_RenderPresent(m_renderer);

    currentFrame += 1ULL;
    // Caps the frame rate at target FPS value:
    double frameDurationMilliseconds = fpsCapTimer.time() * 1000;
    if (frameDurationMilliseconds < millisecondsPerFrame) {
      SDL_Delay(millisecondsPerFrame - frameDurationMilliseconds);
    }
  }
}

void Engine::close()
{
  LOG(log::DEBUG) << "Engine::close()";
  SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;

  SDL_DestroyWindow(m_window);
  m_screenSurface = nullptr;
  m_window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

} // namespace neon
