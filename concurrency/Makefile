FLAGS = -Wall -pthread -g 

clean:
	rm -rf main-thread-intro main-thread-api main-thread-lock mem-layout-test

main-thread-intro: main-thread-intro.c common_threads.h
	gcc -o main-thread-intro main-thread-intro.c $(FLAGS)

main-thread-api: main-thread-api.c common_threads.h
	gcc -o main-thread-api main-thread-api.c $(FLAGS)

main-thread-lock: main-thread-lock.c common_threads.h
	gcc -o main-thread-lock main-thread-lock.c $(FLAGS)

mem-layout-test: mem-layout-test.c
	gcc -o mem-layout-test mem-layout-test.c $(FLAGS)
