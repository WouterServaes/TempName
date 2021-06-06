#include "MiniginPCH.h"
#include "CoopScene.h"

#include "Animation_Comp.h"
#include "CharacterController_Comp.h"
#include "CoilyCreature_Comp.h"
#include "CreatureObserver.h"
#include "DiskManager_Comp.h"
#include "EngineSettings.h"
#include "GameController_Comp.h"
#include "GreenCreature_Comp.h"
#include "Health_Comp.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PlayerManager_Comp.h"
#include "PurpleCreature_Comp.h"
#include "ResourceManager.h"
#include "Score_Comp.h"
#include "Subject.h"
#include "Text_Comp.h"
#include "TileChanger_Comp.h"
#include "Transform.h"
#include "UiComponents.h"
#include "UI_Comp.h"
#include "WorldTileManager_Comp.h"

#include "SceneParser.h"
void CoopScene::InitializeScene()
{
	GetInputManager()->SetMaxControllerAmount(2);
	auto fpsCounter = std::make_shared<GameObject>("Fps");
	fpsCounter->AddComponent(new FpsUI());
	fpsCounter->GetTransform()->SetPosition(5.f, 5.f);
	AddGameObject(fpsCounter);

	InitGameController();
	InitWorld();
	InitPlayers();
	InitUi();
	InitCoily();
	InitGreen();
	InitPurple();
	InitDisks();
}

void CoopScene::Restart()
{
	//player full restart
	GetGameObject("PlayerManager")->GetComponent<PlayerManager_Comp>()->ResetPlayers();
	//gameController restart
	GetGameObject("GameController")->GetComponent<GameController_Comp>()->ResetGame();
	//tiles
	GetGameObject("WorldTileManager")->GetComponent<WorldTileManager_Comp>()->ResetTiles();
	//disk full restart
	GetGameObject("DiskManager")->GetComponent<DiskManager_Comp>()->ResetDisks();
	//creatures full restart
	GetGameObject("Coily")->GetComponent<CoilyCreature_Comp>()->ResetCreature();
	GetGameObject("Ugg")->GetComponent<PurpleCreature_Comp>()->ResetCreature();
	GetGameObject("Wrongway")->GetComponent<PurpleCreature_Comp>()->ResetCreature();
	GetGameObject("Slick")->GetComponent<GreenCreature_Comp>()->ResetCreature();
	GetGameObject("Sam")->GetComponent<GreenCreature_Comp>()->ResetCreature();

	GetGameObject("GameOver")->SetActive(false);
	GetGameObject("GameOverMenu")->SetActive(false);
	GetGameObject("Win")->SetActive(false);
	GetGameObject("WinMenu")->SetActive(false);
}

void CoopScene::InitUi()
{
	const auto sceneData{ SceneParser::GetSceneData(1) };
	const std::string font{ sceneData->Font };
	const auto fontColor{ sceneData->FontColor };
	auto pGameOver{ std::make_shared<GameObject>("GameOver") };
	pGameOver->AddComponent(new Render_Comp());
	pGameOver->AddComponent(new Text_Comp("Game over!", font, 28, fontColor));
	pGameOver->GetTransform()->SetPosition(120.f, 150.f);
	pGameOver->SetActive(false);
	AddGameObject(pGameOver);

	auto pGameOverMenu{ std::make_shared<GameObject>("GameOverMenu") };
	pGameOverMenu->AddComponent(new GameOverUI());
	pGameOverMenu->GetTransform()->SetPosition(120.f, 200.f);
	AddGameObject(pGameOverMenu);
	pGameOverMenu->SetActive(false);

	auto pWin{ std::make_shared<GameObject>("Win") };
	pWin->AddComponent(new Render_Comp());
	pWin->AddComponent(new Text_Comp("You won!", font, 28, fontColor));
	pWin->GetTransform()->SetPosition(120.f, 150.f);
	pWin->SetActive(false);
	AddGameObject(pWin);

	auto pWinMenu{ std::make_shared<GameObject>("WinMenu") };
	pWinMenu->AddComponent(new WinUI());
	pWinMenu->GetTransform()->SetPosition(120.f, 200.f);
	AddGameObject(pWinMenu);
	pWinMenu->SetActive(false);
}

