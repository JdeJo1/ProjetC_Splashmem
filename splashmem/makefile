SRCS=$(wildcard src/*.c)
HDRS=$(wildcard src/*.h)
OBJS=$(SRCS:.c=.o)
CFLAGS= -Wall -g2 -fPIC  
LDFLAGS= -ldl -lSDL2 -lSDL2_ttf -lSDL2_image
EXE=splashmem

all: players $(EXE)

$(EXE): $(OBJS)
	gcc $(OBJS) $(LDFLAGS) -o $(EXE)

%.o: %.c $(HDRS)
	gcc $(CFLAGS) -c $< -o $@

players:
	cd players && $(MAKE) -f Makefile

clean_pl:
	cd players && $(MAKE) -f Makefile clean

clean_all: clean_pl clean 
	@echo "Done"

clean: 
	rm -f core
	rm -f *.a
	rm -f *.so
	rm -f $(OBJS)
	rm -f $(EXE)
