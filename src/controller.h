#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <memory>

class Controller {
 public:
    Controller(std::shared_ptr<Snake> snake);
    void HandleInput(bool &running);

 private:
    std::shared_ptr<Snake> _snake;
};

#endif