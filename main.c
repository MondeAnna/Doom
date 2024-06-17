#include <SDL2/SDL.h>

#define FIVE_SECONDS	5000
#define SIZE	10
#define WIDTH    1360
#define HEIGHT   768
#define TRUE		1
#define FALSE		0

/**
 * darkenBackdrop - darkens the backdrop
 * @renderer: backdrop to be darkened
 * Return: void
 */
void darkenBackdrop(SDL_Renderer *renderer)
{
	/* set colour to black */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

/**
 * drawMap - draws map onto the renderer
 * @renderer: the backdrop in use
 * Return: void
 */
void drawMap(SDL_Renderer *renderer)
{
	int col, row;
	int map[][8] = {
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1}
	};

	SDL_Rect block = {0, 0, SIZE * 2, SIZE * 2};

	for (row = 0; row < 8; row++)
	{
		for (col = 0; col < 8; col++)
		{
			if (map[row][col])
				/* set colour to white */
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else
				/* set colour to black */
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			block.x = row;
			block.y = col;

			SDL_RenderDrawRect(renderer, &block);
			SDL_RenderPresent(renderer);
		}
	}
}

/**
 * drawPlayer - draws player onto the renderer
 * @renderer: the backdrop in use
 * @player: the player object
 * Return: void
 */
void drawPlayer(SDL_Renderer *renderer, SDL_Rect *player)
{
	/* set colour to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, player);
	SDL_RenderPresent(renderer);
}

/**
 * handleEvent - processes event/input
 * @event: the event/input
 * @player: the player object
 * Return: FALSE if user quits, else TRUE
 */
int handleEvent(SDL_Event *event, SDL_Rect *player)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			return (FALSE);

		/* swap the arrows for a, s, d, w */
		/* SDL_GetKeyName(event.key.keysym.sym) */
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.sym == SDLK_UP)
				player->y -= SIZE;
			else if (event->key.keysym.sym == SDLK_DOWN)
				player->y += SIZE;
			else if (event->key.keysym.sym == SDLK_LEFT)
				player->x -= SIZE;
			else if (event->key.keysym.sym == SDLK_RIGHT)
				player->x += SIZE;
		}
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
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Doom by Monde Anna");

	SDL_Rect player = {WIDTH / 2, HEIGHT / 2, SIZE, SIZE};

	drawMap(renderer);

	do {
		darkenBackdrop(renderer);
		drawPlayer(renderer, &player);
	} while (handleEvent(&event, &player));

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return (0);
}
