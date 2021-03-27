#pragma once
#include "MiniginPCH.h"
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{
	class Render_Comp :public BaseComponent
	{
	public:
		explicit Render_Comp( const std::string& filename = "PlaceHolderPng.png"); //Place holder is used to avoid empty m_Texture
		explicit Render_Comp(std::shared_ptr<Texture2D> texture);
		~Render_Comp() = default;
		void Render()const override;
		void UpdateTexture(std::shared_ptr<Texture2D> texture);
	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}
