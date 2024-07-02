OS              := $(shell uname)
NAME            = philo
CC              = cc
SRC             = philo.c routine.c utils.c monitor.c utils2.c takeforks.c
OBJDIR          = obj
OBJS            = $(SRC:%.c=$(OBJDIR)/%.o)
CFLAGS          = -g -Wall -Werror -Wextra #-fsanitize=thread
LDFLAGS			= #-fsanitize=thread

# Generic rule for .o files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all

run: all
	./$(NAME)
