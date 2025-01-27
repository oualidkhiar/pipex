NAME = pipex

NMBO = pipex_bonus
CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = pipex.c\
	pipex_utils.c\
	libft/libft.a\

SRCS_BNS = pipex_bonus.c\
	pipex_bonus_utils.c\
	libft/libft.a\

CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	make all -C libft
	${CC} ${CFLAGS} -g ${SRCS} -o ${NAME}

bonus : $(NMBO)

$(NMBO):
	make all -C libft
	$(CC) $(CFLAGS) $(SRCS_BNS) -o $(NMBO)

clean :
		make clean -C libft

fclean :
	rm -rf $(NAME) $(NMBO)
	make fclean -C libft

re : fclean all
