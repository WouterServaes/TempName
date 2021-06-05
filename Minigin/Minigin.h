#pragma once
struct SDL_Window;

extern int GameMain();
struct EngineSettings;
class Minigin
{
public:
	Minigin() = default;
	virtual ~Minigin() = default;
	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) noexcept = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) noexcept = delete;

	/// <summary>
	/// Runs the game from start to finish, contains the game loop
	/// </summary>
	void Run();

	/// <summary>
	/// Engine/game settings 
	/// </summary>
	static EngineSettings* pEngineSettings;

	/// <summary>
	/// Used in game loop, setting this to false leaves the loop and ends the game
	/// </summary>
	static bool* pQuitGame;
protected:

	/// <summary>
	/// Used to add scenes to the game
	/// </summary>
	virtual void LoadGame() = 0;

private:
	/// <summary>
	/// Initialized SDL window, renderer and audio
	/// </summary>
	void Initialize();

	/// <summary>
	/// Cleans up Renderer, audio and closes SDL window
	/// </summary>
	void Cleanup();
	static const int MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps
	const float MsPerUpdate{ MsPerFrame / 1000.f };
	SDL_Window* m_Window{};
};
