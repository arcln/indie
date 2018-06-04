##
## EPITECH PROJECT, 2018
## cpp_indie
## File description:
## Menu Engine
##

NAME	= 	menu

CXX	=	g++ -I./ -I./engine/menu/ -std=c++14 -W -Wall -Wextra -g -g3

LDFLAGS = 	-lIrrlicht -lGL -lGLU -lglut -lX11 -lstdc++ -lpthread

RM	=	rm -f

SRCS	=	engine/menu/main.cpp					\
		engine/menu/classes/parsers/MyScriptParser.cpp		\
		engine/menu/classes/parsers/ButtonFactory.cpp		\
		engine/menu/classes/parsers/ImageFactory.cpp		\
		engine/menu/classes/parsers/ImageHandler.cpp		\
		engine/components/ButtonComponent.cpp		\
		engine/components/ImageComponent.cpp		\
		engine/components/CameraComponent.cpp		\
		engine/components/ComponentPoolEvent.cpp		\
		engine/components/IrrlichtComponent.cpp		\
		engine/components/LightComponent.cpp		\
		engine/core/Entities.cpp				\
		engine/core/Entity.cpp				\
		engine/core/EventsHandler.cpp			\
		engine/core/Game.cpp				\
		engine/core/Scene.cpp				\
		engine/exceptions/ComponentPoolException.cpp	\
		engine/network/Selector.cpp				\
		engine/network/Socket.cpp				\
		engine/systems/ClientNetworkSystem.cpp		\
		engine/systems/DisplaySystem.cpp			\
		engine/systems/System.cpp				\
		engine/utils/EntityComparator.cpp			\
		engine/utils/TagComparator.cpp


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
