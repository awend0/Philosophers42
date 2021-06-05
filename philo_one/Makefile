NAME	= philo_one
SRC		=	main.c \
			init.c \
			thread.c \
			lifespan.c \
			utils.c \
			print.c \

DIR_INC	= includes/
DIR_SRC = srcs/
SRCS	= $(addprefix $(DIR_SRC), $(SRC))
OBJS	= $(SRCS:c=o)
FLAGS	= -O3 -I $(DIR_INC) -Wall -Wextra -Werror -fsanitize=address -pthread

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette .