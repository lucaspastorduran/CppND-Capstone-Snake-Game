#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  Renderer(std::shared_ptr<Snake> snake, const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps, int difficultyLevel);

 private:
  // an ordinary delete call is not correct. 
  // We use decltype to automatically construct the correct deleter format from the deleter function.
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _sdlWindow;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _sdlRenderer;
  std::shared_ptr<Snake> _snake;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif