#pragma once

#include <SDL.h>

#include "common/log.h"
#include "core/frame.h"
#include "gfx/panel.h"
#include "system/scene.h"

struct panel_base;

struct window
{
	std::vector<panel_base*> panel;
	SDL_Event sdlevent;
	SDL_Window* sdlwindow;
	SDL_Renderer* sdlrenderer;
	const char* title;
	frame fc;
	uint32_t framerate;
	uint16_t width;
	uint16_t height;

	template<typename T>
	void add_panel(scene* set_scene)
	{
		// check if template can be converted to panel (probably not even necessary)
		(bool)static_cast<panel_base*>((T*)0) ? LOG_FATAL("failed. is this a valid panel?") : void();

		panel.emplace_back((panel_base*)new T(this, set_scene));
	}
	void render_panels();

	void init(const char* window_title, uint16_t win_width, uint16_t win_height);
	void on_resize();
};