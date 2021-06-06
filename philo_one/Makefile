NAME	=	philo_one
SRC		=	main.c \
			init.c \
			routines.c \
			lifespan.c \
			utils.c \
			print.c \

DIR_SRC = 	srcs/
SRCS	= 	$(addprefix $(DIR_SRC), $(SRC))
OBJS	= 	$(SRCS:c=o)
FLAGS	=	-Wall -Wextra -Werror -O3 -fsanitize=address -pthread

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