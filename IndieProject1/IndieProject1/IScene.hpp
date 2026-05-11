#pragma once
#include "SceneId.hpp"

class IScene
{
public:
	virtual ~IScene() = default;

	virtual bool Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;

	virtual SceneId GetNextScene() const noexcept = 0;
};