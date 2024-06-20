#include <math.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH    	1360
#define SCREEN_HEIGHT   	768

#define MAP_WIDTH		8
#define MAP_HEIGHT		8
#define PERSON_SIZE		10

#define FALSE			0
#define TRUE			1
#define DEGREE_TO_RADIANS	0.0174533
#define RADIAN_TO_DEGREES	57.2958
#define PI			3.14159265359  /* find max floats using #define */

/* place this in own file/header */
int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}
};

/* add definitive comments for betty && move to header */
/* clean this up */
typedef struct player {
	float pos_x;
	float pos_y;
	float delta_x;
	float delta_y;
	float direction_x;
	float direction_y;
	float camera_plane_x;
	float camera_plane_y;
	/* the angle is where the player is facing ... come up with a clearer name */
	float angle;
} player_t;

/**
 * prepBackdrop - prepares backdrop for render draw
 * @renderer: backdrop to be darkened
 * Return: void
 */
void prepBackdrop(SDL_Renderer *renderer)
{
	/* set colour to black */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

/**
 * drawPlayer - draws player onto the renderer
 * @renderer: the backdrop in use
 * @player: the player object
 * Return: void
 */
void drawPlayer(SDL_Renderer *renderer, player_t *player)
{
	/* int x; */

	/* set colour to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	/*
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		SDL_RenderDrawLine(renderer, x, 50, x, SCREEN_HEIGHT - 100);
	}
	*/

	SDL_Rect rect = {player->pos_x, player->pos_y, PERSON_SIZE, PERSON_SIZE};
	SDL_RenderDrawRect(renderer, &rect);

	/* temp: allow visibility of line of sight in 2d render */
	SDL_RenderDrawLine(
		renderer,
		player->pos_x,
		player->pos_y,
		player->delta_x * PERSON_SIZE,
		player->delta_y * PERSON_SIZE
	);

	SDL_RenderPresent(renderer);
}

/**
 * handleEvent - processes event/input
 * @event: the event/input
 * @player: the player object
 * Return: FALSE if user quits, else TRUE
 */
int handleEvent(SDL_Event *event, player_t *player)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			return (FALSE);

		if (event->key.keysym.sym == SDLK_ESCAPE)
			return (FALSE);

		/* swap the arrows for a, s, d, w */
		/* SDL_GetKeyName(event.key.keysym.sym) */
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.sym == SDLK_UP)
			{
				/*
				 * temp angular change in direction;
				 * map this to forward and sideways
				 * buttons
				 */
				player->pos_y += player->delta_y;
				player->pos_x += player->delta_x;
			}
			else if (event->key.keysym.sym == SDLK_DOWN)
			{
				/*
				 * temp angular change in direction;
				 * map this to forward and sideways
				 * buttons
				 */
				player->pos_y -= player->delta_y;
				player->pos_x -= player->delta_x;
			}
			else if (event->key.keysym.sym == SDLK_LEFT)
			{
				/* find an properly name an value to change by */
				player->angle -= 0.1;


				if (player->angle < 0)
					/* recall, 2 * pi is 360deg in radian */
					player->angle += 2 * PI;

				/* move to own function */
				player->delta_x = cos(player->angle) * PERSON_SIZE;
				player->delta_y = sin(player->angle) * PERSON_SIZE;
			}
			else if (event->key.keysym.sym == SDLK_RIGHT)
			{
				/* find an properly name an value to change by */
				player->angle += 0.1;

				if (player->angle > 2 * PI)
					/* recall, 2 * pi is 360deg in radian */
					player->angle -= 2 * PI;

				/* move to own function */
				player->delta_x = cos(player->angle) * PERSON_SIZE;
				player->delta_y = sin(player->angle) * PERSON_SIZE;
			}
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
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Doom by Monde Anna");

	player_t player = {
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		// 5,  // starting with a delta of one means we can move forward/back
		// 5,  // starting with a delta of one means we can move forward/back
		cos(0) * PERSON_SIZE,
		sin(0) * PERSON_SIZE,
		-1,
		0,
		0,
		0.66,
		0
	};

	do {
		prepBackdrop(renderer);
		drawPlayer(renderer, &player);
	} while (handleEvent(&event, &player));

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return (0);
}
