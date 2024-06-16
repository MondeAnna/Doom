#include <SDL2/SDL.h>

#define FIVE_SECONDS	5000
#define PLAYER_SIZE	10
#define SCREEN_WIDTH    1360
#define SCREEN_HEIGHT   768
#define TRUE		1
#define FALSE		0

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
			if (event->key.keysym.sym == SDLK_UP)
				player->y-=PLAYER_SIZE;
			else if (event->key.keysym.sym == SDLK_DOWN)
				player->y+=PLAYER_SIZE;
			else if (event->key.keysym.sym == SDLK_LEFT)
				player->x-=PLAYER_SIZE;
			else if (event->key.keysym.sym == SDLK_RIGHT)
				player->x+=PLAYER_SIZE;
	}

	return (TRUE);
}


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
 * main - entry point
 *
 * Description: draw single pixel onto screen as to
 * demonstrate that the sdl2 library is installed
 * and operational
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Doom by Monde Anna");

	SDL_Rect player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_SIZE, PLAYER_SIZE};

	do {
		darkenBackdrop(renderer);
		drawPlayer(renderer, &player);
	} while(handleEvent(&event, &player));

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return (0);
}
