#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

Controller::Controller(std::shared_ptr<Snake> snake) :
  _snake(snake)
{
}

void Controller::HandleInput(bool &running) {
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
          _snake->ChangeDirection(Snake::Direction::kUp);
          break;

        case SDLK_DOWN:
          _snake->ChangeDirection(Snake::Direction::kDown);
          break;

        case SDLK_LEFT:
          _snake->ChangeDirection(Snake::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          _snake->ChangeDirection(Snake::Direction::kRight);
          break;
      }
    }
  }
}