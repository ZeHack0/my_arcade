##
## EPITECH PROJECT, 2026
## nanotekspice
## File description:
## flags.mk
##

CPPFLAGS += -std=c++20
CPPFLAGS += -Wall
CPPFLAGS += -Wextra
CPPFLAGS += -Werror

CPPFLAGS += -I ./include

# macOS (Homebrew) include paths (Apple Silicon & Intel)
CPPFLAGS += -I/opt/homebrew/include -I/usr/local/include
