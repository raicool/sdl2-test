#pragma once

namespace texture
{
	uint32_t add_texture(const char* dir, std::string_view id);
	void set_opacity(std::string_view id, uint8_t value);
	SDL_Texture* get_texture(std::string_view id);

	void set_renderer(SDL_Renderer* renderer);
}