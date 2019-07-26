/**
 * Name: Engine.cpp
 * Description: Implements a class representing a Neon rendering engine
 * Created on: 26.07.2019
 * Last modified: 26.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include "Engine.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "log/Logger.hpp"

namespace neon
{

Engine::Engine()
: m_window(nullptr)
, m_renderer(nullptr)
, m_screenSurface(nullptr)
{
}

bool Engine::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    LOG(log::ERROR) << "Failed to initialize the SDL system.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    LOG(log::WARNING) << "Could not enable linear texture filtering.";
  }

  m_window = SDL_CreateWindow(
    "neon",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    800,
    600,
    SDL_WINDOW_SHOWN
  );
  if (m_window == nullptr)
  {
    LOG(log::ERROR) << "Failed to create a game window.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
  if (m_renderer == nullptr)
  {
    LOG(log::ERROR) << "Failed to create a vsynced renderer.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    LOG(log::ERROR) << "Failed to initialize SDL_image module.";
    LOG(log::ERROR) << "SDL_image error: " << IMG_GetError();
    return false;
  }

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
  bool isQuittingMainLoop = false;
  SDL_Event sdlEvent;
  while (!isQuittingMainLoop)
  {
    // Processes the incoming events:
    while (SDL_PollEvent(&sdlEvent))
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

    SDL_RenderPresent(m_renderer);
  }
}

void Engine::close()
{
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
