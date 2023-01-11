#pragma once

#include "entity.h"

struct entity_base;

enum collision_type
{
	COL_WALL    = 0x00,
	COL_ENTITY  = 0x01,
	COL_SPECIAL = 0x02
};

struct box_collider
{
	void* touch[8]{ nullptr }; //< how many entities are currently touching the collider (nullptr = end of check)
	void* owner;               //< what the collider belongs to
	float x;
	float y;
	float w;
	float h;
	uint8_t touch_count = 0;
	uint8_t type;

	void touching(box_collider* other)
	{
		if (this != other &&
			touch_count < 8 &&
			x     < other->x + other->w &&
			x + w > other->x            &&
			y     < other->y + other->h &&
			y + h > other->y            )
		{
			// if already touching other, return
			for (int i = 0; i < 8; i++)
				if (touch[i] == other->owner) return;

			touch[touch_count] = other->owner;
			touch_count++;
		}
		else
		{
			// if not touching, search through array and remove other
			for (int i = 0; i < 8; i++)
			{
				if (touch[i] == other->owner)
				{
					touch[i] = nullptr;
					touch_count--;
				}
			}
		}
	}
};