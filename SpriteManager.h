#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include "../gs2d/src/gs2dframework.h"
#include <map>

class SpriteManager
{
	public:
		static const gs2d::str_type::string SPRITE_DEFAULT_PATH;
		gs2d::SpritePtr GetSprite(const gs2d::str_type::string &filename);
		void AddSprite(gs2d::VideoPtr video, const gs2d::str_type::string &filename, gs2d::math::Vector2 origin = gs2d::math::Vector2(0, 0));
	private:
		std::map<gs2d::str_type::string, gs2d::SpritePtr> m_sprites;
};
typedef boost::shared_ptr<SpriteManager> SpriteManagerPtr;

#endif