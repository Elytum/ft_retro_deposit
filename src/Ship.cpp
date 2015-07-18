#include <Ship.hpp>
#include <Tools.hpp>

std::string		Ship::getName( void ) const {
	return name;
}

int				Ship::getHP( void ) const {
	return HP;
}

int				Ship::getArmor( void ) const {
	return armor;
}

int				Ship::getArmorRegen( void ) const {
	return armorRegen;
}

int				Ship::getReduction( void ) const {
	return reduction;
}

void			Ship::takeDamage( int attack ) {	
	attack -= reduction;
	if (attack < 0)
		return ;
	armor -= attack;
	if (armor >= 0)
		return ;
	HP += armor;
	armor = 0;
}

Ship::Ship( std::string const & name, int hp, int armor, int armorregen,
	int reduction, int speed, float reload, Sprite const & sprite ) : Entity (0, 0, speed, sprite.clone()),
	name(name), HP(hp), maxHP(HP), armor(armor), armorRegen(armorregen),
	reduction(reduction), reload(reload) {
}

Ship::Ship( float posX, float posY, float vecX, float vecY,
				std::string const & name, int hp, int armor, int armorregen,
				int reduction, float speed, float reload, Sprite const & sprite ) :
	Entity (posX, posY, vecX, vecY, speed, sprite.clone()),
	name(name), HP(hp), maxHP(HP), armor(armor), armorRegen(armorregen),
	reduction(reduction), reload(reload) {
}
Ship&				Ship::operator=(Ship const & arg)	{
	this->name = arg.getName();
	this->HP = arg.getHP();
	this->armor = arg.getArmor();
	this->armorRegen = arg.getArmorRegen();
	this->reduction = arg.getReduction();
	this->speed = arg.getSpeed();
	return (*this);
}

Ship::~Ship ( void ) {
}

void			Ship::shoot( Container & missiles ) {
	(void)missiles;
}

bool			Ship::canShoot( void ) const {
	return (lastShoot + reload < getMilliCount() / 1000.f);
}
