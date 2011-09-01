#include "TowerManager.h"
using namespace gs2d;
using namespace math;
const Vector2 TowerManager::BLOCK_SIZE = Vector2(64.0f, 16.0f);
const int TowerManager::MAX_TOWERS = 20;

int TowerManager::GetMaxTowers()
{
	return MAX_TOWERS;
}

Vector2 TowerManager::GetBlockSize()
{
	return BLOCK_SIZE;
}

void TowerManager::Draw()
{
	for (std::size_t i = 0; i < m_towers.size(); i++)
	{
		m_towers[i]->GetSprite()->SetRect(m_towers[i]->GetRect2Df());
		m_towers[i]->GetSprite()->Draw(m_towers[i]->GetPos());
	}
	
}

void TowerManager::AddTowers(PhysicsSimulatorPtr simulator, SpritePtr sprite)
{
	for (std::size_t i = 0; i < MAX_TOWERS; i++)
	{
		float height = (1 + math::Randomizer::Int((sprite->GetBitmapSizeF().y / BLOCK_SIZE.y) - 1)) * BLOCK_SIZE.y;
		Rect2Df rect2Df = Rect2Df(Vector2(0, 0), Vector2(sprite->GetBitmapSizeF().x, height));
		Vector2 pos = Vector2(sprite->GetBitmapSizeF().x * static_cast<float>(i), 0);
		m_towers.push_back(TowerPtr(new Tower(simulator, sprite, rect2Df, pos)));
	}
}

TowerPtr TowerManager::GetTower(int index)
{
	return m_towers[index];
}

SpritePtr Tower::GetSprite()
{
	return sprite;
}

Vector2 Tower::GetPos()
{
	return pos;
}

Rect2Df Tower::GetRect2Df()
{
	return rect2Df;
}


int TowerManager::GetNextTowerId()
{
	return sizeof(m_towers) + 1;
}

Tower::Tower(PhysicsSimulatorPtr simulator, SpritePtr sprite, Rect2Df rect2Df, Vector2 pos)
{
	simulator->CreatePolygon(rect2Df, 0.0f, 1.0f, 0.0f, 0.0f);
	this->sprite = sprite;
	this->rect2Df = rect2Df;
	this->pos = pos;
}