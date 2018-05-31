##
## EPITECH PROJECT, 2018
## cpp_indie
## File description:
## Menu Engine
##

NAME	= 	menu

CXX	=	g++ -I./ -I./../../ -std=c++14 -W -Wall -Wextra -g -g3

LDFLAGS = 	-lIrrlicht -lGL -lGLU -lglut -lX11 -lstdc++ -lpthread

RM	=	rm -f

SRCS	=	main.cpp					\
		classes/parsers/MyScriptParser.cpp		\
		classes/parsers/ButtonFactory.cpp		\
		../components/ButtonComponent.cpp		\
		../components/CameraComponent.cpp		\
		../components/ComponentPoolEvent.cpp		\
		../components/DisplayComponent.cpp		\
		../components/LightComponent.cpp		\
		../core/Entities.cpp				\
		../core/Entity.cpp				\
		../core/EventsHandler.cpp			\
		../core/Game.cpp				\
		../core/Scene.cpp				\
		../exceptions/ComponentPoolException.cpp	\
		../network/Selector.cpp				\
		../network/Socket.cpp				\
		../systems/ClientNetworkSystem.cpp		\
		../systems/DisplaySystem.cpp			\
		../systems/System.cpp				\
		../utils/EntityComparator.cpp


OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
