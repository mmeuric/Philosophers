# Colors
RESET				:= \033[0m
BOLD				:= \033[1m
RED					:= \033[91m
GREEN				:= \033[92m
YELLOW				:= \033[33m
ORANGE				:= \033[93m
BLUE				:= \033[94m

# Compiler
NAME			= philo
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
MKDIR			= mkdir -p
RM				= rm -rf
LINKER  	    = -lpthread

# Includes
INCLUDES_DIR 	= inc
INCLUDES_FLAG 	= -I$(INCLUDES_DIR)
INCLUDES		= $(INCLUDES_DIR)/philo.h

# Sources
SRCS_DIR		= srcs/
SRC_FILES		= main.c \
				  init.c \
				  utils.c \
				  ft_atoi.c \
				  philo.c \

# Objects
OBJS_DIR		= objs/
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))


all : $(OBJS_DIR) $(NAME)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(NAME) : $(OBJS) Makefile
	@echo "$(BOLD)$(RED)👴      Compiling Philosophers     👴$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)
	@echo "$(BOLD)$(GREEN)🍝     Philosophers compiled, Ready to think !     🍝$(RESET)"
	@echo "\n$(BOLD)🌟 Usage: ./philo [nb_philos] [time_to_die] [time_to_eat] [time_to_sleep] and with or not [nb_of_dinners] 🌟$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@	

clean :
	@$(RM) $(OBJS_DIR)
	@echo "$(BOLD)$(ORANGE)🌀     Cleaned *.o files     🌀$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(BOLD)$(ORANGE)🌀     Full Cleaned     🌀$(RESET)"

re: fclean all

.PHONY: all clean fclean re
