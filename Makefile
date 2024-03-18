
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
IMAG_DIR = imag

BIN_FILE = bin
SRC_FILE = main
PY_FILE  = plot

CC      = g++
OPT     = -O0
CFLAGS  = -g -Wall $(OPT) -I$(INC_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(wildcard $(INC_DIR)/*.hpp)

all: $(BIN_DIR)/$(BIN_FILE)

$(BIN_DIR)/$(BIN_FILE): $(OBJ_DIR)/$(SRC_FILE).o $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -g

run: $(BIN_DIR)/$(BIN_FILE) | $(DATA_DIR) $(IMAG_DIR)
	./$(BIN_DIR)/$(BIN_FILE)
	./$(SRC_DIR)/$(PY_FILE).py

python: $(IMAG_DIR)
	./$(SRC_DIR)/$(PY_FILE).py

$(BIN_DIR) $(OBJ_DIR) $(DATA_DIR) $(IMAG_DIR):
	mkdir -p $@

clean:
	#rm -f $(OBJS) $(BIN_DIR)/bin
	rm -r $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run python clean

