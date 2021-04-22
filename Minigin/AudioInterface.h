#pragma once
namespace dae
{
	class AudioInterface
	{
	public:
		virtual ~AudioInterface() = default;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void Update() = 0;
		virtual void PlaySound(int soundId, int volume) = 0;
		virtual void StopSound(int soundId) = 0;
		virtual void AddAudioFile(const char* fileName) = 0;		
	};
}