void CoopScene::InitWorld()
{
	const auto sceneData{ SceneParser::GetSceneData(1) };
	const auto pNormalTexture{ ResourceManager::GetInstance().LoadTexture(sceneData->NormalTileTexture) }
		, pIntermediateTexture{ ResourceManager::GetInstance().LoadTexture(sceneData->IntermediateTileTexture) }
	, pHighlightTexture{ ResourceManager::GetInstance().LoadTexture(sceneData->HighlightedTileTexture) };

	const auto bottomRowAmount{ sceneData->PyramidSize };
	auto pWorldGridManager{ std::make_shared<GameObject>("WorldTileManager") };
	AddGameObject(pWorldGridManager);
	pWorldGridManager->GetTransform()->ScaleUniform(.5f);
	pWorldGridManager->AddComponent(new WorldTileManager_Comp(pNormalTexture, pHighlightTexture, pIntermediateTexture, bottomRowAmount));
}

void CoopScene::InitPlayers()
{
	auto pPlayerManager{ std::make_shared<GameObject>("PlayerManager") };
	auto* pPlayerManagerComp{ new PlayerManager_Comp() };
	pPlayerManager->AddComponent(pPlayerManagerComp);
	AddGameObject(pPlayerManager);

	const auto sceneData{ SceneParser::GetSceneData(1) };
	pPlayerManagerComp->AddPlayers(sceneData->Players);

	std::vector<glm::vec2> uiPositions{ { 30.f, 50.f }, { Minigin::pEngineSettings->WindowWidth - 150.f, 50.f } };
	const auto players{ pPlayerManagerComp->GetPlayers() };
	const std::string font{ sceneData->Font };
	const auto fontColor{ sceneData->FontColor };
	for (int idx{}; idx < players.size(); idx++)
	{
		const glm::vec2 uiPos{ uiPositions.at(idx) };

		auto pLiveDisplay{ std::make_shared<GameObject>("Player1LiveUi") };
		pLiveDisplay->AddComponent(new Render_Comp());
		auto* pLiveText{ new Text_Comp("Lives: ", font, 18, fontColor) };
		pLiveDisplay->AddComponent(pLiveText);
		players.at(idx)->GetComponent<Health_Comp>()->AttachTextComp(pLiveText);
		AddGameObject(pLiveDisplay);
		pLiveDisplay->GetTransform()->SetPosition(uiPos.x, uiPos.y);

		auto pScoreDisplay{ std::make_shared<GameObject>("Player1ScoreUi") };
		pScoreDisplay->AddComponent(new Render_Comp());
		auto* pScoreText{ new Text_Comp("Score: ", font, 18, fontColor) };
		pScoreDisplay->AddComponent(pScoreText);
		players.at(idx)->GetComponent<Score_Comp>()->AttachTextComp(pScoreText);
		AddGameObject(pScoreDisplay);
		pScoreDisplay->GetTransform()->SetPosition(uiPos.x, uiPos.y + 20.f);
	}
}

void CoopScene::InitCoily()
{
	const auto coilyData{ SceneParser::GetCreatureData("coily", 1) };
	const auto coilyEggData{ SceneParser::GetCreatureData("coilyEgg", 1) };

	auto pCoily{ std::make_shared<GameObject>("Coily", true) };
	AddGameObject(pCoily);
	pCoily->AddComponent(new Render_Comp());
	pCoily->AddComponent(new Animation_Comp(coilyEggData.TextureData.imgPath, coilyEggData.TextureData.Count, coilyEggData.TextureData.Fps, coilyEggData.TextureData.FrameSize));
	pCoily->AddComponent(new CharacterController_Comp(.15f));
	pCoily->AddComponent(new CoilyCreature_Comp(coilyEggData.TimeBetweenJumps, coilyData.TextureData.imgPath, coilyData.TextureData.Count, coilyData.TextureData.Fps, coilyData.TextureData.FrameSize));
	pCoily->GetTransform()->ScaleUniform(.1f);
	pCoily->GetSubject()->AddObserver(new CreatureObserver());
}

