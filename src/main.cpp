#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Select level of difficulty
  int difficultyLevel;
  std::cout << "Select difficulty level from 1 to 5:" << std::endl;
  std::cin >> difficultyLevel;
  while (difficultyLevel < 1 || difficultyLevel > 5)
  {
    std::cout << "Select difficulty level from 1 to 5:" << std::endl;
    std::cin >> difficultyLevel;
  }

  //Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, std::move(difficultyLevel));
  game.Run(kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}