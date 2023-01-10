#include "pch.h"
#include "game.h"

#include "common/log.h"
#include "core/window.h"
#include "system/entity.h"
#include "system/scene.h"
#include "system/serialize.h"
#include "system/texture.h"

window sdlwindow;
scene game_scene;

void init()
{
	log::init();

	sdlwindow.init("SDL", 1326, 720);
	sdlwindow.add_panel<hierarchy>(&game_scene);
	sdlwindow.add_panel<info>(&game_scene);
	//sdlwindow.add_panel<memory>(&game_scene);

	texture::set_renderer(sdlwindow.sdlrenderer);
	texture::add_texture("res/tex/hitbox.png", "hitbox");
	texture::set_opacity("hitbox", 126);
	texture::add_texture("res/tex/red.png", "red");
	texture::add_texture("res/tex/blue.png", "blue");
	texture::add_texture("res/tex/ball.png", "ball");
	texture::add_texture("res/tex/color.png", "colorful");
	texture::add_texture("res/tex/tex.png", "grid");

	game_scene.scene_texture_pallete[0] = texture::get_texture("colorful");
	game_scene.scene_texture_pallete[1] = texture::get_texture("grid");
	
	game_scene.add_player("player1", 1326 / 2, 720 / 1.25, "red", true);
	game_scene.add_player("player2", 1326 / 2, 720 / 4, "blue");

	deserialize_field_binary("res/scene/scene.bin", game_scene);

	game_scene.display_entities = true;
	game_scene.display_field    = true;
	game_scene.enable_collision = true;
}

uint32_t main_loop()
{
	while (1)
	{
		sdlwindow.fc.before = SDL_GetTicks();

		SDL_SetRenderDrawColor(sdlwindow.sdlrenderer, 0, 128, 255, 255);
		SDL_RenderClear(sdlwindow.sdlrenderer);
		SDL_PollEvent(&sdlwindow.sdlevent);
		ImGui_ImplSDL2_ProcessEvent(&sdlwindow.sdlevent);

		switch (sdlwindow.sdlevent.type)
		{
		case SDL_QUIT:
			return 0;
		}

		game_scene.update(sdlwindow);
		sdlwindow.render_panels();

		SDL_RenderPresent(sdlwindow.sdlrenderer);

		sdlwindow.fc.apply_delay((1.0f / sdlwindow.framerate) * 1000);
	}
	return 0;
}