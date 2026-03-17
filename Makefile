TARGET_DIR = ./build
PROJECTS = ado1 ex_aula5

.SECONDEXPANSION:
$(TARGET_DIR)/%: $$(wildcard %/*.c)
	mkdir -p $(TARGET_DIR)
	gcc $^ -o $@

ado1: build/ado1

ex_aula5: build/ex_aula5

all: $(PROJECTS)

clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean $(PROJECTS)
