CC = g++
CFLAGS = -Wall
LIBVAR   = -lpsapi

BUILD_DIR = build

SOURCE=$(wildcard *.cpp)
EXECS=$(patsubst %.cpp,$(BUILD_DIR)/%,$(SOURCE))  


CC_C = gcc
SOURCE_C=$(wildcard *.c)
EXECS_C=$(patsubst %.c,$(BUILD_DIR)/%,$(SOURCE_C))  

all: $(EXECS) $(EXECS_C)

$(BUILD_DIR)/% : %.cpp 
	@echo + CC $<
	@mkdir -p $(BUILD_DIR)
	$(CC) -g -o $@ $< $(LIBVAR)

$(BUILD_DIR)/% : %.c 
	@echo + CC_C $<
	@mkdir -p $(BUILD_DIR)
	$(CC_C) -g -o $@ $< 

# Don't remove *.o files automatically
# .SECONDARY: $(OBJS)

.PHONY:clean  all
clean:
	-rm -rf $(BUILD_DIR)