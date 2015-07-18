#include <Entity.hpp>
#include <Math.h>
#include <ncurses.h>
#include <string.h>

static void		normalize(float *vecX, float *vecY) {
	float				magn = sqrt (*vecX * *vecX + *vecY * *vecY);

	*vecX /= magn;
	*vecY /= magn;
}

float			Entity::getSpeed( void ) const {
	return (speed);
}

float			Entity::getPosX( void ) const {
	return (posX);
}

float			Entity::getPosY( void ) const {
	return (posY);
}

float			Entity::getVecX( void ) const {
	return (vecX);
}

float			Entity::getVecY( void ) const {
	return (vecY);
}

void			Entity::setVecXY( float x, float y )	{
	vecX = x;
	vecY = y;
	normalize(&vecX, &vecY);
}

void			Entity::setVecX( float x ) {
	vecX = x;
}

void			Entity::setVecY( float y ) {
	vecX = y;
}

void			Entity::updateXY( void ) {
	if (vecX || vecY)
		normalize(&vecX, &vecY);
}


void			Entity::setPosX( float x )	{
	posX = x;
}

void			Entity::setPosY( float y )	{
	posY = y;
}

Sprite*			Entity::getSprite() const {
	return (sprite);
}

int				Entity::getHP( void ) const {
	return (0);
}

Entity::Entity( float posX, float posY, float speed, Sprite * sprite ) :
	posX(posX), posY(posY), vecX(0), vecY(0), speed(speed), sprite(sprite) {
}

Entity::Entity( float posX, float posY, float vecX, float vecY, float speed, Sprite * sprite ) :
	posX(posX), posY(posY), vecX(vecX), vecY(vecY), speed(speed), sprite(sprite) {
		if (vecX || vecY)
			normalize(&vecX, &vecY);
		this->vecX = vecX;
		this->vecY = vecY;
}

Entity::Entity( Entity const & cpy ) {
	*this = cpy;
}

Entity&				Entity::operator=(Entity const & arg)	{
	speed = arg.getSpeed();
	posX = arg.getPosX();
	posY = arg.getPosY();
	vecX = arg.getVecX();
	vecY = arg.getVecY();
	sprite = arg.getSprite();
	return (*this);
}

Entity::~Entity ( void ) {
	delete sprite;
}

void			Entity::update( float speedRatio ) {
	if (vecX > 0)
		posX += vecX * speed * speedRatio / 1000 * 1.5;
	else
		posX += vecX * speed * speedRatio / 1000;
	posY += vecY * speed * speedRatio / 1000 / 1.5;
}

void			Entity::update_borders( float speedRatio, int xMin, int xMax, int yMin, int yMax ) {
	// int newPosX, newPosY;
	Sprite*		sprite = getSprite();
	float		half_width = sprite->getSizeX() / 2;
	float		half_height = sprite->getSizeY() / 2;

	// if (vecX > 0)
	// 	newPosX = posX + vecX * speed * speedRatio / 1000 * 1.5;
	// else
	// 	newPosX = posX + vecX * speed * speedRatio / 1000;
	// newPosY = posY + vecY * speed * speedRatio / 1000 / 1.5;
	// if (newPosX - half_width < xMin || newPosX + half_width > xMax ||
	// 	newPosY - half_height < yMin || newPosY + half_height > yMax)
	// 	return;
	(void)xMin;
	(void)xMax;
	(void)yMin;
	(void)yMax;
	// posX = newPosX;
	// posY = newPosY;


	float newPosX;
	float newPosY;
	if (vecX > 0)
		newPosX = posX + vecX * speed * speedRatio / 1000 * 1.5;
	else
		newPosX = posX + vecX * speed * speedRatio / 1000;
	newPosY = posY + vecY * speed * speedRatio / 1000 / 1.5;
	if (newPosX - half_width < xMin + 1 || newPosX + half_width > xMax + 1 ||
		newPosY - half_height < yMin + 1 || newPosY + half_height > yMax + 1)
		return;
	posX = newPosX;
	posY = newPosY;
}

void			Entity::event( int id, Container & missiles ) {
	if (id == 'w')
		setVecXY(0, -1);
	else if (id == 's')
		setVecXY(0, 1);
	else if (id == 'a')
		setVecXY(-1, 0);
	else if (id == 'd')
		setVecXY(1, 0);
	else if (id == ' ')
		shoot(missiles);
}

void			Entity::shoot( Container & missiles ) {
	(void)missiles;
}

bool			Entity::canShoot( void ) const {
	return false;
}

/*

0,3 ; 0,4
1,3 ; 1;4

7,2 ; 7,3
8,2 ; 8;3

diffX = OTHER - ME = 7 - 0

 0123456789
0***
1***
2***	
3	;;
4



*/


bool			Entity::collide( Entity *checked ) const {
	Sprite*			selfSprite = getSprite();
	int				selfSizeX = selfSprite->getSizeX();
	int				selfSizeY = selfSprite->getSizeY();

	Sprite*			checkedSprite = checked->getSprite();
	int				checkedPosX = checked->getPosX();
	int				checkedPosY = checked->getPosY();
	int				checkedSizeX = checkedSprite->getSizeX();
	int				checkedSizeY = checkedSprite->getSizeY();

	int				checkedLeft = checkedPosX - checkedSizeX / 2;
	int				checkedRight = checkedPosX + checkedSizeX / 2;
	int				checkedTop = checkedPosY - checkedSizeY / 2;
	int				checkedBottom = checkedPosY + checkedSizeY / 2;

	int				left = posX - selfSizeX / 2;
	int				right = posX + selfSizeX / 2;
	int				top = posY - selfSizeY / 2;
	int				bottom = posY + selfSizeY / 2;

	if (((left >= checkedLeft && left <= checkedRight) ||
		(right >= checkedLeft && right <= checkedRight) ||
		(checkedLeft >= left && checkedLeft <= right) ||
		(checkedRight >= left && checkedRight <= right)) &&
		((top >= checkedTop && top <= checkedBottom) ||
		(bottom >= checkedTop && bottom <= checkedBottom) ||
		(checkedTop >= top && checkedTop <= bottom) ||
		(checkedBottom >= top && checkedBottom <= bottom)))
		return (true);
	return (false);
}
















