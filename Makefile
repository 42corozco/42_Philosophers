# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corozco <????@????.???>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 02:02:47 by corozco           #+#    #+#              #
#    Updated: 2021/02/25 15:23:26 by corozco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
#color
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

EX_1 = philo_one
EX_2 = philo_two
EX_3 = philo_three

SRCS = Philosophers

all: $(EX_1) $(EX_2) $(EX_3)

$(EX_1):
	@$(MAKE) -C $(SRCS)/$(EX_1) MAKEFLAGS=
	@cp -rf $(SRCS)/$(EX_1)/$(EX_1) ./$(EX_1)

$(EX_2):
	@$(MAKE) -C $(SRCS)/$(EX_2) MAKEFLAGS=
	@cp -rf $(SRCS)/$(EX_2)/$(EX_2) ./$(EX_2)

$(EX_3):
	@$(MAKE) -C $(SRCS)/$(EX_3) MAKEFLAGS=
	@cp -rf $(SRCS)/$(EX_3)/$(EX_3) ./$(EX_3)

clean:
	@make clean -C $(SRCS)/$(EX_1)
	@make clean -C $(SRCS)/$(EX_2)
	@make clean -C $(SRCS)/$(EX_3)

fclean:
	@make fclean -C $(SRCS)/$(EX_1)
	@make fclean -C $(SRCS)/$(EX_2)
	@make fclean -C $(SRCS)/$(EX_3)
	@rm -rf $(EX_1) $(EX_2) $(EX_3)

re: fclean all

norme:
	@printf "%b" "$(OK_COLOR)\tnorme $(EX_1)$(NO_COLOR)\n";
	@/usr/bin/norminette $(SRCS)/$(EX_1)/includes/ $(SRCS)/$(EX_1)/srcs
	@printf "%b" "$(OK_COLOR)\tnorme $(EX_2)$(NO_COLOR)\n";
	@/usr/bin/norminette $(SRCS)/$(EX_2)/includes/ $(SRCS)/$(EX_2)/srcs
	@printf "%b" "$(OK_COLOR)\tnorme $(EX_3)$(NO_COLOR)\n";
	@/usr/bin/norminette $(SRCS)/$(EX_3)/includes/ $(SRCS)/$(EX_3)/srcs
