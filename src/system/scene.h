#pragma once

#include "core/window.h"
#include "entity.h"
#include "field.h"

struct window;

struct scene
{
	SDL_Texture* scene_texture_pallete[256]{ nullptr };
	std::vector<entity_base*> entities;
	SDL_Rect temp_rect;
	field* field;
	uint32_t entity_count = 0;
	bool display_hitbox;
	bool display_field;
	bool display_entities;
	bool enable_collision;

	uint32_t add_player(const char* identifier, uint32_t posx, uint32_t posy, const char* texture, bool controllable = false, bool collision = true);
	uint32_t add_ball(uint32_t posx, uint32_t posy);
	void delete_entity(uint32_t id);

	void update(window& sdlwindow);
};