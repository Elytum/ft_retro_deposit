#ifndef ENEMY2_HPP
# define ENEMY2_HPP

# include <Ship.hpp>
# include <Container.hpp>
# include <AMissile.hpp>

class Enemy2 : public Ship
{
	public:
		Enemy2( void );
		Enemy2( float posX, float posY, float vecX, float vecY );
		Enemy2 ( Enemy2 const & cpy );
		~Enemy2( void );
		virtual void		shoot( Container & missiles );
};

#endif
