#include <Window.hpp>
#include <signal.h>

#include <iostream>
static float			calcRefresh(int fps) {
	return ((1.f / fps) * 1000);
}

/* CLASS start here */

void	Window::open( void ) {
	if (opened == true)
		return ;
	opened = true;
initscr();


struct winsize w;
ioctl(0, TIOCGWINSZ, &w);
game_window = newwin(w.ws_row, w.ws_col, 0, 0);
keypad(game_window, TRUE);

window_red = derwin(game_window, w.ws_row, w.ws_col, 0, 0);
window_green = derwin(game_window, w.ws_row, w.ws_col, 0, 0);
window_blue = derwin(game_window, w.ws_row, w.ws_col, 0, 0);
window_yellow = derwin(game_window, w.ws_row, w.ws_col, 0, 0);
window_white = derwin(game_window, w.ws_row, w.ws_col, 0, 0);

init_color(COLOR_RED, 500, 500, 500);
start_color();

init_pair(1, COLOR_RED, COLOR_BLACK);
init_pair(2, COLOR_GREEN, COLOR_BLACK);
init_pair(3, COLOR_BLUE, COLOR_BLACK);
init_pair(4, COLOR_YELLOW, COLOR_BLACK);
init_pair(5, COLOR_WHITE, COLOR_BLACK);

wbkgd(window_red, COLOR_PAIR(1));
wbkgd(window_green, COLOR_PAIR(2));
wbkgd(window_blue, COLOR_PAIR(3));
wbkgd(window_yellow, COLOR_PAIR(4));
wbkgd(window_white, COLOR_PAIR(5));

noecho();
curs_set(FALSE);
	(void)content;
	(void)colors;
}

void				Window::close( void )	{
	if (opened == false)
		return ;
	endwin();
}

void	Window::clr( void ) const {

	// static char buffer[1000 * 1000];
	// static bool init = false;

	// if (init == false) {
	// 	init = true;
	// 	memset(buffer, ' ', height * width);
	// }
	// buffer[height * width] = '\0';
	// mvwprintw(game_window, 0, 0, buffer);
	// buffer[height * width] = ' ';


	// int y = 0;
	// int x;
	// while (y < height) {
	// 	x = 0;
	// 	while (x < width) {
	// 		mvwprintw(game_window, y, x, " ");
	// 		++x;
	// 	}
	// 	++y;
	// }
	
	// y = 0;
	// while (y < height) {
	// 	x = 0;
	// 	while (x < width) {
	// 		mvwprintw(game_window, y, x, " ");
	// 		++x;
	// 	}
	// 	++y;
	// }
	// werase(window_red);
	// werase(window_green);
	// werase(window_blue);
	// werase(window_white);
	// werase(window_yellow);
	werase(game_window);
	memset(content, ' ', width * height);
	memset(colors, ' ', width * height);
}

void		Window::print( int x, int y, char const *c ) const {
	char *ptr = (char *)c;

	if (y < 0 || y > height || !*ptr)
		return ;
	while (x < 0) {
		if (!*ptr)
			return ;
		++x;
		++ptr;
	}
	int pos = x + y * width + 1;
	while (*ptr && x < width) {
		content[pos] = *ptr++;
		colors[pos] = 'W';
		++pos;
		++x;
	}
}

void	Window::print( int x, int y, char const c, char const color ) const {
	int		colorID = 0;
	int		pos = 0;

	if (c == ' ' || color == ' ' || c == '\0' || color == '\0' || x < 0 || y < 0 || x >= width || y >= height)
		return ;
	if (color == 'R')
    	colorID = 1;
 	 else if (color == 'G')
    	colorID = 2;
  	else if (color == 'B')
    	colorID = 3;
  	else if (color == 'Y')
    	colorID = 4;
  	else if (color == 'W')
    	colorID = 5;
	if (colorID) {
		pos = x + y * width - 1;
		content[pos] = c;
		colors[pos] = color;
	}
}

void	Window::doPrint( void ) const {
	int		x;
	int		y = 0;
	int		p = 0;
	int		colorID;
	char	tmp[2];

	tmp[1] = '\0';
	while (y < height) {
		x = 0;
		while (x < width) {
			if (content[p] != ' ' && content[p] != '\0' && colors[p] != ' ' && colors[p]) {
				colorID = 0;
				tmp[0] = content[p];
				if (colors[p] == 'R')
					mvwprintw(window_red, y, x, tmp);
				else if (colors[p] == 'G')
					mvwprintw(window_green, y, x, tmp);
				else if (colors[p] == 'B')
					mvwprintw(window_blue, y, x, tmp);
				else if (colors[p] == 'Y')
					mvwprintw(window_yellow, y, x, tmp);
				else if (colors[p] == 'W')
					mvwprintw(window_white, y, x, tmp);
			}
			++p;
			++x;
		}
		++y;
	}
}