void CoopScene::InitGreen()
{
	auto slickData{ SceneParser::GetCreatureData("slick", 1) };
	auto pSlick{ std::make_shared<GameObject>("Slick", true) };
	AddGameObject(pSlick);
	pSlick->AddComponent(new Render_Comp());
	pSlick->AddComponent(new Animation_Comp(slickData.TextureData.imgPath, slickData.TextureData.Count, slickData.TextureData.Fps, slickData.TextureData.FrameSize));
	pSlick->AddComponent(new CharacterController_Comp(.15f));
	pSlick->AddComponent(new GreenCreature_Comp(slickData.TimeBetweenJumps));
	pSlick->AddComponent(new TileChanger_Comp(TileChanger_Comp::TileChangeLevel::RevertChanges));
	pSlick->GetTransform()->ScaleUniform(.25f);
	pSlick->GetSubject()->AddObserver(new CreatureObserver());

	auto samData{ SceneParser::GetCreatureData("sam", 1) };
	auto pSam{ std::make_shared<GameObject>("Sam", true) };
	AddGameObject(pSam);
	pSam->AddComponent(new Render_Comp());
	pSam->AddComponent(new Animation_Comp(samData.TextureData.imgPath, samData.TextureData.Count, samData.TextureData.Fps, samData.TextureData.FrameSize));
	pSam->AddComponent(new CharacterController_Comp(.15f));
	pSam->AddComponent(new GreenCreature_Comp(samData.TimeBetweenJumps));
	pSam->AddComponent(new TileChanger_Comp(TileChanger_Comp::TileChangeLevel::RevertChanges));
	pSam->GetTransform()->ScaleUniform(.25f);
	pSam->GetSubject()->AddObserver(new CreatureObserver());
}

void CoopScene::InitPurple()
{
	const auto creatureData{ SceneParser::GetSceneData(0)->Creatures };
	const auto uggData{ SceneParser::GetCreatureData("ugg", 1) };
	auto pUgg{ std::make_shared<GameObject>("Ugg", true) };
	AddGameObject(pUgg);
	pUgg->AddComponent(new Render_Comp());
	pUgg->AddComponent(new Animation_Comp(uggData.TextureData.imgPath, uggData.TextureData.Count, uggData.TextureData.Fps, uggData.TextureData.FrameSize));
	pUgg->AddComponent(new CharacterController_Comp(.15f));
	pUgg->AddComponent(new PurpleCreature_Comp(Transform::Side::Left, uggData.TimeBetweenJumps));
	pUgg->GetTransform()->ScaleUniform(.25f);
	pUgg->GetSubject()->AddObserver(new CreatureObserver());

	const auto wrongWayData{ SceneParser::GetCreatureData("wrongway", 1) };
	const auto pWrongway{ std::make_shared<GameObject>("Wrongway", true) };
	AddGameObject(pWrongway);
	pWrongway->AddComponent(new Render_Comp());
	pWrongway->AddComponent(new Animation_Comp(wrongWayData.TextureData.imgPath, wrongWayData.TextureData.Count, wrongWayData.TextureData.Fps, wrongWayData.TextureData.FrameSize));
	pWrongway->AddComponent(new CharacterController_Comp(.15f));
	pWrongway->AddComponent(new PurpleCreature_Comp(Transform::Side::Right, wrongWayData.TimeBetweenJumps));
	pWrongway->GetTransform()->ScaleUniform(.25f);
	pWrongway->GetSubject()->AddObserver(new CreatureObserver());
}

void CoopScene::InitDisks()
{
	const auto disksdata{ SceneParser::GetSceneData(0)->Disks };

	auto pDiskManager{ std::make_shared<GameObject>("DiskManager") };
	AddGameObject(pDiskManager);
	std::vector<DiskManager_Comp::DiskPos> diskPositions{};
	for (const auto& diskdata : disksdata)
		diskPositions.push_back(DiskManager_Comp::DiskPos{ diskdata.Side, diskdata.Row });
	
	pDiskManager->AddComponent(new DiskManager_Comp(diskPositions));
}

void CoopScene::InitGameController()
{
	auto pGameController{ std::make_shared<GameObject>("GameController") };
	AddGameObject(pGameController);
	pGameController->AddComponent(new GameController_Comp());
}