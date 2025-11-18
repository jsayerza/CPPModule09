NAME = RPN

# Compiler
CXX = c++
# Flags per a compiler
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
# Flags per a debug
DEBUG_FLAGS = -g -fsanitize=address -fsanitize=undefined

INC_PATH =	./includes/
INC =		-I $(INC_PATH)
HEADERS =	$(INC_PATH)RPN.hpp 

SRC_PATH =	./sources/
SRC =		$(SRC_PATH)main.cpp \
			$(SRC_PATH)RPN.cpp 

OBJ_PATH =	./objects/
OBJ =		$(SRC:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)


# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Regla per a build
all: $(OBJ_PATH) $(NAME)

# Regla per a build objects
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC)
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"

# Regla per a build program
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) successfully compiled$(RESET)"

# Regla per a debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: re

clean:
	rm -f $(OBJ_PATH)*.o
	@echo "$(RED)✗ Objects deleted$(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re debug

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "7 7 * 7 -"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 2 * 2 / 2 * 2 4 - +"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "(1 + 1)"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 20 -"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 2.0 -"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 2.0f -"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 2+"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 2 3 +"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "0 0 / +"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "1 0 + 0 /"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./RPN "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *"
