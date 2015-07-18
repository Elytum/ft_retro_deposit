#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <Ship.hpp>
# include <Container.hpp>
# include <AMissile.hpp>

class Enemy : public Ship
{
	public:
		Enemy( void );
		Enemy( float posX, float posY, float vecX, float vecY );
		Enemy ( Enemy const & cpy );
		~Enemy( void );
		virtual void		shoot( Container & missiles );
};

#endif
