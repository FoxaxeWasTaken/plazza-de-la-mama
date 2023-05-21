##
## EPITECH PROJECT, 2023
## plazza
## File description:
## Makefile for plazza
##

GCC			=	g++
RM			=	-rm

NAME		=	plazza

MAIN		=	src/Main.cpp

SRC			=	src/Messages.cpp			\
				src/Pizzas.cpp				\
				src/Storage.cpp				\
				src/Thread.cpp				\
				src/ConditionalVariable.cpp	\
				src/Mutex.cpp				\
				src/Fork.cpp				\
				src/ScopedLock.cpp			\
				src/Clock.cpp

OBJ			=	$(SRC:%.cpp=%.o) $(MAIN:%.cpp=%.o)

TESTS_SRC	=

TESTS_OBJ	=	$(TESTS_SRC:%.cpp=%.o)

CPPFLAGS	=	-Wall -Wextra -Wshadow -Wpedantic -I./src -std=c++17 -pthread

TESTS_FLAGS	=	-lcriterion
COVERAGE	=	--coverage -fprofile-arcs -ftest-coverage

all:		$(NAME)

$(NAME):	$(OBJ)
	$(GCC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	find . -name "*~" -delete -or -name "#*#" -delete
	find . -name "*.o" -delete
	find . -name "*.gcda" -delete -or -name "*.gcno" -delete

fclean:		clean
	$(RM) -f $(NAME)

re:			fclean $(NAME)

tests_run:	LDFLAGS += $(TESTS_FLAGS)
tests_run:	CXXFLAGS += $(COVERAGE)
tests_run:	clean
	@$(GCC) -o unit_tests $(TESTS_SRC) $(SRC) $(CXXFLAGS) $(LDFLAGS) -I./
	./unit_tests --always-succeed
	$(RM) unit_tests

coverage:	tests_run
	gcovr . --exclude tests/
	gcovr .	-b --exclude tests/
	$(MAKE) clean

debug:		CXXFLAGS += -g
debug:		re

.PHONY:	all clean fclean re
