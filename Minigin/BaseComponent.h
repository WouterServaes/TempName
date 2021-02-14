#pragma once


namespace dae
{
	class BaseComponent
	{
	public:
		enum class componentType
		{
			render = 0,
			text = 1,
			transform = 2,
			fps = 3,
			animation = 4
		};
		
		BaseComponent(componentType type):m_ComponentType(type){};
		virtual ~BaseComponent() = default;

		const componentType m_ComponentType;
		
	};
}