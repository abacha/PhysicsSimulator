#ifndef SHOOTMANAGER_H_
#define SHOOTMANAGER_H_

#include "PhysicsSimulator.h"

class ShootManager
{
	private:
		bool m_shooting;
		int m_ballIndex;
		PhysicsSimulatorPtr m_simulator;
		gs2d::SpritePtr m_sprite;
	public:
		ShootManager(PhysicsSimulatorPtr simulator);
		bool isShooting();
		void Shoot(gs2d::math::Vector2 playerPos, int turn, gs2d::math::Vector2 shootPower);
		void SetSprite(gs2d::SpritePtr sprite);
		void Draw();
};
typedef boost::shared_ptr<ShootManager> ShootManagerPtr;

#endif