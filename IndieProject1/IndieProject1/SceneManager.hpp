#pragma once
#include <memory>

#include "IScene.hpp"
#include "SceneId.hpp"

class SceneManager
{
private:
	std::unique_ptr<IScene>m_currentScene = nullptr;
	SceneId m_currentSceneId = SceneId::None;

	bool m_isExitRequested = false;

public:
	SceneManager() = default;
	~SceneManager() = default;

	bool Initialize(SceneId firstScene);
	void Update(float deltaTime);
	void Draw();
	void Finalize();

	bool IsExitRequested() const noexcept { return m_isExitRequested; }

private:

	bool ChangeScene(SceneId nextScene);
	std::unique_ptr<IScene> CreateScene(SceneId sceneId);

};