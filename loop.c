#include "gol/gol.h"

SDL_bool running = SDL_TRUE;
grid_t source_grid, dest_grid;

int CELL_SIZE = 1;

int min(int x, int y) {
  return x > y ? y : x;
}

void init_state() {
  source_grid = read_grid();
  dest_grid = new_grid(source_grid.size);

  CELL_SIZE = min(
      WINDOW_WIDTH / source_grid.size.cols,
      WINDOW_HEIGHT / source_grid.size.rows);
  WINDOW_WIDTH = CELL_SIZE * source_grid.size.cols;
  WINDOW_HEIGHT = CELL_SIZE * source_grid.size.rows;
}

void destroy_state() {
  print_grid(source_grid);

  dispose_grid(source_grid);
  dispose_grid(dest_grid);
}

void update() {
  step_grid(source_grid, dest_grid);

  grid_t tmp;
  tmp = source_grid;
  source_grid = dest_grid;
  dest_grid = tmp;
}

void draw() {
  SDL_SetRenderDrawColor(
      renderer,
      0x00, 0x00, 0x00,
      SDL_ALPHA_OPAQUE);
  SDL_RenderClear(
      renderer);

  SDL_SetRenderDrawColor(
      renderer,
      0xff, 0xff, 0xff,
      SDL_ALPHA_OPAQUE);

  SDL_Rect rect = { 0, 0, CELL_SIZE, CELL_SIZE };
  grid_t grid = source_grid;
  char *current = grid.str;
  for (int i = 0; i < grid.size.rows; i++, current++) {
    rect.y = i * CELL_SIZE;

    for (int j = 0; j < grid.size.cols; j++, current++) {
      rect.x = j * CELL_SIZE;

      if (*current != ' ')
        SDL_RenderFillRect(
            renderer, &rect);
    }
  }

  SDL_RenderPresent(renderer);
}

void handle_events() {
  static SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {

      case SDL_QUIT:
        running = SDL_FALSE;
        break;

      case SDL_WINDOWEVENT:
        printf("Window event: %d\n", event.window.event);
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {

          case SDLK_ESCAPE:
            running = SDL_FALSE;
            break;

          default:
            if (isprint(event.key.keysym.sym))
              printf("Keydown: %c\n", event.key.keysym.sym);
            else
              printf("Keydown: %d\n", event.key.keysym.sym);
            break;

        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {

          default:
            if (isprint(event.key.keysym.sym))
              printf("Keyup: %c\n", event.key.keysym.sym);
            else
              printf("Keyup: %d\n", event.key.keysym.sym);
            break;

        }
        break;

      default:
        printf("Event: %d\n", event.type);
        break;

    }
  }
}

void loop() {
  while (running) {
    update();
    draw();
    handle_events();
    SDL_Delay(5);
  }
}
