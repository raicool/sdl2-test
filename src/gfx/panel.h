#pragma once

#include "core/window.h"
#include "system/entity.h"
#include "system/field.h"
#include "system/scene.h"

struct window;
struct scene;

struct panel_base
{
	panel_base(window* sdlwindow, scene* new_scene)
		: current_window(sdlwindow), current_scene(new_scene), visible(true) {};

	window* current_window;
	scene* current_scene;
	bool visible;

	virtual void render() = 0;
	virtual void link_window(window*) = 0;
	virtual void link_scene(scene*) = 0;
};

struct hierarchy : public panel_base
{
	hierarchy(window* sdlwindow, scene* new_scene)
		: panel_base(sdlwindow, new_scene) {};


	void render() override;
	void link_window(window* new_window) override { current_window = new_window; };
	void link_scene(scene* new_scene) override { current_scene = new_scene; };

	void render_entity_node(uint32_t id, entity_base* entity);
	void render_tile_node(tile* tile);
};

struct info : public panel_base
{
	info(window* sdlwindow, scene* new_scene)
		: panel_base(sdlwindow, new_scene) {};

	bool save_popup_closed;
	char name_buffer[256]{ 0 };

	void render() override;
	void link_window(window* new_window) override { current_window = new_window; };
	void link_scene(scene* new_scene) override { current_scene = new_scene; };
};

struct memory : public panel_base
{
	memory(window* sdlwindow, scene* new_scene)
		: panel_base(sdlwindow, new_scene) {};

	void* dst;

	void render() override;
	void link_window(window* new_window) override { current_window = new_window; };
	void link_scene(scene* new_scene) override { current_scene = new_scene; };
};