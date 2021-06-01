#pragma once

class BaseComponent;
class Texture2D;
class Transform;
class Subject;
class Scene;
class GameObject final
{
public:
	GameObject() = delete;
	explicit GameObject(const std::string& objectName, Scene* pScene, bool isSubject = false);
	explicit GameObject(const std::string& objectName, bool isSubject = false);
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update();
	void Start();
	void Render() const;
	void AddComponent(BaseComponent* component); //Adds the desired component to this gameObject (by adding to a BaseComponent vector m_pComponents)

	[[nodiscard]] bool IsMarkedForDeletion() const { return m_MarkForDeletion; };
	void MarkForDeletion() { m_MarkForDeletion = true; };
	[[nodiscard]] bool NeedsToBeRendered()const { return m_NeedsToBeRendered; };
	[[nodiscard]] bool IsActive()const { return m_IsActive; };
	void SetActive(const bool active) { m_IsActive = active; };

	void SetScene(Scene* pScene, bool warnIfFail = true);

	//Determines render order: higher layers are rendered ontop of lower layers
	void SetRenderLayer(int layer);
	[[nodiscard]] int GetRenderLayer() const;

	
	template<typename T>
	T* GetComponent()
	{
		for (auto& comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
				return static_cast<T*>(comp);
		}

		Logger::LogWarning("GetComponent() -> Component doesn't exist on GameObject");
		return nullptr;
	};

	template<typename T>
	const T* GetConstComponent() const
	{
		for (auto& comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
				return static_cast<T*>(comp);
		}

		Logger::LogWarning("GetConstComponent() -> Component doesn't exist on GameObject");
		return nullptr;
	}

	GameObject* GetGameObject(const char* pGameObjectName) const; //returns game object in current scene

	[[nodiscard]] Transform* GetTransform();
	[[nodiscard]] const std::string& GetName()const { return m_ObjectName; };

	[[nodiscard]] Subject* GetSubject()const;
	[[nodiscard]] Scene* GetCurrentScene()const;
private:

	std::vector<BaseComponent*> m_pComponents{};

	bool m_MarkForDeletion{ false }; //true: this game object will be deleted from the scene at the end of the current update
	bool m_NeedsToBeRendered{ false }; //true: Render() of this gameObject will be called from the scene manager, not every game object needs to be rendered.
	bool m_IsActive{ true };
	std::string m_ObjectName{};

	Scene* m_pCurrentScene{};

	Subject* const m_pSubject{ nullptr };

	int m_RenderLayer{0};
};
