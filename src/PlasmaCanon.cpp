#include <PlasmaCanon.hpp>

#define DAMAGE 10
#define RELOADTIME 1.f
#define SPEED 3500
#define WIDTH 13
#define HEIGHT 4
#define SPRITE \
					"  	 __       "\
					"    \\ \\_____ "\
					" ###[==_____>"\
					"    /_/      "

#define COLORS \
					"  	 RR       "\
					"    RRRRRRRR "\
					" RRYYYYYYYYRR"\
					"    RRR      "

static Sprite 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy);
}

PlasmaCanon::PlasmaCanon( void ) : AMissile(RELOADTIME, DAMAGE, spriteTemplate()) {
}

PlasmaCanon::PlasmaCanon( float posX, float posY, float vecX, float vecY ) : AMissile(posX, posY, vecX, vecY, SPEED, RELOADTIME, DAMAGE, spriteTemplate()) {
}

PlasmaCanon::~PlasmaCanon( void ) {
}
