#ifndef AMISSILE_HPP
# define AMISSILE_HPP

# include <Entity.hpp>
# include <iostream>

class AMissile : public Entity
{
	protected:
		int				damage;
		float			reloadTime;

		AMissile	( void );

	public:
		AMissile	( float reloadTime, int damage, Sprite const sprite );
		AMissile	( float posX, float posY, float vecX, float vecY, float speed, float reloadTime, int damage, Sprite const sprite );
		AMissile	( AMissile const & cpy );
		virtual ~AMissile( void );
		// virtual	void	attack( float posX, float posY, float vecX, float vecY ) const = 0;
		float			getReloadTime() const;
		int				getDamage() const;
		AMissile&		operator=( AMissile const & arg );
};

std::ostream &operator<<(std::ostream& flux, const AMissile& arg);

//			Weapons
#include <PlasmaCanon.hpp>
#include <Bullet.hpp>

#endif
