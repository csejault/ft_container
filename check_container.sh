#!/bin/bash

MAIN_FT="./srcs/ft_containers.cpp"
MAIN_MAKEFILE="./srcs/main.cpp"

cat $MAIN_FT > $MAIN_MAKEFILE
make
./ft_containers > .ft_result.txt

sed s/"namespace LIB_TO_USE = ft"/"namespace LIB_TO_USE = std"/g $MAIN_FT > $MAIN_MAKEFILE
sed s/"LIB_NAME = ft"/"LIB_NAME = std"/g $MAIN_FT > $MAIN_MAKEFILE
make re
./ft_containers > .std_result.txt
make fclean

diff .ft_result.txt .std_result.txt && echo "DIFF OK"
rm $MAIN_MAKEFILE

