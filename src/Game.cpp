#include <Game.hpp>
#include <signal.h>
#include <curses.h>

#include <Enemy.hpp>
#include <Enemy2.hpp>
#include <AMissile.hpp>

Window  sing_window ( Window * window ) {
	static Window *save = NULL;

	if (window)
		save = window;
	return (*save);
}
#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

char const choices[3][14] = {
	"[  Imperial ]",
	"[ BattlShip ]",
	"[   Eta_2   ]"
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	for(i = 0; i < 3; i++)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}



void    Game::start( void ) {
	if (status == PLAY) 
		return ;
	if (status == STOP) {
		status = PLAY;
		launchMenu();
	} else if (status == PAUSE)
		status = PLAY;
}

void	Game::launchMenu( void ) {
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
				
	startx = (w.ws_col - 10)  / 2;
	starty= (w.ws_row - 5) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	
		c = wgetch(menu_win);
		
		
		mvwprintw(menu_win, 10, 10, "%s", c);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = 3;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == 3)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0) {
			clrtoeol();
			refresh();
			endwin();
		    srand(time(NULL));
    		score = 0;	
			if (game_loop(highlight) == -1){
				break;
			}
		}
	}	
	clrtoeol();
	refresh();
}

void    Game::pause( void ) {
	if (status != PAUSE)
		return;
	status = PLAY;
}

void    Game::stop( void ) {
	if (status == STOP)
		return;
	status = STOP;
	win.close();
}

void    Game::spawnRandom( void ) {
  const float xRatio = 1.5f;

  int windowWidth = win.getWidth();
  int windowHeight = win.getHeight();

  int border = rand() % 8;
  float pX;
  float pY;
  float vX;
  float vY;

  if (border == 0) {                                                        //LEFT
                                pX = 1;
                                pY = rand() % windowHeight;
                                vX = (((rand() % 100) / 100.f) - .5) * xRatio;
                                vY = 1 * (rand() % 100) / 100.f;
  } else if (border == 1 || border == 2 ) {                                 //Top
                                pX = rand() % windowHeight;
                                pY = 1;
                                vX = (1 * (rand() % 100) / 100.f) * xRatio;
                                vY = (((rand() % 100) / 100.f) - .5);
  } else if (border == 3 || border == 4) {                                  //Bottom
                                pX = rand() % windowWidth;
                                pY = windowHeight - 2;
                                vX = (((rand() % 100) / 100.f) - .5) * xRatio;
                                vY = -1 * (rand() % 100) / 100.f;
  } else {                                                                  //RIGHT
                                pX = windowWidth - 2;
                                pY = rand() % windowHeight;
                                vX = (-1 * (rand() % 100) / 100.f) * xRatio;
                                vY = (((rand() % 100) / 100.f) - .5);
  }

    if (rand() % 2 == 1)
      enemies.push(new Enemy(pX, pY, vX, vY));
    else
      enemies.push(new Enemy2(pX, pY, vX, vY));
}

void          Game::spawnRandom( int quantity ) {
	while (quantity--)
		spawnRandom();
}

void          Game::displayInfo( int hp, int shield ) const {
  win.print(0, 0, ("Life: " + std::to_string(hp) + ", Shield: " + std::to_string(shield)
                    + ", score: " + std::to_string(score)).c_str());
}

int    Game::game_loop( int choice ) {
	Ship *player_1;

  if ( choice == 1)
	player_1 = new ImperialStarship(30, 30, -1, 0);
  else if ( choice == 2)
  	player_1 = new BattleShip(30, 30, -1, 0);
  else
  	player_1 = new Eta_2(30, 30, -1, 0);
  player_1->setVecX(1);
  player_1->updateXY();
  players.push(player_1);

  int i;
  while (status != STOP) {
    if (((rand() % 10000) / 100.f) > 98.5)
      spawnRandom();
    update();

                //Collisions missiles_enemies / Player
    i = missiles_enemies.eachCollision(player_1);
    while (i != -1) {
      Entity*   missile = missiles_enemies.getUnit(i);
      if (missile) {
        player_1->takeDamage(((AMissile*)missile)->getDamage());
      }
      missiles_enemies.delUnit(i);
      i = missiles_enemies.eachCollision(player_1);
    }

                //Collisions enemies / Player
    i = enemies.eachCollision(player_1);
    while (i != -1) {
      player_1->takeDamage(50);
      enemies.delUnit(i);
      i = enemies.eachCollision(player_1);
    }

                //Collisions allies / enemies
    int max = enemies.getCount();
    int c = 0;
    bool done;

    while (c < max) {
      Entity*   enemy = enemies.getUnit(c);
      done = false;
      if (enemy) {
        i = missiles_allies.eachCollision(enemy);
        while (i != -1) {
           if (done == false) {
             enemies.delUnit(c);
             done = true;
             score += 10;
          }
          missiles_allies.delUnit(i);
          i = missiles_allies.eachCollision(enemy);
        }
      }
      ++c;
    }

    displayInfo(player_1->getHP(), player_1->getArmor());
    win.flush();
    if (player_1->getHP() <= 0) {
    	endwin();
	  	return (-1);
	}
  }
	return (0);
}

static void resizeDetection( int ) {
	Window window = sing_window(NULL);

	window.resizeEvent();
}

Game::Game( void ) : win(Window()), status(STOP), fps(60) {
    sing_window(&win);
    win.open();
    win.setFPS(fps);
    nodelay(win.getGameWindow(), TRUE);
    signal( SIGWINCH, resizeDetection );
}

Game::Game( Game const & cpy ) {
	(*this) = cpy;
}

Game::~Game( void ) {
}

e_gamestatus    Game::getStatus() const {
	return (status);
}

int             Game::getFPS() const  {
  return (fps);
}

void            Game::setFPS( int value )  {
  fps = value;
  speedRatio = 1.f / fps;
  win.setFPS(fps);
}

float       Game::getSpeedRatio() const  {
	return (speedRatio);
}

Game&    Game::operator=(Game const & arg) {
	fps = arg.getFPS();
	status = arg.getStatus();
	speedRatio = arg.getSpeedRatio();
	return (*this);
}

std::ostream  &operator<<(std::ostream& flux, const Game& arg) {
	if (arg.getStatus() == PLAY)
		flux << "Game is on, FPS cap set to " << arg.getFPS() << std::endl;
	else if (arg.getStatus() == PAUSE)
		flux << "Game is in pause" << std::endl;
	else
		flux << "Game is off" << std::endl;
	return (flux);
}

void      Game::draw( void ) const {
	win.clr();
	win.drawSprite(missiles_allies);
	win.drawSprite(missiles_enemies);
	win.drawSprite(enemies);
	win.drawSprite(players);
}

void      Game::update( void ) {
  char c = wgetch(win.getGameWindow());
  players.event(c, missiles_allies);
  enemies.event(' ', missiles_enemies);
  draw();
  enemies.update( win.getSpeed(), 0, win.getWidth(), 0, win.getHeight() );
  players.update_borders( win.getSpeed(), 0, win.getWidth(), 0, win.getHeight() );
  missiles_allies.update( win.getSpeed(), 0, win.getWidth(), 0, win.getHeight() );
  missiles_enemies.update( win.getSpeed(), 0, win.getWidth(), 0, win.getHeight() );
}
