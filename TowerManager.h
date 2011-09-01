#ifndef TOWERMANAGER_H_
#define TOWERMANAGER_H_

#include "PhysicsSimulator.h"
#include "SpriteManager.h"
#include <boost/shared_ptr.hpp>
#include <vector>

class Tower
{
	private:
		gs2d::math::Rect2Df rect2Df;
		gs2d::math::Vector2 pos;
		gs2d::SpritePtr sprite;
	public:		
		Tower(PhysicsSimulatorPtr simulator, gs2d::SpritePtr sprite, gs2d::math::Rect2Df rect2Df, gs2d::math::Vector2 pos);
		gs2d::math::Rect2Df GetRect2Df();
		gs2d::SpritePtr GetSprite();
		gs2d::math::Vector2 GetPos();
};
typedef boost::shared_ptr<Tower> TowerPtr;


class TowerManager
{
	private:
		std::vector<TowerPtr> m_towers;
		static const int MAX_TOWERS;
		static const gs2d::math::Vector2 BLOCK_SIZE;
	public:
		void AddTowers(PhysicsSimulatorPtr simulator, gs2d::SpritePtr sprite);
		TowerPtr GetTower(int index);
		int GetNextTowerId();
		static int GetMaxTowers();
		static gs2d::math::Vector2 GetBlockSize();
		void Draw();
};
typedef boost::shared_ptr<TowerManager> TowerManagerPtr;

#endif
