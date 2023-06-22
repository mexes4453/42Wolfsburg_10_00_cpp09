# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/30 15:08:09 by cudoh             #+#    #+#              #
#    Updated: 2023/06/22 23:25:43 by cudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS:= main.cpp  PmergeMe.cpp

OBJS:= $(SRCS:.c=.o)
MSG = 
REP = mexes

NAME = PmergeMe

CC = c++
STD_CPP = c++98
DEBUG = 
CFLAGS = -Werror -Wall -Wextra -std=$(STD_CPP)
INCLUDES = -I./

#=== DEBUG ====
ifeq ($(DEBUG), 1)
	CFLAGS := $(CFLAGS) -g -D_DEBUG_=1
endif
	
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

#=================== GIT ===============================
#define comments
push:	clean
	$(info Pushing to Git Repository)
ifeq ($(REP), 42)
	@git push wolfsburg main
	@echo $(COL_G)Pushed to repo: $(REP)$(COL_D)
#	@git rm -f --cached *.pdf *.md			#	2> /dev/null
else 
	@git add ../*
	@git ls-files; git status
	@git commit -m "$(MSG)"
	@git push mexes main
	@echo $(COL_G)Pushed to repo: mexes$(COL_D)
	@echo $(COL_G)$(MSG)$(COL_D)
endif

#endef # comments


# ========== TEST ====================
test:
	@echo $(COL_G)=== TEST === 1 = NO ARGS$(COL_D)
	@./$(NAME)
	@echo
	@echo $(COL_G)=== TEST === 2 = MORE THAN 1 ARG INPUT $(COL_D)
	@./$(NAME) "5 1 2 6 8" 56
	@echo
	@echo $(COL_G)=== TEST === 3 = VALID INPUT $(COL_D)
	@./$(NAME) "5 1 2 6 8"
	@echo
	@echo $(COL_G)=== TEST === 4 = INVALID INPUT = NON DIGIT $(COL_D)
	@./$(NAME) "90 94 23 4 2 5 1  4    452  2  45 2   4 -k "
	@echo
	@echo $(COL_G)=== TEST === 5 = INVALID INPUT = NEGATIVE INTEGER $(COL_D)
	@./$(NAME) "90 94 23 4 2 5 1  4    452  2  45 2   4 -1 "
	@echo
	@echo $(COL_G)=== TEST === 6 = INVALID INPUT = OVF INTEGER $(COL_D)
	@./$(NAME) "90 94 42949672956 4 2 5 1  4    452  2  45 2   4 -1 "
	@echo
	@echo $(COL_G)=== TEST === 7 = INVALID INPUT = NON DIGIT $(COL_D)
	@./$(NAME) "90 94 23 4 2 5 1  4    452  2  45 2   4k3 "
	@echo
	@echo $(COL_G)=== TEST === 8 = INVALID INPUT = CORRUPT INT $(COL_D)
	@./$(NAME) "90 94 23 4 2 5 1  4    452  2  45 2   5-3 "
	@echo
	@echo $(COL_G)=== TEST === 9 = INVALID INPUT = CORRUPT INT $(COL_D)
	@./$(NAME) "90 94 -0 23 4 2 5 1  4    452  2  45 2   543 "
	@echo
	@echo $(COL_G)=== TEST === 10 = 42 SUBJECT INPUT $(COL_D)
	@./$(NAME) 3 5 9 7 4
	@echo
	@echo $(COL_G)=== TEST === 11 = 42 SUBJECT INPUT $(COL_D)
	@./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`
	@echo
	@echo $(COL_G)=== TEST === 12 = 42 SUBJECT INPUT $(COL_D)
	@./$(NAME) "-1" "2"
	@echo
.PHONY : all fclean clean re push test
