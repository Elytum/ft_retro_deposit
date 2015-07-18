#ifndef PLASMACANON_HPP
# define PLASMACANON_HPP

# include <AMissile.hpp>

class PlasmaCanon : public AMissile
{
	private:

	public:
		PlasmaCanon( void );
		PlasmaCanon( float posX, float posY, float vecX, float vecY );
		virtual ~PlasmaCanon( void );
};

#endif
