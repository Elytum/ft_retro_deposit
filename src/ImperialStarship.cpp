#include <ImperialStarship.hpp>

#define NAME "ImperialStarship"
#define WIDTH 24
#define HEIGHT 9
#define SPRITE \
					"[=====>                 "\
					"[  (    _____           "\
					" \\__\\,-'//   `--._      "\
					"  [_/~||,-----.\\@_\\\\___ "\
					"  [_) |||()()()   ~[|||>"\
					"  [_\\_||`-----'   //    "\
					" /  /`-.\\\\___,--'==(-   "\
					"[  (                    "\
					"[=====>                 "
#define COLORS \
					"RRRRRRR                 "\
					"R  R    RRRRR           "\
					" RRRRRRRRRRRRRRRRRRR    "\
					"  RRRRRRRBBBBRRRRRRRRRR "\
					"  RRRRRRBBBBBBRRRRRRRRRR"\
					"  RRRRRRRBBBBRRRRRRR    "\
					" R  RRRRRRRRRRRRRRRRR   "\
					"R  R                    "\
					"RRRRRRR                 "
#define CURRENT_HP 42
#define ARMOR 150
#define ARMORREGEN 1
#define REDUCTION 2
#define SPEED 400
#define RELOADTIME 0.75f


static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

ImperialStarship::ImperialStarship( void ) :
	Ship(NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

ImperialStarship::ImperialStarship( float posX, float posY, float vecX, float vecY ) :
	Ship(posX, posY, vecX, vecY, NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

ImperialStarship::~ImperialStarship( void ) {
}

void				ImperialStarship::shoot( Container & missiles ) {
	if (canShoot()) {
		missiles.push(new PlasmaCanon(posX + 12, posY + (-2), 1, -.05));
		missiles.push(new PlasmaCanon(posX + 15, posY + (-1), 1, -.025));
		missiles.push(new PlasmaCanon(posX + 20, posY + 0, 1, 0));
		missiles.push(new PlasmaCanon(posX + 15, posY + 1, 1, .025));
		missiles.push(new PlasmaCanon(posX + 12, posY + 2, 1, .05));
		lastShoot = getMilliCount() / 1000.f;
	}
}