DEBUG	= yes
C99		= no
ifeq ($(DEBUG),no)
	FLAGS=-Wall -Wextra -Werror
else
	FLAGS= -g
endif
ifeq ($(C99),yes)
	FLAGS += -std=c99
endif
NAME	= ft_minishell1
LDFLAGS	= -I./include/ -I./libft/include/
SRC		= error.c search_bin.c  main.c \
			misc.c process.c builtin.c \
			parser_input.c builtin_env.c \
			init.c parser_var.c \
			display_prompt.c split_parser.c
OBJ		= $(SRC:.c=.o)
SRCDIR	= ./src/
OBJDIR	= ./obj/
INCDIR	= ./includes/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(OBJ))
INCS	= $(addprefix $(INCDIR), $(INC))
LIBFLAG = -L./libft/ -lft -ltermcap

all: $(NAME)

.SILENT:

$(NAME): $(OBJS) $(INCS)
	gcc $(FLAGS) -o $@ $^ $(LIBFLAG)
	echo "\\033[1;32mSuccess.\\033[0;39m"

$(OBJS): $(SRCS)
ifeq ($(DEBUG),yes)
	echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
	echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
endif
	make -C libft/
	echo "\\033[1;34mGenerating objects... Please wait.\\033[0;39m"
	gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	mv $(OBJ) $(OBJDIR)

.PHONY: clean fclean re

clean:
	echo "\\033[1;34mDeleting objects...\\033[0;39m"
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	echo "\\033[1;34mDeleting $(NAME)\\033[0;39m"
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all
