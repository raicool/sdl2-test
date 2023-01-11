#pragma once

#include "gfx/rect.h"

struct tile
{
	tile() {};
	tile(float _x, float _y, float _w, float _h, uint8_t _idx = 0)
		: x(_x), y(_y), w(_w), h(_h), texture_index(_idx) {}

	float x;
	float y;
	float w;
	float h;
	uint8_t texture_index = 0;  // texture index based on scene's texture pallete
	char* name = (char*)"tile";

	SDL_FRect* sdlrect() { return reinterpret_cast<SDL_FRect*>(this); }
};

struct field
{
	std::vector<tile> tile_map; //< contains model, texture index, and collision type for each tile in the field
	uint32_t tile_count = 0;         //< width of the map in # of tiles (should not go above 25565)
}; 