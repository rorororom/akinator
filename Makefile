CXX = g++-13
EXECUTABLE = list
CXXFLAGS =  -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts       \
			-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
			-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
			-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
			-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
			-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
			-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
			-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192         \
			-Wstack-usage=8192 -fsanitize=address -fsanitize=undefined -fPIE -Werror=vla

SOURCES = tree.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
EXECUTABLE = akinator.out

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:%.cpp=%.o))

.PHONY: all clean generate_image

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

run:
	./$(EXECUTABLE)

run_and_gen_image:
	./$(EXECUTABLE)
	dot -Tpng /Users/aleksandr/Desktop/akinator/grapth.dot -o file.png

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
