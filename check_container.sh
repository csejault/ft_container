#!/bin/bash

MAIN_FT="./srcs/ft_containers.cpp"
MAIN_MAKEFILE="./srcs/main.cpp"

if [[ $# -eq 0 ]]
then
	clear
	cat $MAIN_FT > $MAIN_MAKEFILE
	make && valgrind -s --leak-check=full --show-leak-kinds=all ./ft_containers
	make fclean
	exit
else

	clear
	cat $MAIN_FT > $MAIN_MAKEFILE
	make && ./ft_containers >.ft_result.txt
	make fclean

	cat $MAIN_FT > $MAIN_MAKEFILE
	make std && ./ft_containers >.std_result.txt
	make fclean

	vimdiff .ft_result.txt .std_result.txt && echo "DIFF OK"
	rm $MAIN_MAKEFILE
fi