void	Window::flush( void )	{

	// usleep(10000);	// int		timeToSleep;

	// // refresh();
	// // mvwprintw(window, 0, 0, "LOL");
	// wrefresh(window);
	// // // exit (0);
	// // timeToSleep = refreshTime - getMilliSpan(lastFlush);
	// // if (timeToSleep > 0) {
	// // 	usleep(timeToSleep * 1000);
	// // 	speed = 1;
	// // } else
	// // 	speed = ((-timeToSleep) / refreshTime);
	// // lastFlush = getMilliCount();
	// speed = 1;



	int		timeToSleep;

	doPrint();
// wrefresh(window_red);
// wrefresh(window_green);
// wrefresh(window_blue);
// wrefresh(window_yellow);
// wrefresh(window_white);
	// usleep(1000);
	// usleep(10000);
	wrefresh(game_window);
	timeToSleep = refreshTime - getMilliSpan(lastFlush);
	if (timeToSleep > 0) {
		usleep(timeToSleep * 1000);
		speed = 1;
	}
	// clr();
	lastFlush = getMilliCount();
}

float	Window::getSpeed( void ) const {
	return speed;
}

void	Window::setFPS( int fps ) {
	FPS = fps;
	refreshTime = calcRefresh(FPS);
}

WINDOW*		Window::getGameWindow( void )	{
	return game_window;
}

void	Window::drawSprite ( int x, int y, Sprite const & sprite ) const {
	char	*content = sprite.getContent();
	char	*colors = sprite.getColors();
	int		maxX = sprite.getSizeX();
	int		maxY = sprite.getSizeY();
	int		halfX = maxX / 2;
	int		halfY = maxY / 2;
	int		posX;
	int		posY;


	int     i;
  	int     j = 0;
  	int     p = 0;

	while (j < maxY) {
    	i = 0;
    	posY = j + y - halfY;
    	if (posY > 0 && posY < height) {
			while (i < maxX) {
    			posX = i + x - halfX;
				if (posX > 0 && posY < height)
					print(posX, posY, content[p], colors[p]);
				++p;
				++i;
			}
		}
	++j;
	}
}

void	Window::drawSprite ( Container const & container ) const {
	int			pos = 0;
	int			max = container.getCount();
	Entity		*entity;

	while (pos < max) {
		entity = container.getUnit(pos++);
		if (entity)
			drawSprite(entity->getPosX(), entity->getPosY(), *entity->getSprite());
	}
}

Window::Window( void ) : opened(false), FPS(60), refreshTime(calcRefresh(FPS)), lastFlush(getMilliCount()),
	content(NULL), colors(NULL), window_red(NULL), window_green(NULL), window_blue(NULL),
	window_yellow(NULL), window_white(NULL), game_window(NULL)	{
	resizeEvent();
	memset(content, width * height, '\0');
	memset(colors, width * height, '\0');
}

Window::Window ( Window const & cpy ) {
  *this = cpy;
}

Window::~Window( void )	{
	if (window_red)
		delwin(window_red);
	if (window_green)
		delwin(window_green);
	if (window_blue)
		delwin(window_blue);
	if (window_yellow)
		delwin(window_yellow);
	if (window_white)
		delwin(window_white);
	if (game_window)
		delwin(game_window);
}

Window&				Window::operator=(Window const & arg)	{
	return (*this);
	(void)arg;
}


void		Window::resizeEvent( void ) {
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	height = w.ws_row;
	width = w.ws_col;


	// if (content)
	// 	delete content;
	// if (colors)
	// 	delete colors;
	content = new char [width * height];
	colors = new char [width * height];

	erase();
	print(0, 0, "Resize !");
}

int			Window::getWidth( void ) const {
	return width;
}

int			Window::getHeight( void ) const {
	return height;
}

/*


\
**-
****
**-
/




                 -)------+====+                       
         -)----====    ,'   ,'  
               `.  `.,;___,'  
                 `, |____l_\                          
  _,.....------c==]""______ |,,,,,,.....____ _        
 "-:______________  |____l_|]''''''''''' 
                ,'"",'.   `.  
         -)-----====   `.   `.
                -)-------+====+ 

            .
           .d$ .
           d$$  :
          .$$$
          :$$$   :
          $$$$   :
          $$$$   :
         .$$$$
         :$$$$    :
         :$$$$    :
         $$$$$    :
         $$$$$    :
         :    $$$$$
         :    $$$$$
         :    $$$$$
        .:    $$$$$.
       / :    $$$$: \
      /  :    $$$$:  \
     '        $$$$`   '
     |    :   $$$$    |
     |   /:   $$$$\   |
     |  /     $$$` \  |
     |_/   :__$$P   \_|





*/
