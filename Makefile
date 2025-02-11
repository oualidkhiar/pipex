NAME = pipex

NAME_BNS = pipex_bonus

CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = pipex.c\
	pipex_utils.c\
	pipex_utils2.c

SRCS_BNS = pipex_bonus.c\
	childs.c\
	manage_files.c\
	pipex_bonus_utils.c\
	here_doc.c\
	memory_managment.c

OBJS = $(SRCS:.c=.o)
OBJS_BNS = $(SRCS_BNS:.c=.o)

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	@$(CC) $(CFLAGS) ${OBJS} libft/libft.a -o ${NAME}
	@echo "Compile success"

bonus: $(NAME_BNS)

$(NAME_BNS): $(OBJS_BNS)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS_BNS) libft/libft.a -o ${NAME_BNS}
	@echo "Compile bonus success"

clean :
	@rm -rf $(OBJS) $(OBJS_BNS)
	@make clean -s -C libft
	@echo "cleaning success"

fclean : clean
	@rm -rf $(NAME) $(NAME_BNS)
	@make fclean -s -C libft

re : fclean all
