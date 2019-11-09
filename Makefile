a.out: searchtest.c
	$(error "Did not specify what library to use! Either 'proc' or 'thread' ")

proc: searchtest.c multitest_proc.o
	gcc seachtest.c multitest_proc.o

thread: searchtest.c multitest_thread.o
	gcc searchtest.c multitest_thread.o

multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c

multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c
