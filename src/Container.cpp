#include <Container.hpp>

Container::Container( void ) : count(0), container(0) {
}

Container::~Container( void ) {
	int			i = 0;

	while (i < count) {
		if (container[i])
			delete container[i];
		++i;
	}
	count = 0;
}

int				Container::getCount( void ) const {
	return (count);
}

int				Container::push( Entity* marine ) {
	int				i = 0;

	while (i < count) {
		if (container[i] == 0) {
			container[i] = marine;
			return (i);
		}
		++i;
	}

	Entity**		containing = new Entity*[count + 1];
	int					len = 0;

	while (len < count) {
		containing[len] = container[len];
		++len;
	}
	if (container)
		delete [] container;
	containing[len] = marine;
	container = containing;
	return (count++);
}

Entity*			Container::getUnit( int pos ) const {
	if (pos < 0 || pos >= count)
		return (0);
	return (container[pos]);
}

void			Container::delUnit(int i) {
	if (i < 0 || i >= count)
		return ;
	if (container[i]) {
		delete container[i];
		container[i] = 0;
	}
}

void			Container::update( float speedRatio, int minX, int maxX, int minY, int maxY ) {
	int				i = 0;
	int				right;
	int				left;
	int				bottom;
	int				top;
	int				halfSizeX;
	int				halfSizeY;
	int				posX;
	int				posY;
	Sprite			*sprite;

	while (i < count) {
		if (container[i]) {
			posX = container[i]->getPosX() / 2;
			posY = container[i]->getPosY() / 2;
			sprite = container[i]->getSprite();
			halfSizeX = sprite->getSizeX();
			halfSizeY = sprite->getSizeY();

			right = posX + halfSizeX - 5;
			left = posX - halfSizeX + 5;
			bottom = posY + halfSizeY - 5;
			top = posY - halfSizeY + 5;

			if (right < minX || left > maxX || top < minY || bottom > maxY) {
				delete container[i];
				container[i] = 0;
			} else
				container[i]->update(speedRatio);
		}
		++i;
	}
}

void			Container::update_borders( float speedRatio, int minX, int maxX, int minY, int maxY ) {
	int				i = 0;

	while (i < count) {
		if (container[i])
			container[i]->update_borders(speedRatio, minX, maxX, minY, maxY );
		++i;
	}
}

void			Container::event( int key, Container & missiles ) {
	int				i = 0;

	while (i < count) {
		if (container[i])
			container[i]->event(key, missiles);
		++i;
	}
}

int				Container::eachCollision( Entity *compared ) {
	static int			i = 0;

	while (i < count) {
		if (container[i]) {
			if (compared->collide(container[i])) {
				return (i++);
			}
		}
		++i;
	}
	i = 0;
	return (-1);
}