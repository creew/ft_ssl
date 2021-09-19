ALL_C =	ft_ssl.c \
        parse_arg.c \
        print.c \
        process_hash_md5.c \
        process_hash_sha256.c \
        process_hash_sha224.c \
        process_hash_sha512.c \
        usage.c \
        utils.c \
		commands/md5.c \
        commands/sha256.c \
        commands/sha224.c \
        commands/sha512.c \
        options/parse_option_p.c \
        options/parse_option_q.c \
        options/parse_option_r.c \
        options/parse_option_s.c
SRCDIR = ./srcs
OBJDIR = ./objs
OBJDIRS = $(OBJDIR) $(OBJDIR)/options $(OBJDIR)/commands
ALL_OBJ = $(ALL_C:%.c=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = ft_ssl

INCLUDES = includes/ft_ssl.h \
           includes/md5.h \
           includes/sha256.h \
           includes/sha224.h \
           includes/sha512.h \
           includes/ssl_types.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $@

$(OBJDIRS):
	/bin/mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIRS)
	gcc $(FLAGS) -I./includes -I./libft/includes -c $< -o $@


clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY:  clean fclean all re
