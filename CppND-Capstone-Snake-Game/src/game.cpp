#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int food_count = 0;
  bool running = true;
  bool exitWindows = false;

  // Get Game Level from User
  level_ = renderer.Render();
  setLevelFoodCount(food_count);
  SDL_Log("Selected User Level is %d", level_);
  SDL_Log("Food Count is set as %d", food_count);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, exitWindows);

    if (exitWindows) {
      exitWindows = false;
      if( renderer.ContinueOrExit() )
        running = false;
    }

    Update(food_count );
    renderer.Render(snake, food);

    if(food_count == 0 ) {
       level_++;
       setLevelFoodCount(food_count);
       setSize();
       SDL_Log("<<<  the User Level is %d  >>>", level_);
       SDL_Log("  Need to get %d Food Count for next level", food_count);
       SDL_Log("  Current Snake size is %d", snake.size);
       SDL_Log("  Current Snake speed is %f", snake.speed);
       SDL_Log("  Current Snake growth rate is %d", snake.growth);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, level_);
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
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(int &food_count) {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    food_count--;
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

void Game::setLevelFoodCount(int &food_count){
  switch(level_) {
    case 1: food_count = 5;
      break;
    case 2: food_count = 10;
      break;
    case 3: food_count = 15;
      break;
    case 4: food_count = 20;
      break;
    case 5: food_count = 25;
  }
  return;
}

void Game::setSize() {
  snake.growth = level_;
}

int Game::GetScore() const { return score; }

int Game::GetSize() const { return snake.size; }