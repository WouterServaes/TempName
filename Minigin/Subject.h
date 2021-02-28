#pragma once
#include "Observer.h"
//https://gameprogrammingpatterns.com/observer.html
namespace dae
{
    class Subject
    {
    public:
        Subject() = default;
        ~Subject() ;
        void AddObserver(Observer* pObserver);
        void RemoveObserver(Observer* pObserver);
        void Notify(const std::shared_ptr<GameObject>& gameObject, Event event);
    private:
        Observer* m_pHeadObserver{nullptr};
    };
}
