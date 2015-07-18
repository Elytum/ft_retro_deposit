#ifndef SPRITE_HPP
# define SPRITE_HPP

class Sprite
{
	public:
		Sprite( void ) {}
		Sprite ( int maxX, int maxY, char const *str, char const *colors );
		Sprite ( Sprite const & cpy );
		~Sprite( void );

		Sprite&		operator=( Sprite const & arg );

		int				getSizeX( void ) const;
		int				getSizeY( void ) const;
		char			*getContent( void ) const;
		char			*getColors( void ) const;
		char			*spriteDuplicate( int maxX, int maxY, char const *str) const;
		Sprite*			clone( void ) const;

	private:
		int			sizeX;
		int			sizeY;
		char		*content;
		char		*colors;
};

#endif
