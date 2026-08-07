CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = iter_test

all: $(NAME)

$(NAME): main.cpp iter.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all
