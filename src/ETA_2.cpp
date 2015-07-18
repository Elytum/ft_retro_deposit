#include <Eta_2.hpp>

#define NAME "Eta-2 Actis-class interceptor"
#define WIDTH 18
#define HEIGHT 8
#define SPRITE \
          "    ____          "\
          "   /  / \\         "\
          "  |  /() \\______  "\
          " _/ __  ________\\ "\
          "<_ |__| )________ "\
          "  \\       ______/ "\
          "  |  \\   /        "\
          "   \\__\\_/         "
#define COLORS \
          "    YYYY          "\
          "   Y  R Y         "\
          "  Y  RWW YYYYYYY  "\
          " YY BB  YYYYYYYYY "\
          "YY BBBB YYYYYYYYY "\
          "  Y R     YYYYYYY "\
          "  Y  R   Y        "\
          "   YYYRYY         "
#define CURRENT_HP 42
#define ARMOR 5
#define ARMORREGEN 1
#define REDUCTION 2
#define SPEED 650
#define RELOADTIME .5f




static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

Eta_2::Eta_2( void ) :
	Ship(NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Eta_2::Eta_2( float posX, float posY, float vecX, float vecY ) :
     Ship(posX, posY, vecX, vecY, NAME, CURRENT_HP, ARMOR, ARMORREGEN, REDUCTION, SPEED, RELOADTIME, spriteTemplate()) {
}

Eta_2::~Eta_2( void ) {
}

void           Eta_2::shoot( Container & missiles ) {
  if (canShoot()) {
    missiles.push(new PlasmaCanon(posX + 12, posY + (-2), 1, -.05));
    // missiles.push(new PlasmaCanon(posX + 15, posY + (-1), 1, -.025));
    missiles.push(new PlasmaCanon(posX + 20, posY + 0, 1, 0));
    // missiles.push(new PlasmaCanon(posX + 15, posY + 1, 1, .025));
    missiles.push(new PlasmaCanon(posX + 12, posY + 2, 1, .05));
    lastShoot = getMilliCount() / 1000.f;
  }
}
