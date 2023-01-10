#include "pch.h"
#include "texture.h"

#include "common/log.h"

namespace texture
{
	std::unordered_map<std::string_view, SDL_Texture*> textures;
	SDL_Renderer* current_renderer;
	uint32_t texture_count;

	void set_renderer(SDL_Renderer* renderer)
	{
		current_renderer = renderer;
	}

	uint32_t add_texture(const char* dir, std::string_view id)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

		SDL_Surface* surface = IMG_Load(dir);

		if (!surface)
		{
			LOG_ERROR("Error creating texture {} : {}", id, SDL_GetError());
			return 0;
		}

		textures[id] = SDL_CreateTextureFromSurface(current_renderer, surface);

		LOG_TRACE("texture {} created at address {}", id, (void*)textures[id]);

		SDL_FreeSurface(surface);

		texture_count++;
		return texture_count;
	}

	void set_opacity(std::string_view id, uint8_t value)
	{
		if (SDL_SetTextureAlphaMod(textures[id], value) == -1) LOG_ERROR(SDL_GetError());
	}

	SDL_Texture* get_texture(std::string_view id)
	{
		return textures[id];
	}
}