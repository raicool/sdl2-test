#include "pch.h"
#include "entity.h"

#include "common/log.h"

entity_base::entity_base(uint32_t id, uint32_t posx, uint32_t posy)
	: id(id)
{
	model.rect.x = posx;
	model.rect.y = posy;
	x = posx;
	y = posy;
	model.rect.w = 64;
	model.rect.h = 64;
	model.angle = 0;
	collision = true;
	hitbox.owner = this;
	hitbox.type = COL_ENTITY;
}

void entity_base::update(float delta) {};

void player::update(float delta)
{
	SDL_FRect& pos = model.rect;

	if (control)
	{
		const uint8_t* _keyboard = SDL_GetKeyboardState(NULL);
		pos.x += ((-_keyboard[SDL_SCANCODE_A] + _keyboard[SDL_SCANCODE_D]) * speed) * (delta / 16);
		pos.y += ((-_keyboard[SDL_SCANCODE_W] + _keyboard[SDL_SCANCODE_S]) * speed) * (delta / 16);
	}

//	LOG_INFO("x = {}, y = {}", rpos.x, rpos.y);
	hitbox.x = pos.x + 3;
	hitbox.y = pos.y + 3;
	hitbox.w = pos.w - 6;
	hitbox.h = pos.h - 6;
}

void ball::update(float delta)
{
	SDL_FRect& pos = model.rect;
//	const uint8_t* _keyboard = SDL_GetKeyboardState(NULL);
	
	if (hitbox.touch[0])
	{
		player* p_pos = (player*)(hitbox.touch[0]);
		direction = (abs(pos.y - p_pos->y) + abs(pos.x - p_pos->x));
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

	pos.x += (velocity * (delta / 16)) * (-1 * direction);
	pos.y += (velocity * (delta / 16)) * (direction);

	hitbox.x = pos.x;
	hitbox.y = pos.y;
	hitbox.w = pos.w;
	hitbox.h = pos.h;
}