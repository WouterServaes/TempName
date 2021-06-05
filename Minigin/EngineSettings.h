#pragma once
#include <SDL.h> //included for the macros

/// <summary>
/// Title, window size and start window position
/// </summary>
struct EngineSettings
{
	std::string Title = std::string("Wouter Servaes Exam");
	const int WindowWidth = 640;
	const int WindowHeight = 480;
	const int WindowX = SDL_WINDOWPOS_CENTERED;
	const int WindowY = SDL_WINDOWPOS_CENTERED;
};