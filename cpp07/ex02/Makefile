CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = array_test

all: $(NAME)

$(NAME): main.cpp Array.hpp Array.tpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all
