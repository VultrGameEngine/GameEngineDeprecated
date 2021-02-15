#pragma once
#include "Game.hpp"
#include <core/core.h>

class Vultr
{
  public:
    void Init(bool debug);
    void LoadGame(const std::string &path);
    void InitGame();
    void UpdateGame(float &t);
    void Destroy();
    GLFWwindow *window;

  private:
    bool debug;
    Game *game;
};
