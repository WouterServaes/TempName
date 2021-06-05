#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

class Transform final
{
public:

	/// <summary>
	/// Copies other transform's position and scale to this transform
	/// </summary>
	Transform(const Transform& other) :m_Position(other.GetPosition()), m_Scale(other.GetScale()) {}

	/// <summary>
	/// Sets this transform's position and scale to the other's
	/// </summary>
	Transform& operator=(const Transform& other);
	
	Transform(Transform&& other) noexcept = delete;
	Transform& operator=(Transform&& other) noexcept = delete;

	/// <summary>
	/// Position = 0,0,0 and scale = 1,1
	/// </summary>
	Transform() = default;

	/// <summary>
	/// Position = position and scale = 1,1
	/// </summary>
	explicit Transform(const glm::vec3& position) :m_Position(position) {};
	~Transform() = default;

	///Returns the current position
	[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }

	///Returns the previous position
	[[nodiscard]] const glm::vec3& GetLastPosition() const { return m_LastPosition; }

	/// <summary>
	/// Sets the position to new position, previous position gets saved
	/// </summary>
	void SetPosition(float x = 0.f, float y = 0.f, float z = 0.f);
	/// <summary>
	/// Sets the position to new position, previous position gets saved
	/// </summary>
	void SetPosition(const glm::vec3& pos = glm::vec3(0.f, 0.f, 0.f));

	/// <summary>
	/// translates the current position, previous position gets saved
	/// </summary>
	void Translate(const glm::vec3& translation);

	/// <summary>
	/// translates the current position, previous position gets saved
	/// </summary>
	void Translate(float x, float y, float z);

	///Returns the scale as a 2d vector
	[[nodiscard]] const glm::vec2& GetScale() const { return m_Scale; }

	//Returns the x of the scale, use only if x and y of scale are the same
	[[nodiscard]] float GetUniformScale() const { return m_Scale.x; }

	/// <summary>
	/// scales x and y by one scale
	/// </summary>
	void ScaleUniform(float scale);

	/// <summary>
	/// scales x and y
	/// </summary>
	void Scale(float scaleX, float scaleY);

	/// <summary>
	/// scales x and y
	/// </summary>
	void Scale(const glm::vec2& scale);

	/// <summary>
	/// Avoids IsLeft or IsRight booleans
	/// </summary>
	enum class Side
	{
		Left, Right
	};

private:
	glm::vec3 m_Position;
	glm::vec3 m_LastPosition;
	glm::vec2 m_Scale{1.f,1.f};
};
