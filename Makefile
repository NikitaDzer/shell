CC     = gcc
CFLAGS = -O1 -fsanitize=address

BUILD_DIR = ./build
EXEC_FILE = terminal


all: $(EXEC_FILE)

$(EXEC_FILE): $(BUILD_DIR)/main.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/executer.o $(BUILD_DIR)/pipe.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/executer.o $(BUILD_DIR)/pipe.o -o $(EXEC_FILE)

$(BUILD_DIR)/main.o: $(BUILD_DIR) main.c
	$(CC) -c $(CFLAGS) main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/parser.o: parser.c
	$(CC) -c $(CFLAGS) parser.c -o $(BUILD_DIR)/parser.o

$(BUILD_DIR)/executer.o: executer.c
	$(CC) -c $(CFLAGS) executer.c -o $(BUILD_DIR)/executer.o

$(BUILD_DIR)/pipe.o: pipe.c
	$(CC) -c $(CFLAGS) pipe.c -o $(BUILD_DIR)/pipe.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(EXEC_FILE)
