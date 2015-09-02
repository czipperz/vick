plugins_o  = `find plugins -mindepth 1 -type f -name '*.o'`
plugins_cc = `find plugins -mindepth 1 -type f -name '*.cc'`
plugins_hh = `find plugins -mindepth 1 -type d -name 'src' | xargs -n 1 \
              printf '-I%s\n'` -Isrc
CFLAGS=-std=c++11
LDFLAGS=-lboost_regex -lncurses
O=out
S=src
T=test
TO=testout
CXX=clang++
B=vick

files=$O/basic_commands.o     \
      $O/change.o             \
      $O/class_contents.o     \
      $O/command_listeners.o  \
      $O/configuration.o      \
      $O/file_contents.o      \
      $O/hooks.o              \
      $O/int_to_str.o         \
      $O/key_listeners.o      \
      $O/mode.o               \
      $O/prefix.o             \
      $O/prompt.o             \
      $O/show_message.o       \

testfiles = ${TO}/int_to_str_tests.o \
     ${TO}/main.o \
     ${TO}/newmove_tests.o

all: $B

begin:
	mkdir -p plugins
	[ -d plugins/vick-move ] || git clone \
                                        'https://github.com/czipperz/vick-move' \
                                        plugins/vick-move

$B: ${files} $O/main.o
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX}; cd ../..; \
        done
	${CXX} -o $@ ${plugins_o} $^ ${CFLAGS} ${LDFLAGS}

# If header found then force recompilation when updated
$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS} ${plugins_hh}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS} ${plugins_hh}

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CXX} -o $@ -c $< -std=c++11 ${plugins_hh}

$T/UnitTest++/Posix/%.o: $T/UnitTest++/Posix/%.cpp
	${CXX} -o $@ -c $<

$T/UnitTest++/%.o: $T/UnitTest++/%.cpp
	${CXX} -o $@ -c $<

clean:
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} clean; cd ../..; \
        done
	[ ! -e $B ] || rm $B

cleantest:
	rm `find ${TO} -type f -not -name 'main.o'`

test: $B ${testfiles}
	${CXX} -o $T/out \
             ${testfiles} \
             ${files} \
             -lncurses -std=c++11 \
             ${plugins_o} \
             ${LDFLAGS}
	./$T/out

tags:
	etags `find src -maxdepth 1 \( -name '*.cc' -o -name '*.hh' \)`
