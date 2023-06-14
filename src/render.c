#include "../headers/myheader.h"

/**
 * calculateRayCast - Raycasting calculations
 * @init: pointer to sdlinit struct
 * @rayDirX: Pointer to rayDirX
 * @rayDirY: Pointer to rayDirY
 * @mapX: Pointer to mapX
 * @mapY: Pointer to mapY
 * @sideDistX: Pointer to sideDistX
 * @sideDistY: Pointer to sideDistX
 * @deltaDistX: Pointer to deltaDistX
 * @deltaDistY: Pointer to deltaDistY
 * @stepX: Pointer to stepX
 * @stepY: Pointer to stepY
 * @side: Pointer to side
 * @hit: Pointer to hit
 * @perpWallDist: Pointer to perpWallDist
 */
void calculateRayCast(sdlinit *init, double *rayDirX, double *rayDirY,
		int *mapX, int *mapY, double *sideDistX, double *sideDistY,
		double *deltaDistX, double *deltaDistY, int *stepX,
		int *stepY, int *side, int *hit, double *perpWallDist)
{
	if (*rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (init->player.x - *mapX) * (*deltaDistX);
	} else
	{
		*stepX = 1;
		*sideDistX = (*mapX + 1.0 - init->player.x) * (*deltaDistX);
	}
	if (*rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (init->player.y - *mapY) * (*deltaDistY);
	} else
	{
		*stepY = 1;
		*sideDistY = (*mapY + 1.0 - init->player.y) * (*deltaDistY);
	}

	while (*hit == 0) /*Projection of rays from player untill they hit a wall*/
	{
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += *deltaDistX;
			*mapX += *stepX;
			*side = 0;
		} else
		{
			*sideDistY += *deltaDistY;
			*mapY += *stepY;
			*side = 1;
		}
		if (worldMap[*mapX][*mapY] > 0)
			*hit = 1;
	}
	/*Perpendicular distance to wall to prevent fish-eye distortion*/
	if (*side == 0)
		*perpWallDist = (*mapX - init->player.x + (1 - *stepX) / 2) / (*rayDirX);
	else
		*perpWallDist = (*mapY - init->player.y + (1 - *stepY) / 2) / (*rayDirY);
}

/**
 * drawWalls - A function to draw walls
 * @init: Pointer to sdlinit struct
 * @x: int
 * @drawStart: Starting point of drawing walls
 * @drawEnd: Ending point of drawing walls
 * @side: int
 * @mapX: int
 * @mapY: int
 */
void drawWalls(sdlinit *init, int x, int drawStart, int drawEnd, int side,
		int mapX, int mapY)
{
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= SCREEN_H)
		drawEnd = SCREEN_H - 1;

	Uint32 color;

	if (worldMap[mapX][mapY] == 1)
		color = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32),
					100, 100, 100, 255);
	else if (worldMap[mapX][mapY] == 2)
		color = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32),
				64, 64, 200, 255);
	else if (worldMap[mapX][mapY] == 3)
		color = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32),
				200, 64, 64, 255);
	else
		color = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32),
				200, 64, 64, 255);

	if (side == 1)/*Make one side of walls darker*/
		color -= 15;

	for (int y = 0; y < SCREEN_H; y++)
	{
		if (y < drawStart)
			init->pixels[y * SCREEN_W + x] =
				SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 135, 206, 235, 255);
		else if (y >= drawStart && y <= drawEnd)
			init->pixels[y * SCREEN_W + x] = color;
		else
			init->pixels[y * SCREEN_W + x] =
				SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 50, 205, 50, 255);
	}
}

/**
 * renderAll - A function to render all elements
 * @init: sdlinit struct item
 */
void renderAll(sdlinit *init)
{
	for (int x = 0; x < SCREEN_W; x++)
	{
		double cameraX = 2 * x / (double)SCREEN_W - 1;
		double rayDirX = init->player.dirX + init->player.planeX * cameraX;
		double rayDirY = init->player.dirY + init->player.planeY * cameraX;
		int mapX = (int)init->player.x;
		int mapY = (int)init->player.y;
		double sideDistX, sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int stepX, stepY;
		int hit = 0;
		int side;

		calculateRayCast(init, &rayDirX, &rayDirY, &mapX, &mapY, &sideDistX,
				&sideDistY, &deltaDistX, &deltaDistY, &stepX, &stepY,
				&side, &hit, &perpWallDist);

		int lineHeight = (int)(SCREEN_H / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_H / 2;
		int drawEnd = lineHeight / 2 + SCREEN_H / 2;

		drawWalls(init, x, drawStart, drawEnd, side, mapX, mapY);
	}
	SDL_UpdateTexture(init->texture, NULL, init->pixels,
			SCREEN_W * sizeof(Uint32));
	SDL_RenderClear(init->renderer);
	SDL_RenderCopy(init->renderer, init->texture, NULL, NULL);
	SDL_RenderPresent(init->renderer);
}
