#pragma once
#include "Observer.h"
//https://gameprogrammingpatterns.com/observer.html
namespace dae
{
    class Subject
    {
    public:
        Subject() = default;
        virtual ~Subject() = default;
        void AddObserver(Observer* pObserver);
        void RemoveObserver(Observer* pObserver);
    protected:
        void Notify(const GameObject* gameObject, Event event);
    private:
        Observer* m_pHeadObserver{nullptr};
    };
}
