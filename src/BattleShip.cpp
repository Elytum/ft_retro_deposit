#include <BattleShip.hpp>

# define NAME "BattleShip"
# define WIDTH 15
# define HEIGHT 5
# define SPRITE \
       "|\\       a     "\
       "| \\            "\
       "=[_|H)--._____ "\
       "=[+--,-------' "\
       " [|_/\"\"        "
# define COLORS \
       "RR       YY    "\
       "R R            "\
       "BBBBHBBBBBBBBB "\
       "BBBBBBBBBBBBB' "\
       " BBBBRR        "
# define CURRENT_HP 42
# define ARMOR 5
# define ARMORREGEN 1
# define REDUCTION 2
# define SPEED 1000
# define RELOADTIME .25










static Sprite 	spriteTemplate( void ) {
  static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

BattleShip::BattleShip( void ) :
	Ship(NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate())      {
}

BattleShip::BattleShip( float posX, float posY, float vecX, float vecY ) :
       Ship(posX, posY, vecX, vecY, NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate())       {
}

BattleShip::~BattleShip( void ) {
}

void        BattleShip::shoot( Container & missiles ) {
  if (canShoot()) {
    // missiles.push(new PlasmaCanon(posX + 12, posY + (-2), 1, -.05));
    // missiles.push(new PlasmaCanon(posX + 15, posY + (-1), 1, -.025));
    missiles.push(new PlasmaCanon(posX + 20, posY + 0, 1, 0));
    // missiles.push(new PlasmaCanon(posX + 15, posY + 1, 1, .025));
    // missiles.push(new PlasmaCanon(posX + 12, posY + 2, 1, .05));
    lastShoot = getMilliCount() / 1000.f;
  }
}
