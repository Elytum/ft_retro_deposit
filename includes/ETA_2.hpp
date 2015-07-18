#ifndef ETA_2_HPP
# define ETA_2_HPP

# include <Ship.hpp>
# include <Container.hpp>
# include <PlasmaCanon.hpp>
# include <AMissile.hpp>
# include <Tools.hpp>

class Eta_2 : public Ship
{
	public:
		Eta_2( void );
		Eta_2( float posX, float posY, float vecX, float vecY );
		Eta_2 ( Eta_2 const & cpy );
		~Eta_2( void );
		virtual void shoot( Container & missiles );
};

#endif
