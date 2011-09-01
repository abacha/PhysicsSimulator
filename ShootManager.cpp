#include "ShootManager.h"

using namespace gs2d;
using namespace math;

ShootManager::ShootManager(PhysicsSimulatorPtr simulator): m_shooting(false) 
{
	m_simulator = simulator;
}

bool ShootManager::isShooting()
{
	return m_shooting;
}

void ShootManager::Shoot(Vector2 playerPos, int turn, Vector2 shootPower)
{
	Vector2 overlay = Vector2(0, 0);
	if (turn == 1)
	{
		overlay.x = -1;
	}
	m_ballIndex = m_simulator->CreateSphere(m_sprite->GetBitmapSizeF().y / 2, playerPos, 0.1f, 0.5f, 0.9f);

	m_shooting = true;
}

void ShootManager::Draw()
{
	if (isShooting())
	{
		m_sprite->Draw(m_simulator->GetPosition(m_ballIndex));
	}
}

void ShootManager::SetSprite(SpritePtr sprite)
{
	m_sprite = sprite;
}