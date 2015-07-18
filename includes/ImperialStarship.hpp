#ifndef IMPERIALSTARSHIP_HPP
# define IMPERIALSTARSHIP_HPP

# include <Ship.hpp>
# include <Container.hpp>
# include <AMissile.hpp>

class ImperialStarship : public Ship
{
	public:
		ImperialStarship( void );
		ImperialStarship( float posX, float posY, float vecX, float vecY );
		ImperialStarship ( ImperialStarship const & cpy );
		~ImperialStarship( void );
		virtual void		shoot( Container & missiles );
};

#endif
