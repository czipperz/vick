CFLAGS=-lncurses -Wall
O=out
S=src
T=tests
CC=g++

all: $O/newmove.o \
     $O/main.o \
     $O/key_listeners.o \
     $O/command_listeners.o \
     $O/show_message.o \
     $O/prefix_g.o \
     $O/int_to_str.o \
     $O/parse_init_contents.o \
     $O/configuration.o \
     $O/basic_commands.o
	${CC} -o testVI $^ $(CFLAGS)

#	aser2	4sk	6eskl	8
#	2be	4	6
#	2	4
#	2
#1	3

# If header found then force recompilation when updated
$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CC} -o $@ -c $< $(CFLAGS)

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CC} -o $@ -c $< $(CFLAGS)

clean:
	rm -R out
	rm `find -name '*~'`

test:
	${CC} -o $T/out \
     $T/*.cc \
     $T/UnitTest++/*.cpp \
     $T/UnitTest++/Posix/*.cpp \
     $S/int_to_str.cc \
     ${CFLAGS}
	./$T/out
