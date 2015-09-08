plugins_o  = `[ "$$(ls plugins)" ] && \
              if [ "$$(find plugins -name out -type d)" ]; then \
                 find plugins -name out -type d \
                   | xargs -n 1 printf "find %s -type f\n" \
                   | bash; \
              else \
                 echo; \
              fi`
plugins_hh = `find plugins -name src -type d | xargs -n 1 printf "-I%s\n"` -Isrc
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
      $O/contents.o           \
      $O/command_listeners.o  \
      $O/file_contents.o      \
      $O/hooks.o              \
      $O/to_str.o             \
      $O/key_listeners.o      \
      $O/mode.o               \
      $O/prefix.o             \
      $O/prompt.o             \
      $O/show_message.o       \
      $O/visual.o             \

testfiles = ${TO}/to_str_tests.o        \
            ${TO}/main.o                \
            ${TO}/visual_tests.o        \

all: ${files} $O/main.o $O/configuration.o
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} || exit $$!; cd ../..; \
        done
	${CXX} -o $B ${plugins_o} $^ ${CFLAGS} ${LDFLAGS}

begin:
	@mkdir -p plugins
	[ -d plugins/vick-move ] || git clone \
                                        'https://github.com/czipperz/vick-move' \
                                        plugins/vick-move

# If header found then force recompilation when updated
$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O plugins
	${CXX} -o $@ -c $< ${CFLAGS} ${plugins_hh}

$O/%.o: $S/%.cc
	@mkdir -p $O plugins
	${CXX} -o $@ -c $< ${CFLAGS} ${plugins_hh}

$O/.test_configuration.o: $S/configuration.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS} -Dtesting

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CXX} -o $@ -c $< ${CFLAGS} -Isrc

clean:
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} clean || exit $$!; cd ../..; \
        done
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ ! -e $B ] || rm $B

cleantest:
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} cleantest || exit $$!; cd ../..; \
        done
	rm `find ${TO} -type f -not -name 'main.o'`

test: ${files} ${testfiles} $O/.test_configuration.o
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} test || exit $$!; cd ../..; \
        done
	${CXX} -o $T/out $^ ${plugins_o} ${LDFLAGS} ${CFLAGS}
	./$T/out

tags:
	etags `find $S -name '*.cc' -o -name '*.hh'`
