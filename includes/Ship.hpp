#ifndef SHIP_HPP
# define SHIP_HPP

# include <Container.hpp>
# include <Entity.hpp>
# include <Sprite.hpp>
# include <iostream>

class Ship : public Entity
{
	public:
		Ship( std::string const & name, int hp, int armor, int armorregen,
			int reduction, int speed, float reload, Sprite const & sprite );
		Ship( float posX, float posY, float vecX, float vecY,
				std::string const & name, int hp, int armor, int armorregen,
				int reduction, float speed, float reload, Sprite const & sprite );
		Ship ( Ship const & cpy );
		virtual ~Ship( void );

		Ship&		operator=( Ship const & arg );

		std::string		getName( void ) const;
		int				getArmor( void ) const;
		int				getArmorRegen( void ) const;
		int				getReduction( void ) const;
		void			takeDamage( int attack );

		virtual void	shoot( Container & missiles );
		virtual bool	canShoot( void ) const;
		virtual int		getHP( void ) const;
		void			event( int id );

	protected:
		std::string		name;
		int				HP;
		int				maxHP;
		int				armor;
		int				armorRegen;
		int				reduction;
		float			reload;
		float			lastShoot;
};

//		Include Ships
# include <ETA_2.hpp>
# include <ImperialStarship.hpp>
# include <BattleShip.hpp>

#endif
