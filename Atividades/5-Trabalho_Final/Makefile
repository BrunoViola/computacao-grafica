# Compilador e flags
CXX = g++
CXXFLAGS = -g --std=c++17 -I../include
LDFLAGS = -L/usr/lib -lGL -lGLU -lglut

# Diretórios e arquivos
SRC_DIR = ../src
OBJ_DIR = ../obj
BIN_DIR = ../bin

# Lista de arquivos-fonte
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/glad.c $(SRC_DIR)/arquibancada.cpp $(SRC_DIR)/texturas.cpp $(SRC_DIR)/personagem.cpp $(SRC_DIR)/plataforma.cpp $(SRC_DIR)/bolaParedeGol.cpp $(SRC_DIR)/variaveisGlobais.cpp $(SRC_DIR)/goleiro.cpp $(SRC_DIR)/torcedores.cpp

# Gera nomes dos arquivos-objeto automaticamente
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)))

# Nome do executável
TARGET = $(BIN_DIR)/main

# Regra principal
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $@

# Regra para compilar arquivos .cpp e .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza


