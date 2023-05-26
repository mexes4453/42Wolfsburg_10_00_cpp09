# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2023/05/26 23:39:50 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS:= main.cpp  BitcoinExchange.cpp

OBJS:= $(SRCS:.c=.o)
MSG = 
REP = mexes

NAME = btc

CC = c++
STD_CPP = c++98
CFLAGS = -Werror -Wall -Wextra -std=$(STD_CPP)
INCLUDES = -I./

#=== COLORS ====
COL_Y = "\033[1;32m"
COL_G = "\033[1;33m"
COL_D = "\033[0m"

NAME : all
all : $(NAME)
$(NAME) : $(OBJS) 
	@echo "\033[1;33mCompiling Executables: $(NAME) \033[0m"
	$(CC) $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo; echo "\033[1;32mCompilation Successful. \033[0m"
	@echo; echo

	
# obj files output
%.o : %.c
	@echo
	@echo "\033[1;33mCompiling OBJ files \033[0m"
	$(CC) -c $^ $(CFLAGS) $(INCLUDES) -o $@
	@echo


# remove all object files
fclean:
	rm -rf *.o

# remove final target files
clean: fclean
	rm -rf $(NAME)

# recompile everything
re: clean all

#=================== DEBUG =============================
debug: 
	@$(eval CFLAGS:=$(CFLAGS) -g)
	make
	

#=================== GIT ===============================
#define comments
push:	clean
	$(info Pushing to Git Repository)
	@git add ../*
	@git ls-files; git status
	@git commit -m "$(MSG)"
ifeq ($(REP), 42)
	@git push wolfsburg main
	@echo $(COL_G)Pushed to repo: $(REP)$(COL_D)
#	@git rm -f --cached *.pdf *.md			#	2> /dev/null
else 
	@git push mexes main
	@echo $(COL_G)Pushed to repo: mexes$(COL_D)
endif
	@echo $(COL_G)$(MSG)$(COL_D)

#endef # comments

.PHONY : all fclean clean re push debug
