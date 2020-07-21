#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : _sdlWindow(nullptr, SDL_DestroyWindow),
      _sdlRenderer(nullptr, SDL_DestroyRenderer),
      screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) 
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdlWindow.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, screen_width,
                                    screen_height, SDL_WINDOW_SHOWN));
  
  if (nullptr == _sdlWindow.get()) 
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdlRenderer.reset(SDL_CreateRenderer(_sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED));
  
  if (nullptr == _sdlRenderer.get()) 
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::Renderer(std::shared_ptr<Snake> snake, const std::size_t screen_width, const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height) :
  Renderer::Renderer(screen_width, screen_height, grid_width, grid_height)
{ 
  // Calling Renderer() constructor already constructs _snake, so we must do the assignation here.
  _snake = snake;
}

Renderer::~Renderer() {
  // This destructor is called when Renderer is created as Rvalue and moved into the Heap
  // As tis function closes the window, must be called only once: in Game desctructor.
  //SDL_Quit();
}

Renderer::Renderer(Renderer &&source) :
  screen_width(source.screen_width),
  screen_height(source.screen_height),
  grid_width(source.grid_width),
  grid_height(source.grid_height),
  _snake(std::move(source._snake)),
  _sdlWindow(std::move(source._sdlWindow)),
  _sdlRenderer(std::move(source._sdlRenderer))
{
  // Is not necessary to NULL the "source" pointers as they are moved
  //source._sdlWindow = nullptr;
  //source._sdlRenderer = nullptr;
}

void Renderer::Render(SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(_sdlRenderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdlRenderer.get());

  // Render food
  SDL_SetRenderDrawColor(_sdlRenderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(_sdlRenderer.get(), &block);

  // Render snake's body
  SDL_SetRenderDrawColor(_sdlRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : _snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdlRenderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(_snake->head_x) * block.w;
  block.y = static_cast<int>(_snake->head_y) * block.h;
  if (_snake->alive) {
    SDL_SetRenderDrawColor(_sdlRenderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdlRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdlRenderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(_sdlRenderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps, int difficultyLevel) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + 
                    " Level: " + std::to_string(difficultyLevel)};
  SDL_SetWindowTitle(_sdlWindow.get(), title.c_str());
}
