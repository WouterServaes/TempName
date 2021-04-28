#include "MiniginPCH.h"
#include "AudioLogger.h"

AudioLogger::AudioLogger(AudioInterface* audioToLog)
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

void AudioLogger::PlaySound(const int soundId, const int volume)
{
	Logger::LogInfo(static_cast<std::string>("Played sound - ID: " + std::to_string(soundId) + " volume: " + std::to_string(volume)).c_str());
	m_CurrentAudioSystem->PlaySound(soundId, volume);
}

void AudioLogger::StopSound(const int soundId)
{
	Logger::LogInfo(static_cast<std::string>("Stopped sound - ID: " + std::to_string(soundId)).c_str());
	m_CurrentAudioSystem->StopSound(soundId);
}

void AudioLogger::AddAudioFile(const char* fileName)
{
	auto msg{ static_cast<std::string>("Added audio file ") };
	msg += fileName;
	Logger::LogInfo(msg.c_str());
	m_CurrentAudioSystem->AddAudioFile(fileName);
}