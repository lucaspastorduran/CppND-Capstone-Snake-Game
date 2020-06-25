#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int &&difficulty_level)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      difficultyLevel(std::move(difficulty_level)) 
{
  _snake = std::make_shared<Snake>(Snake(grid_width, grid_height, difficultyLevel));
  _controller = std::make_shared<Controller> (Controller(_snake));
  
  PlaceFood();
}

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    _controller->HandleInput(running);
    Update();
    renderer.Render(_snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, difficultyLevel);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!_snake->alive) return;

  _snake->Update();

  int new_x = static_cast<int>(_snake->head_x);
  int new_y = static_cast<int>(_snake->head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score += difficultyLevel;
    PlaceFood();
    // Grow snake and increase speed.
    _snake->GrowBody();
    // Speed increase depends on difficulty level
    // BUG: when speed is above 1 (at 1.05 starts bug)
    _snake->IncreaseSpeed();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return _snake->size; }
int Game::GetDifficultyLevel() const { return difficultyLevel; }