#include "SpriteManager.h"
using namespace gs2d;
using namespace math;

const str_type::string SpriteManager::SPRITE_DEFAULT_PATH = GS_L("assets/textures/");

gs2d::SpritePtr SpriteManager::GetSprite(const str_type::string &filename)
{
	std::map<str_type::string, SpritePtr>::iterator iter = m_sprites.find(filename);
	if (iter != m_sprites.end())
	{
		return iter->second;
	}
	else
	{
		return SpritePtr();
	}
}
void SpriteManager::AddSprite(VideoPtr video, const str_type::string &filename, Vector2 origin)
{
	SpritePtr sprite = video->CreateSprite(SPRITE_DEFAULT_PATH + filename);
	sprite->SetOrigin(origin);	
	m_sprites[filename] = sprite;
}