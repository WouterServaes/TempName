#pragma once
#include <Observer.h>
class CharacterObserver final:public Observer
{
public:
	CharacterObserver() = default;
	~CharacterObserver() = default;
	CharacterObserver(const CharacterObserver & other) = delete;
	CharacterObserver(CharacterObserver && other) noexcept = delete;
	CharacterObserver& operator=(const CharacterObserver & other) = delete;
	CharacterObserver& operator=(CharacterObserver && other) noexcept = delete;

	void OnNotify(GameObject * pGameObject, Event event) override;
private:
	void FellOffGrid(GameObject* pGameObject);
};

