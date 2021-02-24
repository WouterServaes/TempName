#pragma once
#include "GameObject.h"
namespace dae
{
	class Scene
	{
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update();
		void Render() const;

		explicit Scene(const std::string& name);
		virtual ~Scene() = default;
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		virtual void InitializeScene() = 0;
	protected:
		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
	};

}
