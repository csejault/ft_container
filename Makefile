# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csejault <csejault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 11:59:05 by csejault          #+#    #+#              #
#    Updated: 2022/05/11 19:20:26 by csejault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SOURCES:
#https://codingnest.com/basic-makefiles/
#http://www.gnu.org/software/make/manual/make.html#Text-Functions

FT_NAME			=	ft_containers
STD_NAME		=	std_containers

SOURCES_DIR		=	srcs/

INCLUDES		= 	-I include -I .

DEFINE_STD		=	-D LIB="std"

DEFINE_FT		=	-D LIB="ft"

SOURCES_NAME	= 	\
					srcs/main


# Add SRCS_DIR name before filename and cpp at the end
SOURCES			= $(patsubst %, %.cpp, $(SOURCES_NAME))

# Copy SOURCES but replace .cpp by .o
FT_OBJECTS			= 	$(SOURCES:%.cpp=ft/%.o)
STD_OBJECTS			= 	$(SOURCES:%.cpp=std/%.o)

# Copy SOURCES but replace .cpp by .d
FT_DEPEND			=	$(SOURCES:.cpp=.d)
STD_DEPEND			=	$(SOURCES:.cpp=.d)

# Compiler
CPP				=	c++

# FLAGS
# -MMD tells the compiler to output a Makefile snippet for each compiled .cpp
#  	file, and save it into a .d file with the same name.
# -MP then tells the compiler to also output a non-dependent target for each
#  	header file it encounters. This prevents Make errors if header files are
#  	renamed/deleted/moved, and it attempts to use the old dependency
#  	information, as it thinks it can create the missing header.

#SANITIZE = -fsanitize=address
DEBUG		=	-g3 $(SANITIZE)
CPPFLAGS		=	-Wall -Werror -Wextra -std=c++98 -MMD -MP $(DEBUG) $(INCLUDES)
$(FT_NAME): CPPFLAGS += $(DEFINE_FT)
$(STD_NAME): CPPFLAGS += $(DEFINE_STD)

# Tells Make to include all .d files created by compiling object files,and the -
# 	prefix tells it to ignore error during inclusions. this prevents errors when
# 	compiling the project from scratch when corresponding .d files have not yet
# 	been created.
-include $(FT_DEPEND)
-include $(STD_DEPEND)

#	AUTOMATIC VARIABLES
#	$@	=	Name of the rules
#	$<	=	Name of the first dependances
#	$^	=	every dependances

std/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<

ft/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<


all:			$(FT_NAME) $(STD_NAME)

$(STD_NAME):	$(STD_OBJECTS)
	$(CPP) $(CPPFLAGS) $^ -o $@

$(FT_NAME):		$(FT_OBJECTS)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:			
	rm -rf ft
	rm -rf std

fclean:			clean
	rm -f $(FT_NAME)
	rm -f $(STD_NAME)

re:				fclean all



.PHONY:			all clean fclean re
	# Delete the default suffixes
	.SUFFIXES:            		
	# Define my suffix list
	.SUFFIXES:		.cpp .o .h
	# Default target
	.DEFAULT_GOAL 	:= all

