CC = g++
PRINTF = printf
RM = rm

CPP_FILES = $(wildcard *.cpp)
CPP_FLAGS = -std=c++11 -Wall -Wconversion -Wextra -pedantic

RM_FLAGS = -r -f

all: spell_checker

run: clean all
	@$(PRINTF) "Executing spell_checker...\n\n"
	@./spell_checker

spell_checker: $(CPP_FILES)
	@$(PRINTF) "Compiling spell_checker...\n\n"
	@$(CC) $(CPP_FLAGS) $^ -o $@

clean:
	@$(PRINTF) "Cleaning workspace... "
	@$(RM) $(RM_FLAGS) spell_checker
	@$(PRINTF) "Cleaned!\n"
