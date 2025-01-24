NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = pipex.c\
	pipex_utils.c\
	libft/libft.a\

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME):
	make all -C libft
	${CC} -g ${SRCS} -o ${NAME}

all : $(NAME)

clean :
	rm -rf ${OBJS}
		make clean -C libft

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean delete_file all 

delete_file:
	rm -f outfile