CC      := gcc
INCLUDE := -Iinclude
LIBS    := -lSDL2 -lGLEW -lGL -lm
CARGS   := $(INCLUDE) -ggdb -Wall -Wextra -Werror -pedantic
OUT     := run

objects += main.o
objects += glutil.o
objects += futil.o
objects += vec.o
objects += shape.o
objects += bezier.o

build: $(addprefix obj/, $(objects))
	@mkdir -p $(dir ./$(OUT))
	$(CC) $(CARGS) -o ./$(OUT) $^ $(LIBS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CARGS) -o $@ $^

run: build
	./$(OUT)

gdb: build
	gdb ./$(OUT)

clean:
	rm $(OUT)
	rm -r ./obj
