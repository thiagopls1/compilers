TARGET_DIR = ./build
PROJECTS = ado1

$(TARGET_DIR)/%: %/main.c
	mkdir -p $(TARGET_DIR)
	gcc $< -o $@

.PHONY: $(PROJECTS)
$(PROJECTS): %: $(TARGET_DIR)/%

all: $(PROJECTS)

clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean
