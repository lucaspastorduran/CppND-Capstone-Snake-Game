#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_QUIT) 
    {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
      switch (e.key.keysym.sym) 
      {
        case SDLK_UP:
          snake.ChangeDirection(Snake::Direction::kUp);
          break;

        case SDLK_DOWN:
          snake.ChangeDirection(Snake::Direction::kDown);
          break;

        case SDLK_LEFT:
          snake.ChangeDirection(Snake::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          snake.ChangeDirection(Snake::Direction::kRight);
          break;
      }
    }
  }
}