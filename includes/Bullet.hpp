#ifndef BULLET_HPP
# define BULLET_HPP

# include <AMissile.hpp>

class Bullet : public AMissile
{
	private:

	public:
		Bullet( void );
		Bullet( float posX, float posY, float vecX, float vecY );
		virtual ~Bullet( void );
};

#endif
