#include "pch.h"
#include "window.h"

void window::init(const char* window_title, uint16_t win_width, uint16_t win_height)
{
	title = window_title;
	width = win_width;
	height = win_height;
	framerate = 60;

	sdlwindow = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_RESIZABLE);
	sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(sdlrenderer, width, height);

	if (!sdlwindow) { LOG_ERROR("SDL Window could not be created {}", SDL_GetError()); }
	else { LOG_INFO("SDL Window initialized"); }

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(sdlwindow, sdlrenderer);
	ImGui_ImplSDLRenderer_Init(sdlrenderer);
}

void window::render_panels()
{
	ImGui_ImplSDL2_NewFrame(sdlwindow);
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(nullptr);

	for (panel_base* _panel : panel)
	{
		_panel->render();
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}