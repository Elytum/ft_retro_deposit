#include <Enemy.hpp>

#define NAME "Enemy"
#define WIDTH 3
#define HEIGHT 3
#define SPRITE \
					" **"\
					"<()"\
					" **"
#define COLORS \
					" RR"\
					"GWB"\
					" RR"
#define CURRENT_HP 25
#define ARMOR 5
#define ARMORREGEN 1
#define REDUCTION 2
#define SPEED 200
#define RELOADTIME 3.f


static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

Enemy::Enemy( void ) :
	Ship(NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Enemy::Enemy( float posX, float posY, float vecX, float vecY ) :
	Ship(posX, posY, vecX, vecY, NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Enemy::~Enemy( void ) {
}

void				Enemy::shoot( Container & missiles ) {
	if (canShoot()) {
		// missiles.push(new Bullet(posX + 12, posY + (-2), -1, -.05));
		missiles.push(new Bullet(posX + 15, posY + (-1), -1, -.025));
		// missiles.push(new Bullet(posX - 2, posY, -1, 0)); missiles.push(new Bullet(posX - 5, posY, -1, 0));
		missiles.push(new Bullet(posX + 15, posY + 1, -1, .025));
		// missiles.push(new Bullet(posX + 12, posY + 2, -1, .05));
		lastShoot = getMilliCount() / 1000.f;
	}
}