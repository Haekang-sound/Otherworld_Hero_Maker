#include "GameEngineDemo.h"

// Engine
#include "../DirectY/DirectY.h"
#include "WinAPIInit.h"

// Managers
#include "GameEngine.h"
#include "SoundManager.h"
#include "TileManager.h"
#include "InputManager.h"

// temp �ӽ�
#include "Scene.h"
#include "Animator.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Link.h"
#include "Button.h"
#include "Slider.h"

#include "Player.h"


/// Temp �ӽ� Test��
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

GameEngineDemo::GameEngineDemo() 
	:m_hWnd(NULL), m_winAPIInit(nullptr),
	m_directY(nullptr),
	m_gameEngine(nullptr)
{

}

GameEngineDemo::~GameEngineDemo()
{

}

void GameEngineDemo::Init(HINSTANCE hInstance)
{
	// Window and graphics engine Init
	m_winAPIInit = new WinAPIInit;
	m_hWnd = m_winAPIInit->Init(hInstance);

	m_directY = new DirectY(m_hWnd);

	// Manager Init
	m_gameEngine = new GameEngine;
	m_gameEngine->Init(m_hWnd, m_directY);
	
	Scene* thisScene = m_gameEngine->CreateScene("GameScene");
	m_gameEngine->LoadScene("GameScene");

	//test camera
	GameObject* testCamera = m_gameEngine->CreateObject("Camera", thisScene);

	Transform* cameraTransform = new Transform();
	testCamera->SetElement(cameraTransform, ElementType::Transform);

	Camera* testCameraScript = new Camera();
	testCamera->SetElement(testCameraScript, ElementType::Script);
	
	Button* testButton = new Button(0, 100, 0, 100);
	testCamera->SetElement(testButton, ElementType::Button);
	testButton->SetOnClick([=]() {cameraTransform->Translate(10); });
	testButton->SetOnPressed([=]() {cameraTransform->Translate({0, 5}); });

	//�÷��̾� ����
	GameObject* tileManager = m_gameEngine->CreateObject("TileManager", thisScene);
	Transform* tileManagerTransform = new Transform();
	tileManager->SetElement(tileManagerTransform, ElementType::Transform);
	TileManager* tileManagerScript = new TileManager(m_gameEngine, m_directY);
	tileManager->SetElement(tileManagerScript, ElementType::Script);
	tileManagerTransform->SetParent(cameraTransform);

	GameObject* testObject = m_gameEngine->CreateObject("Link", thisScene);

	Animator* testAnimator = new Animator();
	Transform* testTransform = new Transform();
	Link* testLink = new Link();

	//2023.08.01 ����϶� �츮 ������!!
	Graphics::Motion* testMotion = new Graphics::Motion();
	m_directY->ReadSpriteTxtFile("link_walk_front", m_gameEngine->GetImage("link"), testMotion);
	testAnimator->AddMotion("link", testMotion);

	//testObject->SetElement(testAnimator, ElementType::Animator);
	testObject->SetElement(testTransform, ElementType::Transform);
	testObject->SetElement(testLink, ElementType::Script);
	testTransform->SetParent(cameraTransform);
	testTransform->SetLayer(5);

	GameObject* playerObject = m_gameEngine->CreateObject("Player", thisScene);
	Transform* playerTransform = new Transform();
	playerObject->SetElement(playerTransform, ElementType::Transform); ///ī�޶� �÷��̾� ���� �̵���
	Player* playerScript = new Player();
	playerObject->SetElement(playerScript, ElementType::Script);

	// �����̴� �ϼ�
	/*GameObject* testSlider = m_gameEngine->CreateObject("Slider", thisScene);
	Transform* sliderTransform = new Transform();
	testSlider->SetElement(sliderTransform, ElementType::Transform);

	Graphics::Sprite* handle = m_directY->ReadSpriteTxtFile("handle", m_gameEngine->GetImage("handle"));
	Graphics::Sprite* back = m_directY->ReadSpriteTxtFile("back", m_gameEngine->GetImage("back"));
	Graphics::Sprite* area = m_directY->ReadSpriteTxtFile("area", m_gameEngine->GetImage("area"));
	Slider* slider = new Slider((int)back->m_drawSize.left, (int)back->m_drawSize.right, (int)back->m_drawSize.top, (int)back->m_drawSize.bottom,
		((int)(back->m_drawSize.left + back->m_drawSize.right) / 2), (int)((back->m_drawSize.top + back->m_drawSize.bottom) / 2));

	slider->SetHandle(handle);
	slider->SetBackground(back);
	slider->SetFillArea(area);
	testSlider->SetElement(slider, ElementType::Script);*/

	////��� ����
	//GameObject* heroObject = m_sceneManager->GetCurrentScene()->CreateObject("Hero");
	//Transform* heroTransform = new Transform();
	//heroObject->SetElement(heroTransform, ElementType::Transform);
	//Hero* heroScript = new Hero();
	//heroScript->
	

	//�ù� ����


	//���� ����


	//���� ����

}

