#pragma once
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		Minigin() = default;
		~Minigin() = default;
		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) noexcept = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) noexcept = delete;
		
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		bool* m_QuitGame{ new bool(false) };
		static const int MsPerFrame{ 16 }; //16 for 60 fps, 33 for 30 fps
		const float MsPerUpdate{MsPerFrame/1000.f};
		SDL_Window* m_Window{};
	};
}