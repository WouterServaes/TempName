#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		bool IsMarkedForDeletion() const { return m_MarkForDeletion; };
	protected:
		void MarkForDeletion() { m_MarkForDeletion = true; }; //don'm_NewText delete scene objects, mark them for deletion and delete it after everything is updated
	private:
		bool m_MarkForDeletion{ false };
	};
}
