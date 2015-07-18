#include <AMissile.hpp>

# define DAMAGE 0
# define RELOADTIME 0.f
# define WIDTH 1
# define HEIGHT 1
# define SPRITE "."

# define COLORS "R"


static Sprite* 	spriteTemplate( void ) {
	static const Sprite	cpy = Sprite (WIDTH, HEIGHT, SPRITE, COLORS);

	return (cpy.clone());
}


AMissile::AMissile( float reloadTime, int damage, Sprite const sprite ) :
					Entity(0, 0, 0, sprite.clone()), damage(damage), reloadTime(reloadTime) {
}

AMissile::AMissile( void ) :
					Entity(0, 0, 0, spriteTemplate()), damage(DAMAGE), reloadTime(RELOADTIME) {
}

AMissile::AMissile( float posX, float posY, float vecX, float vecY, float speed, float reloadTime, int damage, Sprite const sprite ) :
					Entity(posX, posY, vecX, vecY, speed, sprite.clone()), damage(damage), reloadTime(reloadTime) {
}

AMissile::AMissile( AMissile const & cpy ) : Entity(0, 0, 0, spriteTemplate())	{
	(*this) = cpy;
}

AMissile::~AMissile(void) {
}

float			AMissile::getReloadTime() const{
	return (reloadTime);
}

int				AMissile::getDamage() const{
	return (damage);
}

AMissile&		AMissile::operator=(AMissile const & arg) {
	reloadTime = arg.getReloadTime();
	damage = arg.getDamage();
	sprite = arg.getSprite();
	return (*this);
}

std::ostream	&operator<<(std::ostream& flux, const AMissile& arg) {
	flux	<< "ReloadTime: " << arg.getReloadTime()
			<< ", deals: " << arg.getDamage()
		<< std::endl;
	return (flux);
}