void GameEngineDemo::Loop()
{
	MSG windowsMessage = {};
	while (true)
	{
		// Update
		windowsMessage = m_winAPIInit->ProcessMessage();

		if (windowsMessage.message == WM_QUIT)
		{
			break;
		}

		Update();
		Render();
	}
}

void GameEngineDemo::Release()
{
	// Engine Release
	delete m_gameEngine;
	delete m_directY;

	delete m_winAPIInit;
}

void GameEngineDemo::FixedUpdate()
{

}

void GameEngineDemo::Update()
{

	// Manager Update
	m_gameEngine->Update();
	
	/// ������ Scene���� �־�� ��
	if (InputManager::GetInstance().IsGetKeyUp('Q'))
	{
		// BGM���
		SoundManager::GetInstance().PlayBack(m_gameEngine->GetSound("PowerRanger"),1,PlayType::BGM);

// 		char buffer[100];
// 		sprintf(buffer, "%f, %d", m_timeManager->GetDeltaTime(), m_timeManager->GetFps());
// 		wchar_t wtext[100]; mbstowcs(wtext, buffer, strlen(buffer) + 1);

// 	/// ������ Scene���� �־�� ��
// 	if (InputManager::GetInstance().IsGetKeyUp('Q'))
// 	{
// 		// BGM���
// 		SoundManager::GetInstance().PlayBackBGM(SoundManager::GetInstance().GetCurrentBGM());
// 		char buffer[100];
// 		sprintf(buffer, "%f, %d", m_timeManager->GetDeltaTime(), m_timeManager->GetFps());
// 		wchar_t wtext[100]; mbstowcs(wtext, buffer, strlen(buffer) + 1);
// 
// 		SetWindowText(m_hWnd, wtext);
// 
// 		SoundManager::GetInstance().PlayBackBGM(m_resourceManager->GetSound("BGM"));
// 	}
		//SetWindowText(m_hWnd, wtext);
	}

	if (InputManager::GetInstance().IsGetKeyUp(VK_LBUTTON))
	{
		// SFX���
		SoundManager::GetInstance().PlayBack(m_gameEngine->GetSound("swish"));
		char buffer[100];
		sprintf(buffer, "%d, %d", (int)InputManager::GetInstance().GetMousePosition().x, (int)InputManager::GetInstance().GetMousePosition().y);
		wchar_t wtext[100]; mbstowcs(wtext, buffer, strlen(buffer) + 1);

		SetWindowText(m_hWnd, wtext);
	}
	/// Ű���� ����
	
	//esc ������ ����
	if (InputManager::GetInstance().IsGetKeyUp(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (InputManager::GetInstance().IsGetKeyUp(VK_LBUTTON))
	{
		
// 		// SFX���
// 		char buffer[100];
// 		//sprintf(buffer, "%d", SoundManager::GetInstance().a());
// 		wchar_t wtext[100]; mbstowcs(wtext, buffer, strlen(buffer) + 1);

	}
	if (InputManager::GetInstance().IsGetKeyDown('A'))
	{
		SoundManager::GetInstance().PlayBack(m_gameEngine->GetSound("drumloop"),1,PlayType::BGM);
	}
	if (InputManager::GetInstance().IsGetKeyDown('S'))
	{
		SoundManager::GetInstance().PlayBack(m_gameEngine->GetSound("Rolling"));
	}

	if (InputManager::GetInstance().IsGetKeyUp(VK_RBUTTON))
	{
		//�Ͻ������� ���带 �����
		SoundManager::GetInstance().StopSound();
	}


	if (InputManager::GetInstance().IsGetKeyUp('X'))
	{
		// ���� �Ͻ�����
		SoundManager::GetInstance().PauseSound();
	}
	if (InputManager::GetInstance().IsGetKeyUp('Z'))
	{
		// ���� ����
		SoundManager::GetInstance().PauseSoundPlay();
	}


	if (InputManager::GetInstance().IsGetKeyUp('X'))
	{
		// ���� �Ͻ�����
		SoundManager::GetInstance().PauseSound();
	}
	if (InputManager::GetInstance().IsGetKeyUp('Z'))
	{
		// ���� ����
		//SoundManager::GetInstance().PauseSoundPlay();
		SoundManager::GetInstance().ChannelGroupVolume(ChannalGroups::BGM, 0.1f);

	}
}

void GameEngineDemo::LateUpdate()
{

}

void GameEngineDemo::PreRender()
{

}

void GameEngineDemo::Render()
{
	// Render�� �����Ϸ��� �ʿ���
	m_directY->BeginDraw();

	// Render
	m_directY->SetTransform({ 1,0,0,1,0,0 });
	m_directY->CleanWindow();
	m_directY->SetBrushColor(1, 0, 0, 1);
	m_directY->DrawRectangle({ 0, 0, 100, 100 });

	m_gameEngine->Render(m_directY);

	// Render�� ���� �� ���, Back Buffer�� �ҷ����� �۾��� ��
	m_directY->EndDraw();
}

void GameEngineDemo::PostRender()
{

}
