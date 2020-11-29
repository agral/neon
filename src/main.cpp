#include "log/Logger.hpp"
#include "Vec2D.hpp"
#include "Engine.hpp"

int main()
{
  LOG(neon::log::DEBUG) << "main.cpp has started.";

  ::neon::Engine engine{};
  engine.init();
  engine.startMainLoop();
  return 0;
}
