# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: psadeghi <psadeghi@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/09/04 15:28:12 by psadeghi      #+#    #+#                  #
#    Updated: 2023/09/27 20:18:05 by parisasadeq   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -pthread -gfsanitize=thread
HEADERS := -I includes
SRC_DIR := source
OBJ_DIR := object
SRC := \
		main.c\
		ft_atoi.c\
		prepare_philos.c\
		routine.c\
		checker.c\
		utils.c\
		
SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(NAME)
	$(info philo compiled)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS) 

clean:
	@$(RM) $(OBJ_DIR)
	# @$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	# @$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean