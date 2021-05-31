#pragma once
struct SDL_Window;

extern int GameMain();

class Minigin
{
public:
	Minigin(int windowWidth = 640, int windowHeight = 480);
	virtual ~Minigin() = default;
	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) noexcept = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) noexcept = delete;
	void Run();

	[[nodiscard]] int GetWindowWidth() const;
	[[nodiscard]] int GetWindowHeight() const;
protected:
	virtual void LoadGame() = 0;

private:
	void Initialize();
	void Cleanup();
	bool* m_QuitGame{ new bool(false) };
	static const int MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps
	const float MsPerUpdate{ MsPerFrame / 1000.f };
	SDL_Window* m_Window{};
	const int m_WindowWidth, m_WindowHeight;
};
