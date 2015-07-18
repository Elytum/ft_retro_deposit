#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <Sprite.hpp>

class Container;

class Entity
{
	public:
		Entity( float posX, float posY, float speed, Sprite * sprite );
		Entity( float posX, float posY, float vecX, float vecY, float speed, Sprite * sprite );
		Entity ( Entity const & cpy );
		virtual ~Entity( void );

		Entity&		operator=( Entity const & arg );

		float			getSpeed( void ) const;
		float			getPosX( void ) const;
		float			getPosY( void ) const;
		float			getVecX( void ) const;
		float			getVecY( void ) const;
		void			setVecXY( float x, float y );
		void			setVecX( float x );
		void			setVecY( float y );
		void			updateXY( void );
		void			setPosX( float x );
		void			setPosY( float y );
		Sprite			*getSprite() const;
		void			update( float speedRatio );
		void			update_borders( float speedRatio, int xMin, int xMax, int yMin, int yMax );
		void			event( int id, Container & missiles );
		virtual	void	shoot( Container & missiles );
		virtual bool	canShoot( void ) const;
		bool			collide( Entity *checked ) const;
		virtual int		getHP( void ) const;

	protected:
		float			posX;
		float			posY;
		float			vecX;
		float			vecY;
		float			speed;
		Sprite*			sprite;
};

#endif
