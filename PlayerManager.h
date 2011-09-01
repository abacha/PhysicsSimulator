#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include "PhysicsSimulator.h"
#include "SpriteManager.h"
#include "ShootManager.h"
#include "TowerManager.h"
#include <boost/shared_ptr.hpp>
#include <vector>

class Player
{
	private:
		gs2d::math::Vector2 m_pos;
		gs2d::SpritePtr m_sprite;
		int m_bodyId;
	public:
		Player(PhysicsSimulatorPtr simulator, gs2d::SpritePtr sprite, gs2d::math::Vector2 pos);
		gs2d::math::Vector2 GetPos();
		gs2d::SpritePtr GetSprite();
		int GetBodyId();
};
typedef boost::shared_ptr<Player> PlayerPtr;

class PlayerManager : public b2ContactListener
{
	private:
		std::vector<PlayerPtr> m_players;
		PhysicsSimulatorPtr m_simulator;
	public:
		PlayerManager(PhysicsSimulatorPtr simulator);
		void AddPlayers(std::vector<gs2d::SpritePtr> sprites, TowerManagerPtr towerManager);
		PlayerPtr GetPlayer(int index);
		void BeginContact(b2Contact* contact);
		void Update(gs2d::VideoPtr video, gs2d::InputPtr input, ShootManagerPtr shootManager, gs2d::SpritePtr playerSprite, gs2d::SpritePtr shootSprite);
		void Draw();
};
typedef boost::shared_ptr<PlayerManager> PlayerManagerPtr;

#endif