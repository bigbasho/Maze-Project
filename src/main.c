#include "../headers/myheader.h"

/**
 * main - Entry function of the entire program
 *
 * Return: if successful 0, otherwise 1
 */
int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) /*Initialization of SDL video*/
	{
		printf("Failed to initialize SDL: %s", SDL_GetError());
		return (1);
	}

	sdlinit init;/*Declaration of sdlinit struct with SDL window, renderer, etc*/

	if (!Init(&init)) /*Initialization and error handling upon failure*/
	{
		SDL_Quit();
		return (1);
	}

	SDL_Event event;
	int running = 1;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)/*Close event*/
			{
				running = 0;
			}
			movePlayer(&init, &event);/*Player movement handling*/
		}

		renderAll(&init);/*Rendering scene and events*/
	}

	cleanup(&init);/*Free resources*/
	SDL_Quit();

	return (0);
}
