CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = whatever

all: $(NAME)

$(NAME): main.cpp whatever.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all
