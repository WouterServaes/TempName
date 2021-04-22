#pragma once
#include "AudioInterface.h"

namespace dae
{
	//When no audio is assigned, we don't want to break the program.
	class NullAudio final:public AudioInterface
	{
	public:
		NullAudio() = default;
		~NullAudio() = default;
		void Start() override {/*do nothing*/ };
		void End() override {/*do nothing*/ };
		void Update() override {/*do nothing*/ };
		void PlaySound(int , int ) override {/*do nothing*/};
		void StopSound(int) override {/*do nothing*/ }
		void AddAudioFile(const char* ) override {/*do nothing*/ }
	};
}
