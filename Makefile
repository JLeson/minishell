NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -f

SRCDIR			=	./src/
BUILTINSDIR		=	$(SRCDIR)builtins/
BINDIR			=	./bin/
HEADERDIR		=	./include/
LIBDIR			=	./lib/

SRCFILES		=	minishell.c	\
					parse.c		\
					expander.c	\
					env.c		\
					echo.c		\

BINFILES		=	$(notdir $(SRCFILES:.c=.o))

SRCPATHS		=	$(addprefix $(SRCDIR), $(SRCFILES))
BINPATHS		=	$(addprefix $(BINDIR), $(BINFILES))

LIBFTNAME		=	libft.a
LIBFTDIR		=	./libft/

$(NAME):		$(LIBDIR)$(LIBFTNAME) $(BINPATHS)
					$(CC) $(CFLAGS) $(BINPATHS) $(LIBDIR)$(LIBFTNAME) -lreadline -o $(NAME)


$(BINDIR)%.o:	$(SRCDIR)%.c
					@mkdir -p $(BINDIR)
					$(CC) $(CFLAGS) -I $(HEADERDIR) -c $< -o $@

$(BINDIR)%.o:	$(BUILTINSDIR)%.c
					@mkdir -p $(BINDIR)
					$(CC) $(CFLAGS) -I $(HEADERDIR) -c $< -o $@

$(LIBDIR)$(LIBFTNAME):
					$(MAKE) -C $(LIBFTDIR)


all:			$(NAME)

clean:
					@$(RM) $(BINPATHS)
					$(MAKE) clean -C $(LIBFTDIR)

fclean:			clean
					@$(RM) $(NAME)
					$(MAKE) fclean -C $(LIBFTDIR)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
