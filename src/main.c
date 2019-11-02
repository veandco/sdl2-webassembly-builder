#include <SDL2/SDL.h>
#include <emscripten.h>

static const char WINDOW_TITLE[] = "Hello, WebAssembly!";

static void main_loop(void *user_data)
{
	SDL_Renderer *renderer = (SDL_Renderer *) user_data;
	SDL_Rect rect;
	SDL_Event event;
	double magnitude = 0.0;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 64);
	SDL_RenderDrawRect(renderer, NULL);

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			magnitude = hypot(event.motion.xrel, event.motion.yrel);

			rect.x = event.motion.x;
			rect.y = event.motion.y;
			rect.w = fmax(1.0, fmin(magnitude, 100));
			rect.h = fmax(1.0, fmin(magnitude, 100));

			SDL_RenderDrawRect(renderer, &rect);
			break;
		}
	}

	SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, NULL);

	emscripten_set_main_loop_arg(main_loop, renderer, 0, 1);
}
