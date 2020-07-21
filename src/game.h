#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_heigth, std::size_t grid_width, 
      std::size_t grid_height, int &&difficulty_level);
  ~Game();
  void Run(std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetDifficultyLevel() const;

 private:
  std::shared_ptr<Snake> _snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::unique_ptr<Controller> _controller;
  std::unique_ptr<Renderer> _renderer;

  int score{0};
  int difficultyLevel = 1; // from 1 to 5: selected by user at the beginning

  void PlaceFood();
  void Update();
};

#endif