#pragma once
#include "MiniginPCH.h"
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent :public BaseComponent
	{
	public:
		enum class ImageTypes
		{
			png
		};

		explicit RenderComponent(const std::string& filename = "PlaceHolderPng.png"); //Place holder is used to avoid empty m_Texture
		explicit RenderComponent(std::shared_ptr<Texture2D> texture);
		~RenderComponent() = default;
		void Render()const override;
		void UpdateTexture(std::shared_ptr<Texture2D> texture);
	private:
		std::shared_ptr<Texture2D> m_Texture;
	};
}
