#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "FpsCounter.h"

std::string dae::FpsComponent::GetAsString()const
{
	return std::to_string(FpsCounter::GetInstance().fps);
}