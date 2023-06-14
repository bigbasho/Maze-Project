#include "../headers/myheader.h"

/**
 * isCollision - A function to check if the player collides with a wall
 * @x: player pos
 * @y: player pos
 *
 * Return: 1 upon collision
 */
int isCollision(double x, double y)
{
	/* Check if the player position collides with a wall*/
	int mapX = (int)x;
	int mapY = (int)y;

	if (mapX < 0 || mapX >= mapW || mapY < 0 || mapY >= mapH)
		return (1); /* Collision with boundary walls*/
	return (worldMap[mapX][mapY] != 0);
}

/**
 * movePlayerPos - Function to handle player movement
 * @init: sdlinit struct
 * @nextX: player next x pos
 * @nextY: player next y pos
 */
void movePlayerPos(sdlinit *init, double nextX, double nextY)
{
	/*If no collision, move player by nextX and nextY values*/
	if (!isCollision(nextX, nextY))
	{
		init->player.x = nextX;
		init->player.y = nextY;
	}
	/*
	 * If collision occurs, and if the wall is of number 3
	 * move player in a random place in the map.
	 */
	if (isCollision(nextX, nextY) && worldMap[(int)nextX][(int)nextY] == 3)
	{
		init->player.x = rand() % mapW;
		init->player.y = rand() % mapH;
	}
}

/**
 * rotatePlayerDir - Function to handle player rotation
 * @init: sdlinit struct
 * @angle: rotaion degree
 */
void rotatePlayerDir(sdlinit *init, double angle)
{
	double oldDirX = init->player.dirX;
	double oldPlaneX = init->player.planeX;

	init->player.dirX =
		init->player.dirX * cos(angle) - init->player.dirY * sin(angle);
	init->player.dirY =
		oldDirX * sin(angle) + init->player.dirY * cos(angle);
	init->player.planeX =
		init->player.planeX * cos(angle) - init->player.planeY * sin(angle);
	init->player.planeY =
		oldPlaneX * sin(angle) + init->player.planeY * cos(angle);
}

/**
 * movePlayer - Function to handle keyboard input
 * @init: sdlinit struct
 * @event: SDL event
 */
void movePlayer(sdlinit *init, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN) /*In the event a key is pressed*/
	{
		double nextX = init->player.x + init->player.dirX * 0.1;
		double nextY = init->player.y + init->player.dirY * 0.1;

		switch (event->key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				{
					movePlayerPos(init, nextX, nextY);
				}
				break;
			case SDLK_DOWN:
			case SDLK_s:
				{
					nextX -= 2 * (init->player.dirX * 0.1);
					nextY -= 2 * (init->player.dirY * 0.1);
					movePlayerPos(init, nextX, nextY);
				}
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				{
					rotatePlayerDir(init, 0.1);
				}
				break;
			case SDLK_LEFT:
			case SDLK_a:
				{
					rotatePlayerDir(init, -0.1);
				}
				break;
		}
	}
}
