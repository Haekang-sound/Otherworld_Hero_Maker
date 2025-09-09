#include "SceneManager.h"
#include "ResourceManager.h"

#include "Scene.h"

#include "../DirectY/DirectY.h"

#include "SoundManager.h"

SceneManager::SceneManager()
	: m_currentScene(nullptr), m_nextScene(nullptr), m_scenes(),
	m_resourceManager(nullptr), m_preScene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Init(ResourceManager* resourceManager)
{
	// ���ҽ��� �ҷ����� ���� ��� ������ ������ �ִ´�. �����...
	m_resourceManager = resourceManager;
}

void SceneManager::FixedUpdate()
{
	m_currentScene->FixedUpdate();
}

void SceneManager::Update(float deltaTime)
{
	m_currentScene->Update(deltaTime);
}

void SceneManager::LateUpdate()
{
	//m_currentScene->LateUpdate();
	if (m_nextScene != nullptr)
	{
		LoadScene(m_nextScene->GetName());
	}
}

void SceneManager::PreRender()
{
	m_currentScene->PreRender();
}

void SceneManager::Render(DirectY* directY)
{
	m_currentScene->Render(directY);
}

void SceneManager::PostRender(DirectY* directY)
{
	m_currentScene->PostRender(directY);
}

void SceneManager::Release()
{
	// ResourceManager�� directY������ GameProcess���� �����Ѵ�.
	for (auto& scene : m_scenes)
	{
		delete scene.second;
	}
	m_scenes.clear();
}

void SceneManager::LoadScene(std::string sceneName)
{
	static int loadCount = 0;

	// ù �ε尡 �ƴϸ�
	if (loadCount > 0)
	{
		// �� ���� -> �߰����� ó���� �ʿ��ϴ�. ���� �̿ϼ�
		m_currentScene->DeleteAllObject();
		// ���� ���� ���ҽ��� �޸𸮿��� �����Ѵ�.
		m_resourceManager->Release();
	}
	
	m_preScene = m_currentScene;

	// ���� �� ����
/*	SoundManager::GetInstance().StopSound();*/
	m_currentScene = m_scenes[sceneName];
	m_sceneInitFunctions[sceneName]();

	m_currentScene->Init();

	m_nextScene = nullptr;

	loadCount++;
}

void SceneManager::CreateScene(std::string sceneName, std::function<void()> initFunction)
{
	Scene* newScene = new Scene(sceneName);
	m_scenes[sceneName] = newScene;
	m_sceneInitFunctions[sceneName] = initFunction;
}

Scene* SceneManager::FindScene(std::string sceneName)
{
	return m_scenes[sceneName];
}
