SRC_DIR = ./src
OBJ_DIR = ./obj
COMMON_FLAGS = -g -I./include
OUT_DIR = ./output

COMMON_SOURCES = DoublyLinkedList.cpp Driver.cpp Process.cpp Reader.cpp
COMMON_OBJECTS = $(addprefix $(OBJ_DIR)/, $(COMMON_SOURCES:.cpp=.o))

# Rule to create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(OUT_DIR))

# Rule to generate object files for common source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(COMMON_FLAGS) -c $< -o $@

# Rule to generate object files for MemoryManager with specific flags
$(OBJ_DIR)/MemoryManager_firstfit.o: $(SRC_DIR)/MemoryManager.cpp
	g++ $(COMMON_FLAGS) -c $< -o $@ -DFIRST_FIT

$(OBJ_DIR)/MemoryManager_bestfit.o: $(SRC_DIR)/MemoryManager.cpp
	g++ $(COMMON_FLAGS) -c $< -o $@ -DBEST_FIT

$(OBJ_DIR)/MemoryManager_nextfit.o: $(SRC_DIR)/MemoryManager.cpp
	g++ $(COMMON_FLAGS) -c $< -o $@ -DNEXT_FIT

$(OBJ_DIR)/MemoryManager_worstfit.o: $(SRC_DIR)/MemoryManager.cpp
	g++ $(COMMON_FLAGS) -c $< -o $@ -DWORST_FIT

all: firstfit bestfit nextfit worstfit

firstfit: $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_firstfit.o
	g++ $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_firstfit.o -o $(OUT_DIR)/firstfit

bestfit: $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_bestfit.o
	g++ $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_bestfit.o -o $(OUT_DIR)/bestfit

nextfit: $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_nextfit.o
	g++ $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_nextfit.o -o $(OUT_DIR)/nextfit

worstfit: $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_worstfit.o
	g++ $(COMMON_OBJECTS) $(OBJ_DIR)/MemoryManager_worstfit.o -o $(OUT_DIR)/worstfit

clean:
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/*