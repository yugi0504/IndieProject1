#pragma once

#include "IScene.hpp"

class TitleScene final : public IScene
{
private:

	SceneId m_nextScene = SceneId::None;

public:

	TitleScene() = default;
	~TitleScene() override = default;

	bool Initialize() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void Finalize() override;

	SceneId  GetNextScene() const noexcept override { return m_nextScene; }
};