#ifndef BLITZKRIEG_H_
#define BLITZKRIEG_H_

#include "../gs2d/src/gs2dframework.h"
#include "PhysicsSimulator.h"
#include "SpriteManager.h"
#include "TowerManager.h" 
#include "PlayerManager.h" 
#include <vector>

namespace gs2d {
class Blitzkrieg : public BaseApplication
{
	VideoPtr m_video;
	InputPtr m_input;
	PhysicsSimulatorPtr m_simulator;
	SpriteManagerPtr m_spriteManager;
	TowerManagerPtr m_towerManager;
	ShootManagerPtr m_shootManager;
	PlayerManagerPtr m_playerManager;

public:
	Blitzkrieg();
	void Start(VideoPtr video, InputPtr input, AudioPtr audio);
	Application::APP_STATUS Update(unsigned long lastFrameDeltaTimeMS);
	void RenderFrame();
	void Destroy();
};
} //namespace gs2d

#endif