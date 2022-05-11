#!/bin/bash

MAIN_FT="./srcs/ft_containers.cpp"
MAIN_MAKEFILE="./srcs/main.cpp"

#if [[ $# -eq 0 ]]
#then
#	clear
#	cat $MAIN_FT > $MAIN_MAKEFILE
#	make && valgrind -s --leak-check=full --show-leak-kinds=all ./ft_containers
#	make fclean
#	exit
#else
#
make
echo -e "\nlauch ft"
time ./ft_containers >.ft_result.txt

echo -e "\nlauch std"
time ./std_containers >.std_result.txt
diff .ft_result.txt .std_result.txt && echo "DIFF OK"
make fclean
#fi
