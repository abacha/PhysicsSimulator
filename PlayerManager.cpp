#include "PlayerManager.h"

using namespace gs2d;
using namespace math;
PlayerManager::PlayerManager(PhysicsSimulatorPtr simulator)
{
	m_simulator = simulator;
	simulator->SetContactListener(this);
}

inline bool IsInArea(const gs2d::math::Vector2& pos, const gs2d::math::Rect2Df& area, const gs2d::math::Vector2& origin, VideoPtr video)
{
	const gs2d::math::Vector2 offset = area.size * origin * -1.0f;	
	float tmp1 = video->GetScreenSizeF().y - area.pos.y + offset.y - area.size.y / 2;
	float tmp2 = video->GetScreenSizeF().y - area.pos.y + area.size.y + offset.y - area.size.y / 2;
	if (pos.x < area.pos.x + offset.x || pos.x > area.pos.x + area.size.x + offset.x
		|| pos.y < area.pos.y + offset.y || pos.y > area.pos.y + area.size.y + offset.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline Vector2 GetAbsolutePos(InputPtr input, VideoPtr video)
{
	return input->GetTouchPos(0, video) + video->GetCameraPos();
}

void PlayerManager::Update(VideoPtr video, InputPtr input, ShootManagerPtr shootManager, SpritePtr playerSprite, SpritePtr shootSprite)
{
	static Vector2 hitPos, releasePos;
	static int turn = 0;
	if (input->GetTouchState(0) == GSKS_HIT)
	{	
		if (IsInArea(GetAbsolutePos(input, video), Rect2Df(GetPlayer(turn)->GetPos(), playerSprite->GetRect().size), Vector2(0.5f, 0.5f), video))
		{
			hitPos = input->GetTouchPos(0, video);
		}
		else
		{
			hitPos = GS_NO_TOUCH;
		}
	}
	if (input->GetTouchState(0) == GSKS_DOWN)
	{
		releasePos = hitPos - input->GetTouchPos(0, video);
	}
	if (input->GetTouchState(0) == GSKS_RELEASE && hitPos != GS_NO_TOUCH)
	{
		{
			Vector2 pos = m_simulator->GetPosition(GetPlayer(turn)->GetBodyId());
			shootManager->Shoot(pos, turn, releasePos);
			turn = !turn;
		}
	}
	if (hitPos == GS_NO_TOUCH)
	{
		video->MoveCamera(input->GetTouchMove(0) * -1);
	}
}

void PlayerManager::AddPlayers(std::vector<SpritePtr> sprites, TowerManagerPtr towerManager)
{			
	for (size_t i = 0; i < sprites.size(); i++)
	{
		int tower = (i * towerManager->GetMaxTowers() / sprites.size() + math::Randomizer::Int(towerManager->GetMaxTowers() / sprites.size())) - i;
		float height = towerManager->GetTower(tower)->GetRect2Df().size.y / 2;
		height += sprites[i]->GetRect().size.y / 2;
		Vector2 pos = Vector2(towerManager->GetBlockSize().x * tower, height * -1);
		m_players.push_back(PlayerPtr(new Player(m_simulator, sprites[i], pos)));
	}
}

PlayerPtr PlayerManager::GetPlayer(int index)
{
	return m_players[index];
}

Player::Player(PhysicsSimulatorPtr simulator, SpritePtr sprite, Vector2 pos)
{
	Rect2Df newSize = sprite->GetRect();
	newSize.size *= 0.95f;
	m_sprite = sprite;
	m_pos = pos;
	m_bodyId = simulator->CreatePolygon(Rect2Df(Vector2(pos.x, pos.y + sprite->GetRect().size.y / 2), newSize.size), 1.0f);	
}

gs2d::math::Vector2 Player::GetPos()
{
	return m_pos;
}

int Player::GetBodyId()
{
	return m_bodyId;
}


gs2d::SpritePtr Player::GetSprite()
{
	return m_sprite;
}


void PlayerManager::BeginContact(b2Contact* contact)
{ 
	/*static int start = 0;

	if (contact->GetFixtureA() == m_players[0]->GetBody()->GetFixtureList() || contact->GetFixtureB() == m_players[0]->GetBody()->GetFixtureList() && start > 1)
	{
		if (contact->GetFixtureA() == m_players[0]->GetBody()->GetFixtureList())
		{
			//destroy B
		}
		else
		{
			//destroy A
		}
		std::cout << "hit player 0" << std::endl;		
		start++;
	}
	if (contact->GetFixtureA() == m_players[1]->GetBody()->GetFixtureList() || contact->GetFixtureB() == m_players[1]->GetBody()->GetFixtureList() && start > 1)
	{
		std::cout << "hit player 1" << std::endl;
		start++;
	}*/
}

void PlayerManager::Draw()
{
	for (std::size_t i = 0; i < m_players.size(); i++)
	{
		//std::cout << m_players[i]->GetBodyId() << std::endl;
		m_players[i]->GetSprite()->Draw(m_players[i]->GetPos());
	}
	
}