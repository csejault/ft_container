#!/bin/bash

MAIN_FT="./srcs/ft_containers.cpp"
MAIN_STD="./srcs/std_containers.cpp"
MAIN_MAKEFILE="./srcs/main.cpp"

cat $MAIN_FT > $MAIN_MAKEFILE
make
./ft_containers > ft_result.txt
make fclean

sed s/"namespace LIB = ft"/"namespace LIB = std"/g $MAIN_FT > $MAIN_MAKEFILE
make
./ft_containers > std_result.txt
make fclean

diff ft_result.txt std_result.txt
rm $MAIN_MAKEFILE

