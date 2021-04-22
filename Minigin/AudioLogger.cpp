#include "MiniginPCH.h"
#include "AudioLogger.h"
#include "Logger.h"

AudioLogger::AudioLogger(BaseAudio* audioToLog)
{
	m_CurrentAudioSystem = audioToLog;
}

void AudioLogger::Start()
{
	Logger::LogInfo("Audio Started");
	m_CurrentAudioSystem->Start();
}

void AudioLogger::End()
{
	Logger::LogInfo("Audio Ended");
	m_CurrentAudioSystem->End();
	delete m_CurrentAudioSystem;
}

void AudioLogger::Update()
{
	m_CurrentAudioSystem->Update();
}

void AudioLogger::PlaySound(int soundId, int volume)
{
	Logger::LogInfo(std::string("Played sound - ID: " + std::to_string(soundId) + " volume: " + std::to_string(volume)).c_str());
	m_CurrentAudioSystem->PlaySound(soundId, volume);
}

void AudioLogger::StopSound(int soundId)
{
	Logger::LogInfo(std::string("Stopped sound - ID: " + std::to_string(soundId)).c_str());
	m_CurrentAudioSystem->StopSound(soundId);
}

void AudioLogger::AddAudioFile(const char* fileName)
{
	auto msg{ std::string("Added audio file ") };
	msg += fileName;
	Logger::LogInfo(msg.c_str());
	m_CurrentAudioSystem->AddAudioFile(fileName);
}
