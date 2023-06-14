#ifndef MYHEADER_H
#define MYHEADER_H

#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_W 1280
#define SCREEN_H 960
#define mapW 50
#define mapH 30

/**
 * struct pl - Player structure
 * @x: player location in x axis
 * @y: player location in y axis
 * @dirX: direction in x axis
 * @dirY: direction in y axis
 * @planeX: plane
 * @planeY: plane
 */
typedef struct pl
{
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
} Player;

/**
 * struct init - SDL window, renderer, texture and pixels and player
 * @window: SDL_Window
 * @renderer: SDL_Renderer
 * @texture: SDL_Texture
 * @pixels: pixels in the sdl window
 * @player: Player struct
 */
typedef struct init
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Uint32 *pixels;
	Player player;
} sdlinit;

/*Function to Initialize SDL*/
int Init(sdlinit *init);

/*Function to clean SDL elements*/
void cleanup(sdlinit *init);

/*Functions to render*/
void calculateRayCast(sdlinit *init, double *rayDirX, double *rayDirY,
		int *mapX, int *mapY, double *sideDistX, double *sideDistY,
		double *deltaDistX, double *deltaDistY, int *stepX,
		int *stepY, int *side, int *hit, double *perpWallDist);
void drawWalls(sdlinit *init, int x, int drawStart, int drawEnd, int side,
		int mapX, int mapY);
void renderAll(sdlinit *init);

/*Function to move the player and handle keyboard events*/
void movePlayerPos(sdlinit *init, double nextX, double nextY);
void rotatePlayerDir(sdlinit *init, double angle);
void movePlayer(sdlinit *init, SDL_Event *event);

/*2D Map*/
extern int worldMap[mapW][mapH];

#endif /*MYHEADER_H*/
