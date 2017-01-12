CC = g++
PRINTF = printf
RM = rm

CPP_FILES = $(wildcard *.cpp)
CPP_FLAGS = -std=c++11 -Wall -Wconversion -Wextra -pedantic

RM_FLAGS = -r -f

all: spell_checker

spell_checker: $(CPP_FILES)
	@$(CC) $(CPP_FLAGS) $^ -o $@

clean:
	@$(PRINTF) "Cleaning workspace... "
	@$(RM) $(RM_FLAGS) spell_checker
	@$(PRINTF) "Cleaned!\n"
