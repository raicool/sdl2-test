#include "pch.h"
#include "rect.h"

#include "system/texture.h"

void rect::set_position(uint32_t posx, uint32_t posy)
{
	rect.x = posx;
	rect.y = posx;
}

void rect::set_texture(const char* tex)
{
	texture = texture::get_texture(tex);
}