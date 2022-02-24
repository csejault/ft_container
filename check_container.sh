#!/bin/bash

MAIN_FT="./srcs/ft_containers.cpp"
MAIN_MAKEFILE="./srcs/main.cpp"

if [[ $# -eq 0 ]]
then
	clear
	cat $MAIN_FT > $MAIN_MAKEFILE
	make re && ./ft_containers
	exit
else

	clear
	cat $MAIN_FT > $MAIN_MAKEFILE
	make re && ./ft_containers >.ft_result.txt

	sed s/"LIB_NAME = ft"/"LIB_NAME = std"/g $MAIN_FT > $MAIN_MAKEFILE
	sed s/"namespace LIB = ft"/"namespace LIB = std"/g -i $MAIN_MAKEFILE
	make re
	./ft_containers >.std_result.txt
	make fclean

	diff .ft_result.txt .std_result.txt && echo "DIFF OK"
	rm $MAIN_MAKEFILE
fi
