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

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	MAC_LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -undefined dynamic_lookup
	RPATH = -Wl,-rpath,/usr/local/lib
else
	MAC_LDFLAGS =
	RPATH =
endif

SRC_MAIN := $(shell find src/core_src/ -name '*.cpp')
SRC_LIBS := $(shell find src/lib_src/ -name '*.cpp')
SRC_GAMES := $(shell find src/games_src/ -name '*.cpp')

OBJ_MAIN = $(SRC_MAIN:%.cpp=$(BUILD_DIR)/%.o)
LIBS_SO = $(notdir $(SRC_LIBS:%.cpp=%.so))
GAMES_SO = $(notdir $(SRC_GAMES:%.cpp=%.so))

LDFLAGS = -ldl -lncurses -lsfml-graphics -lsfml-window -lsfml-system -lSDL2 $(RPATH) $(MAC_LDFLAGS) -rdynamic

GRE := \033[0;32m
GRA := \033[0;37m
BLU := \033[0;34m
RED := \033[0;31m

all:
	@ $(MAKE) $(LIBS_SO) $(GAMES_SO) $(NAME) -j --no-print-directory

$(NAME): $(LIBS_SO) $(GAMES_SO) $(OBJ_MAIN)
	@ $(CC) -o $(NAME) $(OBJ_MAIN) $(CPPFLAGS) $(LDFLAGS)
	@ echo -e "$(BLU)===--- $(GRE)Compiled$(GRA) <$@> $(BLU)---===$(GRA)"

%.so: src/lib_src/%.cpp
	@ $(CC) $(CPPFLAGS) -fPIC -shared $< -o $@ $(LDFLAGS)
	@ echo -e "$(GRE)Compiled$(GRA) $<"
	@ echo -e "$(BLU)===--- $(GRE)Compiled Library$(GRA) <$@> $(BLU)---===$(GRA)"

%.so: src/games_src/%.cpp
	@ $(CC) $(CPPFLAGS) -fPIC -shared $< -o $@ $(LDFLAGS)
	@ echo -e "$(GRE)Compiled$(GRA) $<"
	@ echo -e "$(BLU)===--- $(GRE)Compiled Games$(GRA) <$@> $(BLU)---===$(GRA)"

core: $(OBJ_MAIN)
	@ $(CC) -o $(NAME) $(OBJ_MAIN) $(CPPFLAGS) $(LDFLAGS)
	@ echo -e "$(BLU)===--- $(GRE)Compiled$(GRA) <$@> $(BLU)---===$(GRA)"

games: $(GAMES_SO)
	@ echo -e "$(BLU)===--- $(GRE)Compiled Games$(GRA) $(BLU)---===$(GRA)"

graphicals: $(LIBS_SO)
	@ echo -e "$(BLU)===--- $(GRE)Compiled Graphicals$(GRA) $(BLU)---===$(GRA)"

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(CPPFLAGS) -c -o $@ $<
	@ echo -e "$(GRE)Compiled$(GRA) $<"

clean:
	@ $(RM) $(OBJ_MAIN) $(TOBJ)
	@ $(RM) *.a
	@ echo -e "$(RED)Cleaned$(GRA)"

fclean: clean
	@ $(RM) $(NAME) $(LIBS_SO) $(GAMES_SO)
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM) *.a
	@ echo -e "$(RED)Force cleaned$(GRA)"

re: fclean
	@ $(MAKE) all -j --no-print-directory

.PHONY: all clean fclean re core games graphicals
