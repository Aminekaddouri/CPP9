CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = btc

SRCS = main.cpp BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONEY: all fclean clean re