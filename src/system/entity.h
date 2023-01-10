#pragma once

#include "gfx/rect.h"
#include "collision.h"

struct entity_base
{
	entity_base() = delete;
	entity_base(uint32_t id, uint32_t posx, uint32_t posy);

	rect model;          //< visible entity model
	box_collider hitbox; //< collision hitbox
	const char* name;    //< entity name
	uint32_t id;         //< entity id
	uint32_t x;          //< entity x coords
	uint32_t y;          //< entity y coords
	bool control;        //< is the entity being controlled by input?
	bool collision;      //< is collision calculated?
	
	virtual void update(float delta) = 0;
};

struct player : entity_base
{
	player(uint32_t id, uint32_t posx, uint32_t posy) : entity_base(id, posx, posy) {};

	uint8_t speed = 10;

	void update(float delta) override;
};

struct ball : entity_base
{
	ball(uint32_t id, uint32_t posx, uint32_t posy) : entity_base(id, posx, posy) {};

	float friction = 0.016; //< how fast ball slows down
	float velocity;         //< how fast ball is moving
	float direction;        //< direction ball is moving (not model angle, the rect class has its own angle var)
	
	void update(float delta) override;
};