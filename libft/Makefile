NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_calloc.c ft_isascii.c ft_itoa.c ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c \
	ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memmove.c ft_putendl_fd.c ft_split.c ft_striteri.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c ft_toupper.c \
	ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcmp.c ft_memset.c ft_putnbr_fd.c ft_strchr.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c get_next_line_bonus.c

SRCS_BONUS=ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c  ft_lstnew_bonus.c  ft_lstsize_bonus.c


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@


all : $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	@ar rcs ${NAME} ${OBJS} $(OBJS_BONUS)

$(NAME) : $(OBJS)
	@ar rcs ${NAME} ${OBJS}

clean :
	@rm -f ${OBJS} $(OBJS_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
