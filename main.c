#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <SDL.h>

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
const clock_t FRAME_TARGET = CLOCKS_PER_SEC / 60;

SDL_Window *window;
SDL_Renderer *renderer;

void error(const char *action) {
  eprintf("Failed to %s: %s\n", action, SDL_GetError());
  exit(1);
}

#include "loop.c"

void init_sdl() {
  SDL_Init(SDL_INIT_VIDEO);

  const char *video_driver = SDL_GetVideoDriver(0);
  SDL_VideoInit(video_driver);
  eprintf("Initialized video driver: %s\n", video_driver);

  SDL_Rect bounds;
  SDL_GetDisplayUsableBounds(0, &bounds);
  WINDOW_WIDTH = bounds.w;
  WINDOW_HEIGHT = bounds.h;
}

void init_window() {
  window = SDL_CreateWindow(
      "SDL Demo",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) error("create window");
  eprintf("Created window\n");

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) error("create renderer");
  eprintf("Created renderer\n");
}

void quit() {
  eprintf("Quit\n");
  SDL_DestroyWindow(window);
  SDL_VideoQuit();
}

int main() {
  init_sdl();
  init_state();
  init_window();

  loop();

  destroy_state();
  quit();
}
