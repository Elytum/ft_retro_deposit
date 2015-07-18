#ifndef BATTLESHIP_HPP
# define BATTLESHIP_HPP

# include <Ship.hpp>
# include <Container.hpp>
# include <AMissile.hpp>

class BattleShip : public Ship
{
	public:
		BattleShip( void );
		BattleShip( float posX, float posY, float vecX, float vecY );
		BattleShip ( BattleShip const & cpy );
		~BattleShip( void );
		virtual void		shoot( Container & missiles );
};

#endif
