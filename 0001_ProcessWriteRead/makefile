CC = g++
CFLAGS = -Wall
LIBVAR   = -lpsapi

BUILD_DIR = build

SOURCE=$(wildcard *.cpp)
EXECS=$(patsubst %.cpp,$(BUILD_DIR)/%,$(SOURCE))  

all: $(EXECS)

$(BUILD_DIR)/% : %.cpp
	@echo + CC $<
	@mkdir -p $(BUILD_DIR)
	$(CC) -g -o $@ $< $(LIBVAR)

# Don't remove *.o files automatically
# .SECONDARY: $(OBJS)

.PHONY:clean  all
clean:
	-rm -rf $(BUILD_DIR)