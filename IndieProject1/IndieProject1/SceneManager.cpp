#include "SceneManager.hpp"

#include "TitleScene.hpp"
#include "TutorialScene.hpp"
#include "GameScene.hpp"
#include "ResultScene.hpp"

bool SceneManager::Initialize(SceneId fistScene)
{
	return ChangeScene(fistScene);
}

void SceneManager::Update(float deltaTime)
{
	if (!m_currentScene) return;

	m_currentScene->Update(deltaTime);

	const SceneId next = m_currentScene->GetNextScene();

	if (next == SceneId::Exit)
	{
		m_isExitRequested = true;
		return;
	}

	if (next != SceneId::None && next != m_currentSceneId)
	{
		ChangeScene(next);
	}

}

void SceneManager::Draw()
{
	if (m_currentScene)
	{
		m_currentScene->Draw();
	}
}

void SceneManager::Finalize()
{
	if (m_currentScene)
	{
		m_currentScene->Finalize();
		m_currentScene.reset();
	}

	m_currentSceneId = SceneId::None;
}

bool SceneManager::ChangeScene(SceneId nextScene)
{
	if (m_currentScene)
	{
		m_currentScene->Finalize();
		m_currentScene.reset();
	}

	m_currentScene = CreateScene(nextScene);

	if (!m_currentScene)
	{
		return false;
	}

	if (!m_currentScene->Initialize())
	{
		m_currentScene.reset();
		return false;
	}

	m_currentSceneId = nextScene;
	return true;
}

std::unique_ptr<IScene> SceneManager::CreateScene(SceneId sceneId)
{
	switch (sceneId)
	{
	case SceneId::Title:
		return std::make_unique<TitleScene>();
	
	case SceneId::Tutorial:
		return std::make_unique<TutorialScene>();

	case SceneId::Game:
		return std::make_unique<GameScene>();

	case SceneId::Result:
		return std::make_unique<ResultScene>();

	default:
		return nullptr;

	}
}