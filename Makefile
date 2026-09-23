CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread
NAME    := codexion

SRCS    := 

OBJS    := $(SRCS:.c=.o)

# RULES

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
