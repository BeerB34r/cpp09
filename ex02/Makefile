CXX				=	c++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++20
SRC				=	main.cpp PmergeMe.cpp
OBJ				=	$(SRC:.cpp=.o)
NAME			=	merge

.DEFAULT_GOAL	=	$(NAME)

all				:	clangd

$(NAME)			:	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean			:
	$(RM) $(OBJ)

fclean			:
	$(MAKE) clean
	$(RM) $(NAME)

re				:
	$(MAKE) fclean
	$(MAKE)

clangd			:
	intercept-build-14 $(MAKE)

.PHONY			:	clean fclean re all
