#include "pch.h"
#include "scene.h"

#include "common/utils.h"
#include "core/window.h"
#include "entity.h"
#include "collision.h"

uint32_t scene::add_player(const char* identifier, uint32_t posx, uint32_t posy, const char* texture, bool controllable, bool collision)
{
	player* new_player = new player{ entity_count, posx, posy };

	new_player->name = identifier;
	new_player->control = controllable;
	new_player->collision = collision;
	new_player->model.set_texture(texture);

	vector2<float> tex_size = texture_size<float>(texture);
	new_player->model.w = tex_size.x;
	new_player->model.h = tex_size.y;

	entities.push_back(new_player);

	entity_count++;
	return new_player->id;
}

uint32_t scene::add_ball(uint32_t posx, uint32_t posy)
{
	ball* new_ball = new ball{ entity_count, posx, posy };

	new_ball->name = "ball";
	new_ball->model.set_texture("ball");

	vector2<float> tex_size = texture_size<float>("ball");
	new_ball->model.w = tex_size.x;
	new_ball->model.h = tex_size.y;

	entities.push_back(new_ball);

	entity_count++;
	return new_ball->id;
}

void scene::delete_entity(uint32_t id)
{
	delete entities[id];
	entities.erase(entities.begin() + id);
	entity_count--;
}

void scene::update(window& sdlwindow)
{
	// field
	if (display_field)
	{
		for (int i = 0; i < field->tile_count; i++)
		{
			SDL_RenderCopyF(sdlwindow.sdlrenderer, scene_texture_pallete[field->tile_map[i].texture_index], NULL, field->tile_map[i].sdlrect());
		}
	}

	// entity
	entity_base* ent = nullptr;
	entity_base* other = nullptr;
	for (int i = 0; i < entity_count; i++)
	{
		ent = entities[i];

		// collision
		if (ent->collision && enable_collision)
		{
			for (int j = 0; j < entity_count; j++)
			{
				other = entities[j];
				ent->hitbox.touching(&other->hitbox);
			}
		}

		ent->update(sdlwindow.fc.delta);
		
		// hitbox display
		if (display_hitbox)
		{
			temp_rect.x = ent->hitbox.x;
			temp_rect.y = ent->hitbox.y;
			temp_rect.w = ent->hitbox.w;
			temp_rect.h = ent->hitbox.h;

			if (SDL_RenderCopyEx(sdlwindow.sdlrenderer, texture::get_texture("hitbox"), NULL, &temp_rect, NULL, NULL, SDL_FLIP_NONE) == -1)
				LOG_ERROR("Problem rendering quad : {}", SDL_GetError());
		}

		// entity
		if (display_entities)
		{
			if (SDL_RenderCopyExF(sdlwindow.sdlrenderer, ent->model.texture, NULL, ent->model, ent->model.angle, NULL, SDL_FLIP_NONE) == -1)
				LOG_ERROR("Problem rendering quad : {}", SDL_GetError());
		}
	}
}