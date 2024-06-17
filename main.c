#include <SDL2/SDL.h>

#define SCREEN_WIDTH    1360
#define SCREEN_HEIGHT   768

#define FALSE		0
#define TRUE		1

/**
 * prepBackdrop - prepares backdrop for render draw
 * @renderer: backdrop to be darkened
 * Return: void
 */
void prepBackdrop(SDL_Renderer *renderer)
{
	/* set colour to black */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

/**
 * drawPlayer - draws player onto the renderer
 * @renderer: the backdrop in use
 * Return: void
 */
void drawPlayer(SDL_Renderer *renderer)
{
	int x;

	/* set colour to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		SDL_RenderDrawLine(renderer, x, 50, x, SCREEN_HEIGHT - 100);
	}

	SDL_RenderPresent(renderer);
}

/**
 * handleEvent - processes event/input
 * @event: the event/input
 * Return: FALSE if user quits, else TRUE
 */
int handleEvent(SDL_Event *event)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			return (FALSE);

	}

	return (TRUE);
}

/**
 * main - entry point
 *
 * Description: draw single pixel onto screen as to
 * demonstrate that the sdl2 library is installed
 * and operational
 *
 * Return: 0
 */
int main(void)
{
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Doom by Monde Anna");

	do {
		prepBackdrop(renderer);
		drawPlayer(renderer);
	} while (handleEvent(&event));

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return (0);
}
