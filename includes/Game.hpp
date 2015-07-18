 #ifndef GAME_HPP
# define GAME_HPP

# include <Ship.hpp>
# include <Window.hpp>
# include <AMissile.hpp>

enum e_gamestatus {
  PLAY = 1,
  PAUSE = 2,
  STOP = 3,
};

class Game
{

public:
  Game( void );
  ~Game( void );

  void          start( void );
  void          pause( void );
  void          stop( void );
  int          game_loop( int choice );
  void          draw ( void ) const;
  void          update ( void );
  e_gamestatus  getStatus ( void ) const;
  int           getFPS ( void ) const;
  void          setFPS ( int value );
  float         getSpeedRatio ( void ) const;
  void          spawnRandom( void );
  void          spawnRandom( int quantity );
	void	launchMenu( void );
  void          displayInfo( int hp, int shield ) const;

private:
  Game&    operator=( Game const & arg );
  Game ( Game const & cpy );
  Window          win;
  e_gamestatus    status;
  int             fps;
  Container       enemies;
  Container       players;
  Container       missiles_allies;
  Container       missiles_enemies;
  Container       stars;
  float           speedRatio;
  int             score;
};

#endif
