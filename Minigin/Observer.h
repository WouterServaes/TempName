#pragma once
//https://gameprogrammingpatterns.com/observer.html

enum class Event;
class GameObject;
class Observer
{
public:
	friend class Subject;
	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) noexcept = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) noexcept = delete;
	virtual void OnNotify(GameObject* pGameObject, Event event) = 0;
private:
	Observer* m_pNextObserver{ nullptr };
};
