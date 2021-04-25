#pragma once
#include "MiniginPCH.h"
#include "Texture2D.h"
#include "BaseComponent.h"

namespace dae
{
	class Render_Comp final:public BaseComponent
	{
	public:
		explicit Render_Comp(const std::string& filename = "PlaceHolderPng.png"); //Place holder is used to avoid empty m_Texture
		explicit Render_Comp(std::shared_ptr<Texture2D> texture);
		~Render_Comp() = default;
		Render_Comp(const Render_Comp& other) = delete;
		Render_Comp(Render_Comp&& other) noexcept = delete;
		Render_Comp& operator=(const Render_Comp& other) = delete;
		Render_Comp& operator=(Render_Comp&& other) noexcept = delete;

		void Render()const override;

		///texture + resize
		/// width/height < 0 -> original texture size is used
		void UpdateTexture(std::shared_ptr<Texture2D> texture, float dstWidth = -1.f, float dstHeight = -1.f);

		//cut out part of texture
		void UpdateTexture(std::shared_ptr<Texture2D> texture, float srcX, float srcY, float srcWidth, float srcHeight);

		//cut out + resize
		void UpdateTexture(std::shared_ptr<Texture2D> texture, float dstWidth, float dstHeight, float srcX, float srcY, float srcWidth, float srcHeight);
	private:
		std::shared_ptr<Texture2D> m_Texture{ nullptr };

		float m_DstWidth{}, m_DstHeight{}, m_SrcX{}, m_SrcY{}, m_SrcWidth{}, m_SrcHeight{};

		enum class Method
		{
			Resize, CutOut, CutOutResize
		};

		Method m_Method{ Method::Resize };
	};
}
