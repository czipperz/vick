CFLAGS=-std=c++11
O=out
S=src
T=test
TO=testout
CC=g++
B=vick

files=$O/basic_commands.o	\
      $O/class_contents.o	\
      $O/command_listeners.o	\
      $O/configuration.o	\
      $O/file_contents.o	\
      $O/hooks.o		\
      $O/int_to_str.o		\
      $O/key_listeners.o	\
      $O/move.o			\
      $O/newmove.o		\
      $O/prefix_g.o		\
      $O/prompt.o		\
      $O/show_message.o

testfiles = ${TO}/int_to_str_tests.o \
     ${TO}/main.o \
     ${TO}/newmove_tests.o

all: $B

$B: ${files} $O/main.o
	${CC} -o $@ $^ $(CFLAGS) -lncurses

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

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CC} -o $@ -c $< -std=c++11

$T/UnitTest++/Posix/%.o: $T/UnitTest++/Posix/%.cpp
	${CC} -o $@ -c $<

$T/UnitTest++/%.o: $T/UnitTest++/%.cpp
	${CC} -o $@ -c $<

clean:
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ -z "`find -name '*.o'`" ] || rm `find -name '*.o'`

test: $B ${testfiles}
	${CC} -o $T/out \
             ${testfiles} \
             ${files} \
             -lncurses -std=c++11
	./$T/out
