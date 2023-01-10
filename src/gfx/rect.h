#pragma once

#include "common/type.h"

struct rect
{
	float x;
	float y;
	float w;
	float h;
	SDL_Texture* texture;
	uint32_t angle;

	void set_texture(const char* tex);
	void set_position(uint32_t posx, uint32_t posy);

	operator SDL_FRect* const () { return reinterpret_cast<SDL_FRect*>(this); }
};