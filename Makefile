all:
	gcc -o main src/main.c src/similarity.c src/similarity.h src/file.c src/file.h src/patternMatching.c src/patternMatching.h -lm
	./main

clean:
	rm all main