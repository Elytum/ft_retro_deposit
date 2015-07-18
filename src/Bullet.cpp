#include <Bullet.hpp>

#define DAMAGE 10
#define RELOADTIME 2.f
#define SPEED 300
#define WIDTH 2
#define HEIGHT 1
#define SPRITE \
					"<*"

#define COLORS \
					"RB"

static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

Bullet::Bullet( void ) : AMissile(RELOADTIME, DAMAGE, spriteTemplate()) {
}

Bullet::Bullet( float posX, float posY, float vecX, float vecY ) : AMissile(posX, posY, vecX, vecY, SPEED, RELOADTIME, DAMAGE, spriteTemplate()) {
}

Bullet::~Bullet( void ) {
}
