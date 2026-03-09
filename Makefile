TARGET_DIR = ./build
PROJECTS = ado1

.SECONDEXPANSION:
$(TARGET_DIR)/%: $$(wildcard %/*.c)
	mkdir -p $(TARGET_DIR)
	gcc $^ -o $@

ado1: build/ado1

all: $(PROJECTS)

clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean $(PROJECTS)
