# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csejault <csejault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 11:59:05 by csejault          #+#    #+#              #
#    Updated: 2022/02/08 16:21:22 by csejault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SOURCES:
#https://codingnest.com/basic-makefiles/
#http://www.gnu.org/software/make/manual/make.html#Text-Functions

NAME			=	ft_containers

SOURCES_DIR		=	srcs/

INCLUDES		= 	-I include -I .

DEFINE_STD		=	-D LIB_TO_USE=std -D LIB_TO_USE_STR="std"

SOURCES_NAME	= 	\
					main


# Add SRCS_DIR name before filename and cpp at the end
SOURCES			= $(patsubst %, $(SOURCES_DIR)%.cpp, $(SOURCES_NAME))

# Copy SOURCES but replace .cpp by .o
OBJECTS			= 	$(SOURCES:.cpp=.o)

# Copy SOURCES but replace .cpp by .d
DEPEND			=	$(SOURCES:.cpp=.d)

# Compiler
CPP				=	c++

# FLAGS
# -MMD tells the compiler to output a Makefile snippet for each compiled .cpp
#  	file, and save it into a .d file with the same name.
# -MP then tells the compiler to also output a non-dependent target for each
#  	header file it encounters. This prevents Make errors if header files are
#  	renamed/deleted/moved, and it attempts to use the old dependency
#  	information, as it thinks it can create the missing header.
DEBUG		=	-g3 -fsanitize=address
CPPFLAGS		=	-Wall -Werror -Wextra -std=c++98 -MMD -MP $(DEBUG) $(INCLUDES)

# Tells Make to include all .d files created by compiling object files,and the -
# 	prefix tells it to ignore error during inclusions. this prevents errors when
# 	compiling the project from scratch when corresponding .d files have not yet
# 	been created.
-include $(DEPEND)

#	AUTOMATIC VARIABLES
#	$@	=	Name of the rules
#	$<	=	Name of the first dependances
#	$^	=	every dependances

.cpp.o:			
				$(CPP) $(CPPFLAGS) $(DEFINE_STD) -c $< -o $(<:.cpp=.o)

all:			$(NAME) 

std:			$(OBJECTS)
					$(CPP) $(CPPFLAGS) $(DEFINE_STD) $^ -o $@

$(NAME):		$(OBJECTS)
					$(CPP) $(CPPFLAGS) $^ -o $@

clean:			
					rm -f $(OBJECTS) $(DEPEND)

fclean:			clean
					rm -f $(NAME)

re:				fclean all



.PHONY:			all clean fclean re
# Delete the default suffixes
.SUFFIXES:            		
# Define my suffix list
.SUFFIXES:		.cpp .o .h
# Default target
.DEFAULT_GOAL 	:= all

