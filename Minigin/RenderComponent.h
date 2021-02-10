#pragma once
#include "MiniginPCH.h"
#include "Texture2D.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Texture2D;
	class RenderComponent
	{
	public:
		RenderComponent(const std::string& filename);
		void Render(const glm::vec3& renderPos)const;
	private:
		std::shared_ptr<Texture2D> m_Texture;
		
	};
}

