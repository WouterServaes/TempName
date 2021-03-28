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
			const auto it{ std::find_if(m_AudioFiles.begin(), m_AudioFiles.end(), [fileName](const std::string& str)
				{
					return str == fileName;
				}) };
			
			if (it == m_AudioFiles.end())
			{
				m_AudioIds.push_back(static_cast<int>(m_AudioIds.size()));
				m_AudioFiles.push_back(fileName);
			}
			else
				m_AudioIds.push_back(static_cast<int>(std::distance(m_AudioFiles.begin(), it)));
			
			
		};

	protected:
		std::vector<std::string> m_AudioFiles{};
		std::vector<int> m_AudioIds{};
	};
}
