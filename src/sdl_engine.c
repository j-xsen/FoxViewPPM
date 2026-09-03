#include "sdl_engine.h"

int initialize_engine(SDLEngine* engine, const char* title) {
  engine->is_running = 1;
  engine->is_dragging = 0;

  int result = initialize_renderer(&engine->renderer, title, get_width(),
                                   get_height(), SDL_WINDOW_OPENGL);

  if (result != 0) {
    printf("Error initializing renderer: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

void run(SDLEngine* engine) {
  while (engine->is_running) {
    process_input(engine);
    draw(&engine->renderer);
  }
}

void process_input(SDLEngine* engine) {
  while (SDL_PollEvent(&engine->event) != 0) {
    switch (engine->event.type) {
      case SDL_EVENT_QUIT:
        engine->is_running = 0;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (engine->event.key.key == SDLK_ESCAPE) {
          engine->is_running = 0;
        }
        break;
      case SDL_EVENT_MOUSE_WHEEL: {
        float zoom = engine->renderer.zoom + engine->event.wheel.y * ZOOM_STEP;
        if (zoom < ZOOM_MIN) zoom = ZOOM_MIN;
        if (zoom > ZOOM_MAX) zoom = ZOOM_MAX;
        engine->renderer.zoom = zoom;
        break;
      }
      case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (engine->event.button.button == SDL_BUTTON_LEFT) {
          engine->is_dragging = 1;
        }
        break;
      case SDL_EVENT_MOUSE_BUTTON_UP:
        if (engine->event.button.button == SDL_BUTTON_LEFT) {
          engine->is_dragging = 0;
        }
        break;
      case SDL_EVENT_MOUSE_MOTION:
        if (engine->is_dragging) {
          engine->renderer.pan_x += engine->event.motion.xrel;
          engine->renderer.pan_y += engine->event.motion.yrel;
        }
        break;
      default:
        break;
    }
  }
}

void terminate_engine(SDLEngine* engine) {
  terminate_renderer(&engine->renderer);
  SDL_Quit();
}