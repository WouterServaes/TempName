#pragma once
//https://gameprogrammingpatterns.com/observer.html
namespace dae
{
	enum class Event;
	class GameObject;
	class Observer
	{
	public:
		friend class Subject;
		Observer() = default;
		virtual ~Observer() = default;
		virtual void OnNotify(const std::shared_ptr<GameObject>& gameObject, Event event) = 0;
	private:
		Observer* m_pNextObserver{ nullptr };
	};

}

