# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwanlin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/09 19:27:02 by bwanlin           #+#    #+#              #
#    Updated: 2015/06/21 19:41:38 by bwanlin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang++

CFLAGS	=	-Wall -Werror -Wextra -g

LDFLAGS	= -lncurses

SRC		=	main.cpp			 		\
			src/Tools.cpp				\
			src/Game.cpp	 			\
			src/Battleship.cpp 			\
		   	src/ETA_2.cpp 				\
			src/Entity.cpp 				\
			src/ImperialStarship.cpp 	\
			src/PlasmaCanon.cpp 		\
			src/Ship.cpp 				\
			src/Sprite.cpp 				\
			src/Window.cpp				\
			src/Container.cpp			\
			src/Enemy.cpp				\
			src/Enemy2.cpp				\
			src/Bullet.cpp				\
			src/AMissile.cpp

INC		=	includes

OBJ		=	$(SRC:.cpp=.o)

EXE		=	AwesomeShip

all		:	$(SRC) $(EXE)

$(EXE)	:	$(OBJ)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJ) $(LDFLAGS)

%.o:%.cpp
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(EXE)

re		: fclean all
