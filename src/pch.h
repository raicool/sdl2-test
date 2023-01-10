#pragma once

// Standard Library
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <filesystem>

// Windows
#include <dinput.h>
#include <xaudio2.h>

// SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

// Entt
//#include <entt/entt.hpp>

// Dear Imgui
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>

// spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"