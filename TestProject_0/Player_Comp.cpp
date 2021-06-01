#include "MiniginPCH.h"
#include "Player_Comp.h"
#include "CharacterController_Comp.h"
void Player_Comp::Update()
{
}

void Player_Comp::Start()
{
	m_pController = GetComponent<CharacterController_Comp>();
	InitInput();
}

void Player_Comp::InitInput()
{
	
}
