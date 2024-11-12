CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = PmergeMe

SRCS = main.cpp PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONEY: all clean fclean re