#include "../headers/myheader.h"

/**
 * cleanup - function to clean SDL elements
 * @init: a pointer of sdlinit struct
 */
void cleanup(sdlinit *init)
{
	free(init->pixels);
	SDL_DestroyTexture(init->texture);
	SDL_DestroyRenderer(init->renderer);
	SDL_DestroyWindow(init->window);
}
