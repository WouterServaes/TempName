#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)


class Transform;
class CharacterController_Comp;
class CoilyAi final
{
public:
	CoilyAi(const std::vector<Transform*>& playerTransforms, int* pDefeatedPlayerByIndex, Transform* pCoilyTransform, CharacterController_Comp* pCoilyCharController);
	virtual ~CoilyAi() = default;
	CoilyAi(const CoilyAi& other) = delete;
	CoilyAi(CoilyAi&& other) noexcept = delete;
	CoilyAi& operator=(const CoilyAi& other) = delete;
	CoilyAi& operator=(CoilyAi&& other) noexcept = delete;
	void Mover(bool goToDisk, glm::vec2 diskPos);

private:
	const std::vector<Transform*>& m_pPlayersTransform;
	int* m_pDefeatedByPlayerIndex;
	Transform* m_pCoilyTransform;
	CharacterController_Comp* m_pCoilyCharacterController;
};

