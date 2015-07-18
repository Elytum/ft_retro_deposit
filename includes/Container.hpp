#ifndef CONTAINER_HPP
# define CONTAINER_HPP

# include <IContainer.hpp>

class Container : public IContainer
{
	private:
		int						count;
		Entity**				container;

	public:
		Container( void );
		virtual ~Container();
		virtual int				getCount() const;
		virtual Entity*			getUnit(int) const;
		virtual void			delUnit(int pos);
		virtual int				push(Entity*);
		void					update( float speedRatio, int minX, int maxX, int minY, int maxY );
		void					update_borders( float speedRatio, int minX, int maxX, int minY, int maxY );
		void					event( int key, Container & missiles );
		int						eachCollision( Entity *compared );
};

#endif
