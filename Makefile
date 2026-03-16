##
## EPITECH PROJECT, 2026
## nanotekspice
## File description:
## Makefile
##

include flags.mk

NAME = arcade

CC := g++

BUILD_DIR := .build

SRC := $(shell find src -name '*.cpp')
OBJ := $(SRC:%.cpp=.build/%.o)

LDFLAGS =

GRE := \033[0;32m
GRA := \033[0;37m
BLU := \033[0;34m
RED := \033[0;31m

all:
	@ $(MAKE) $(NAME) -j --no-print-directory

$(NAME): $(OBJ)
	@ $(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)
	@ echo -e "$(BLU)===--- $(GRE)Compiled$(GRA) < $@ > $(BLU)---===$(GRA)"

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(CPPFLAGS) -c -o $@ $<
	@ echo -e "$(GRE)Compiled$(GRA) $<"

clean:
	@ $(RM) $(OBJ) $(TOBJ)
	@ $(RM) *.a
	@ echo -e "$(RED)Cleaned$(GRA)"

fclean: clean
	@ $(RM) $(NAME)
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM) *.a
	@ echo -e "$(RED)Force cleaned$(GRA)"

re: fclean
	@ $(MAKE) all -j --no-print-directory

.PHONY: all clean fclean re
