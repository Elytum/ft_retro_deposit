#include <Sprite.hpp>

int				Sprite::getSizeX( void ) const {
	return sizeX;
}

int				Sprite::getSizeY( void ) const {
	return sizeY;
}

char			*Sprite::getContent( void ) const {
	return content;
}

char			*Sprite::getColors( void ) const {
	return colors;
}

char			*Sprite::spriteDuplicate( int maxX, int maxY, char const *str) const {
	int 		total = (maxX) * (maxY);
	char		*content = new char [total--];

	while (total >= 0) {
		content[total] = str[total];
		--total;
	}
	return (content);
}

Sprite::Sprite( int x, int y, char const *str, char const *colors ) : sizeX(x), sizeY(y),
						content(spriteDuplicate(x, y, str)),
						colors(spriteDuplicate(x, y, colors))	{
}

Sprite::Sprite ( Sprite const & cpy ) {
	*this = cpy;
}

Sprite::~Sprite( void )	{
	delete content;
	delete colors;
}

Sprite&				Sprite::operator=(Sprite const & arg)	{
	this->sizeX = arg.getSizeX();
	this->sizeY = arg.getSizeY();
	this->content = spriteDuplicate(arg.getSizeX(), arg.getSizeY(), arg.getContent());
	this->colors = spriteDuplicate(arg.getSizeX(), arg.getSizeY(), arg.getColors());
	return (*this);
}

Sprite*				Sprite::clone( void ) const {
	return (new Sprite(sizeX, sizeY, content, colors));
}