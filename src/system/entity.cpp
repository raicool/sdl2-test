#include "pch.h"
#include "entity.h"

#include "common/log.h"

entity_base::entity_base(uint32_t id, uint32_t posx, uint32_t posy)
	: id(id)
{
	model.x = posx;
	model.y = posy;
	model.w = 64;
	model.h = 64;
	model.angle = 0;
	collision = true;
	hitbox.owner = this;
	hitbox.type = COL_ENTITY;
}

void entity_base::update(float delta) {};

void player::update(float delta)
{

	if (control)
	{
		const uint8_t* _keyboard = SDL_GetKeyboardState(NULL);
		model.x += ((-_keyboard[SDL_SCANCODE_A] + _keyboard[SDL_SCANCODE_D]) * speed) * (delta / 16);
		model.y += ((-_keyboard[SDL_SCANCODE_W] + _keyboard[SDL_SCANCODE_S]) * speed) * (delta / 16);
	}

//	LOG_INFO("x = {}, y = {}", rpos.x, rpos.y);
	hitbox.x = model.x + 3;
	hitbox.y = model.y + 3;
	hitbox.w = model.w - 6;
	hitbox.h = model.h - 6;
}

void ball::update(float delta)
{
//	const uint8_t* _keyboard = SDL_GetKeyboardState(NULL);
	
	if (hitbox.touch[0])
	{
		player* p_pos = (player*)(hitbox.touch[0]);
		direction = (abs(model.y - p_pos->model.y) + abs(model.x - p_pos->model.x));
		LOG_INFO(direction);
		velocity = 4.5;
	}
	else
	{
		if (velocity >= 0)
		{
			velocity -= friction * delta;
		}
	}
	if (velocity < 0) velocity = 0;

	model.x += (velocity * (delta / 16)) * (-1 * direction);
	model.y += (velocity * (delta / 16)) * (direction);

	hitbox.x = model.x;
	hitbox.y = model.y;
	hitbox.w = model.w;
	hitbox.h = model.h;
}