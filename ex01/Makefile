CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = RPN

SRCS = main.cpp RPN.cpp

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