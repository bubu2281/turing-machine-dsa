build:
	gcc -std=gnu11 -o tema1 -g main.c functii.c
run: build
	./tema1
clean:
	rm tema1
mem-check:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./tema1
gdb:
	gdb ./tema1