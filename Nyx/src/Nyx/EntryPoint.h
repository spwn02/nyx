#pragma once

#include "Application.h"
#include "Log.h"

#ifdef NYX_PLATFORM_WINDOWS

extern Nyx::Application* Nyx::createApplication();

int main(int argc, char** argv)
{
  Nyx::Log::init();
  NYX_CORE_WARN("Initialized Log!");
  int a = 5;
  NYX_INFO("Hello! Var={0}", a);

  auto app = Nyx::createApplication();
  app->run();
  delete app;
}

#endif