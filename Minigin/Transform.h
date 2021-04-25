#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
	public:
		Transform(const Transform& other) :m_Position(other.GetPosition()) {};
		Transform& operator=(const Transform& other);
		Transform(Transform&& other) noexcept = delete;
		Transform& operator=(Transform&& other) noexcept = delete;

		Transform() = default;
		Transform(const glm::vec3& position) :m_Position(position) {};
		~Transform() = default;
		
		
		
		[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0.f, float y = 0.f, float z = 0.f);
		void SetPosition(const glm::vec3& pos = glm::vec3(0.f, 0.f, 0.f));
		void Translate(const glm::vec3& translation);
		void Translate(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
