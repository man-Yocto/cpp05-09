NAME = identify

Cpp = c++
CppLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp Base.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(Cpp) $(CppFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(Cpp) $(CppFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
