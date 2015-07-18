#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <Sprite.hpp>
# include <Container.hpp>
# include <ncurses.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <Tools.hpp>

class Window
{
	public:
		Window( void );
		Window ( Window const & cpy );
		~Window( void );
		void		open( void );
		void		close( void );
		void		clr( void ) const;
		void		print( int x, int y, char const *c ) const;
		void		print( int x, int y, char const c, char const color ) const;
		void		flush( void );
		void		setFPS( int FPS );
		float		getSpeed( void ) const;
		WINDOW*		getGameWindow( void );
		
		int			getWidth( void ) const;
		int			getHeight( void ) const;

		void		drawSprite ( int x, int y, Sprite const & sprite ) const;
		void		drawSprite ( Container const & container ) const;

		void		doPrint( void ) const;
		void		resizeEvent( void );
		Window&		operator=( Window const & arg );

	private:
		bool		opened;
		int			FPS;
		float		refreshTime;
		int			lastFlush;
		float		speed;
		char		*content;
		char		*colors;
		int			height;
		int			width;
		WINDOW		*window_red;
		WINDOW		*window_green;
		WINDOW		*window_blue;
		WINDOW		*window_yellow;
		WINDOW		*window_white;
		WINDOW		*game_window;
};

#endif
