#pragma once
namespace dae
{
	class BaseAudio
	{
	public:
		virtual ~BaseAudio() = default;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void Update() = 0;
		virtual void PlaySound(int soundId, int volume) = 0;
		virtual void StopSound(int soundId) = 0;
		
		void AddSoundFile(const char* fileName)
		{
			m_AudioFiles.push_back(fileName);
		};

	protected:
		std::vector<std::string> m_AudioFiles{};
	};
}
