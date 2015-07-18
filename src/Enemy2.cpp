#include <Enemy2.hpp>

#define NAME "Enemy2"
#define WIDTH 3
#define HEIGHT 3
#define SPRITE \
					"|-|"\
					"-| "\
					"|-|"
#define COLORS \
					"YRR"\
					"GWB"\
					"YRR"
#define CURRENT_HP 35
#define ARMOR 5
#define ARMORREGEN 1
#define REDUCTION 2
#define SPEED 100
#define RELOADTIME 2.25f


static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

Enemy2::Enemy2( void ) :
	Ship(NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Enemy2::Enemy2( float posX, float posY, float vecX, float vecY ) :
	Ship(posX, posY, vecX, vecY, NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Enemy2::~Enemy2( void ) {
}

void				Enemy2::shoot( Container & missiles ) {
	if (canShoot()) {
		missiles.push(new Bullet(posX + 12, posY + (-2), -1, -.05));
		// missiles.push(new Bullet(posX - 2, posY + (-1), -1, -.025));
		missiles.push(new Bullet(posX - 2, posY, -1, 0));
		// missiles.push(new Bullet(posX - 2, posY + 1, -1, .025));
		missiles.push(new Bullet(posX + 12, posY + 2, -1, .05));
		lastShoot = getMilliCount() / 1000.f;
	}
}