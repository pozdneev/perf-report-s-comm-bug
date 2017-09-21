# Credit: Louis Stuber (IBM Client Center Montpellier)
COMMAND=gcc -Ofast -std=c99 -Wall -Wextra
FPIC= -fpic 

all: libdo1.so libdo2.so main.c
	$(COMMAND) main.c -L. -ldo1 -ldo2

libdo1.so: do1.c
	$(COMMAND) $(FPIC) do1.c -c
	$(COMMAND) -shared do1.o -o libdo1.so
libdo2.so: do2.c
	$(COMMAND) $(FPIC) do2.c -c
	$(COMMAND) -shared do2.o -o libdo2.so

clean:
	rm -f *.o *.so *.out

distclean: clean
	rm -f *~ perf.data*
