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

	/// <summary>
	
	/// </summary>
	/// <param name="objectName"> Name of the game object, used to get the game object from the scene</param>
	/// <param name="isSubject"> Whether the game object is a subject or not</param>
	explicit GameObject(const std::string& objectName, bool isSubject = false);
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	/// <summary>
	/// If game object is active, calls Update on every component
	/// </summary>
	void Update();

	/// <summary>
	/// Calls start on every component
	/// </summary>
	void Start();
	
	/// <summary>
	/// If game object is active, calls Render on every component
	/// </summary>
	void Render() const;

	/// <summary>
	/// Adds the desired component to this gameObject 
	/// </summary>
	void AddComponent(BaseComponent* component); 

	[[nodiscard]] bool IsMarkedForDeletion() const { return m_MarkForDeletion; }

	/// <summary>
	/// Delete the game object at the end of this Update
	/// </summary>
	void MarkForDeletion() { m_MarkForDeletion = true; }
	
	[[nodiscard]] bool NeedsToBeRendered()const { return m_NeedsToBeRendered; }
	[[nodiscard]] bool IsActive()const { return m_IsActive; }

	/// <summary>
	/// Activate/deactive this game object
	/// </summary>
	void SetActive(const bool active) { m_IsActive = active; }

	/// <summary>
	/// Sets the scene of this game object, automatically called when adding the game object to a scene \n
	/// Doesn't change the scene if game objects already has a scene!
	/// </summary>
	void SetScene(Scene* pScene, bool warnIfFail = true);

	//Determines render order: higher layers are rendered ontop of lower layers
	void SetRenderLayer(int layer);
	[[nodiscard]] int GetRenderLayer() const;


	/// <typeparam name="T">component type</typeparam>
	/// <returns>true if game object has component of type </returns>
	template<typename T>
	[[nodiscard]] bool HasComponent()
	{
		for (auto& comp : m_pComponents)
			if (typeid(*comp) == typeid(T))
				return true;
		return false;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pComp">component ptr, gets set if a component of this type exists on the game object</param>
	/// <returns>True if game object has component of type</returns>
	template<typename T>
	[[nodiscard]] bool TryGetComponent(T*& pComp)
	{
		for (auto& comp : m_pComponents)
			if (typeid(*comp) == typeid(T))
			{
				pComp = static_cast<T*>(comp);
				return true;
			}
		
		return false;
	}

	/// <summary>
	///throws warning if component doesn't exist on game object
	/// </summary>
	/// <returns>Component ptr of type T of game object</returns>
	template<typename T>
	T* GetComponent()
	{
		for (auto& comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
				return static_cast<T*>(comp);
		}

		Logger::LogWarning("GetComponent() -> Component doesn't exist on GameObject, name: " + m_ObjectName);
		return nullptr;
	}

	/// <summary>
	///throws warning if component doesn't exist on game object
	/// </summary>
	/// <returns>const Component ptr of type T of game object</returns>
	template<typename T>
	const T* GetConstComponent() const
	{
		for (auto& comp : m_pComponents)
		{
			if (typeid(*comp) == typeid(T))
				return static_cast<T*>(comp);
		}

		Logger::LogWarning("GetConstComponent() -> Component doesn't exist on GameObject, name: " + m_ObjectName);
		return nullptr;
	}

	/// <summary>
	/// returns game object in current scene with given name
	/// </summary>
	[[nodiscard]] GameObject* GetGameObject(const char* pGameObjectName) const;

	///Returns the Transform ptr of the transform component of this game object
	[[nodiscard]] Transform* GetTransform();

	///Returns the name of this game object
	[[nodiscard]] const std::string& GetName()const { return m_ObjectName; };

	///Returns the Subject ptr of this game object
	[[nodiscard]] Subject* GetSubject()const;

	///Returns the scene of this game object
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
