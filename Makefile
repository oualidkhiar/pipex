NAME = pipex

NMBO = pipex_bonus
CC = cc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address -g3

SRCS = pipex.c\
	pipex_utils.c

SRCS_BNS = pipex_bonus.c\
	pipex_bonus_utils.c\
	here_doc.c

OBJS = $(SRCS:.c=.o)
OBJS_BNS = $(SRCS_BNS:.c=.o)

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	@make all -s -C libft
	@$(CC) $(CFLAGS) ${OBJS} libft/libft.a -o ${NAME}
	@echo "$(GREEN)Compile success"
	@echo "$(RED)from oukhiar.$(RESET)"

bonus : $(OBJS_BNS)
	@make all -s -C libft
	@$(CC) $(CFLAGS) $(SRCS_BNS) libft/libft.a -o $(NAME)
	@echo "$(GREEN)Compile bonus success"
	@echo "$(RED)from oukhiar.$(RESET)"

clean :
	@rm -rf $(OBJS) $(OBJS_BNS)
	@make clean -s -C libft
	@echo "$(GREEN)cleaning success"
	@echo "$(RED)from oukhiar.$(RESET)"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -s -C libft

re : fclean all

