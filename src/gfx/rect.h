#pragma once

#include "common/type.h"

struct rect
{
	SDL_FRect rect;
	SDL_Texture* texture;
	uint32_t angle;

	void set_texture(const char* tex);
	void set_position(uint32_t posx, uint32_t posy);

	operator SDL_FRect* const () { return &rect; }
};