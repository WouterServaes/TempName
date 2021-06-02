#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

class Transform final
{
public:
	Transform(const Transform& other) :m_Position(other.GetPosition()) {};
	Transform& operator=(const Transform& other);
	Transform(Transform&& other) noexcept = delete;
	Transform& operator=(Transform&& other) noexcept = delete;

	Transform() = default;
	explicit Transform(const glm::vec3& position) :m_Position(position) {};
	~Transform() = default;

	[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
	[[nodiscard]] const glm::vec3& GetLastPosition() const { return m_LastPosition; }
	void SetPosition(float x = 0.f, float y = 0.f, float z = 0.f);
	void SetPosition(const glm::vec3& pos = glm::vec3(0.f, 0.f, 0.f));
	void Translate(const glm::vec3& translation);
	void Translate(float x, float y, float z);

	[[nodiscard]] const glm::vec2& GetScale() const { return m_Scale; }
	[[nodiscard]] float GetUniformScale() const { return m_Scale.x; }
	void ScaleUniform(float scale);
	void Scale(float scaleX, float scaleY);
	void Scale(const glm::vec2& scale);
private:
	glm::vec3 m_Position;
	glm::vec3 m_LastPosition;
	glm::vec2 m_Scale{1.f,1.f};
};
