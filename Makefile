CC=clang

IFLAGS=-I ~/Documents/devlibs/glfw -I ~/Documents/devlibs/glad -I ~/Documents/c/cube/include -I ~/Documents/devlibs/cglm-0.9.0/include

LFLAGS=-L ~/Documents/devlibs/glfw/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

SRC=src
SRCS:=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

BUILD=build
TARGET=$(BUILD)/bin
# CFLAGS:=

.SILENT:
# rule: build binary
all: $(TARGET)

run: $(TARGET)
	@echo running target...
	./$(TARGET)

# rule: build bin from objs
$(TARGET): $(OBJS)
	@echo building target...
	$(CC) $^ $(LFLAGS) -o $@
	@echo done!

# build obj files
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $^ $(IFLAGS) -c -o $@

clean:
	@echo cleaning...
	rm -f $(OBJ)/*
	rm -f $(TARGET)
	@echo done!
