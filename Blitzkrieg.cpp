#include "Blitzkrieg.h" 

using namespace gs2d;
using namespace math;

gs2d::BaseApplicationPtr gs2d::CreateBaseApplication()
{
	return BaseApplicationPtr(new Blitzkrieg);
}

Blitzkrieg::Blitzkrieg()
{
	m_simulator = PhysicsSimulatorPtr(new PhysicsSimulator(Vector2(0.0f, 98), true));
	m_playerManager = PlayerManagerPtr(new PlayerManager(m_simulator));
	m_spriteManager = SpriteManagerPtr(new SpriteManager());
	m_towerManager = TowerManagerPtr(new TowerManager());
	m_shootManager = ShootManagerPtr(new ShootManager(m_simulator));
}

void Blitzkrieg::Start(VideoPtr video, InputPtr input, AudioPtr audio)
{
	m_video = video;
	m_input = input;

	m_video->SetCameraPos(Vector2(0, m_video->GetScreenSizeF().y * -1));
	
	m_spriteManager->AddSprite(m_video, GS_L("brick.png"), Vector2(0.5f, 0.5f));
	m_towerManager->AddTowers(m_simulator, m_spriteManager->GetSprite(GS_L("brick.png")));

	m_spriteManager->AddSprite(video, GS_L("ball.png"), Vector2(0.5f, 0.5f));
	m_shootManager->SetSprite(m_spriteManager->GetSprite(GS_L("ball.png")));

	m_spriteManager->AddSprite(video, GS_L("viking.png"), Vector2(0.5f, 0.5f));
	m_spriteManager->AddSprite(video, GS_L("zombie.png"), Vector2(0.5f, 0.5f));
		
	SpritePtr vikingSprite = m_spriteManager->GetSprite(GS_L("viking.png"));
	vikingSprite->SetupSpriteRects(4, 4);
	vikingSprite->SetRect(1, 2);

	SpritePtr zombieSprite = m_spriteManager->GetSprite(GS_L("zombie.png"));
	zombieSprite->SetupSpriteRects(4, 4);
	zombieSprite->SetRect(1, 1);


	std::vector<SpritePtr> sprites;
	sprites.push_back(vikingSprite);
	sprites.push_back(zombieSprite);
	m_playerManager->AddPlayers(sprites, m_towerManager);
}

Application::APP_STATUS Blitzkrieg::Update(unsigned long lastFrameDeltaTimeMS)
{	
	m_playerManager->Update(m_video, m_input, m_shootManager, m_spriteManager->GetSprite(GS_L("viking.png")), m_spriteManager->GetSprite(GS_L("ball.png")));	
	m_simulator->Step((float)lastFrameDeltaTimeMS / 1000.0f);
	return Application::APP_OK;
}

void Blitzkrieg::RenderFrame()
{
	m_video->BeginSpriteScene(0xFFFFFFFF);
 	m_towerManager->Draw();
	m_playerManager->Draw();
	m_shootManager->Draw();
	m_video->EndSpriteScene();
}


void Blitzkrieg::Destroy()
{
}