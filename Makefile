plugins_o  = `[ "$$(ls plugins)" ] && \
              [ "$$(find plugins -name out -type d)" ] && \
                 find plugins -name out -type d \
                   | xargs -n 1 printf "find %s -type f\n" \
                   | bash;`
plugins_hh = `[ "$$(ls plugins)" ] && \
              [ "$$(find plugins -name src -type d)" ] && \
                 find plugins -name src -type d \
                   | xargs -n 1 printf "-I%s\n"` -Isrc
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
      $O/prefix_key.o         \
      $O/prompt.o             \
      $O/show_message.o       \
      $O/visual.o             \

testfiles = ${TO}/to_str_tests.o        \
            ${TO}/visual_tests.o        \

all: ${files} $O/main.o $O/configuration.o
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir;                                                \
             make CXX=${CXX} || exit $$!; cd ../..;                   \
        done
	${CXX} -o $B ${plugins_o} $^ ${CFLAGS} ${LDFLAGS}

begin: regen
	@mkdir -p plugins
	[ -d plugins/vick-move ] || git clone \
                                        'https://github.com/czipperz/vick-move' \
                                        plugins/vick-move

clean:
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} clean || exit $$!; cd ../..; \
        done
	[ ! -d $O ] || rm -R $O
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ ! -e $B ] || rm $B
	[ ! -d ${TO} ] || rm -R ${TO}

$T/blank:
	@touch $T/blank

test: ${files} ${testfiles} ${TO}/test_main.o $T/blank
	@rm $T/blank
	@mkdir -p plugins
	for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX=${CXX} test || exit $$!; cd ../..; \
        done
	${CXX} -o ${TO}/out ${files} ${testfiles} ${TO}/test_main.o \
               ${plugins_o} ${LDFLAGS} ${CFLAGS} $S/configuration.cc -Dtesting
	./${TO}/out

tags:
	@mkdir -p plugins
	etags `find $S -name '*.cc' -o -name '*.hh'` \
              `[ "$$(ls plugins)" ] && \
               [ "$$(find plugins -name src -type d)" ] && \
                  find plugins -name src -type d \
                    | xargs -n 1 printf "find %s -type f\n" \
                    | bash;`

regen:
	@mkdir -p plugins
	grep -n '######################################################################' Makefile \
             | tail -n 1 \
             | perl -pe 's/(\d+):.*/$$1/' \
             | xargs printf 'head -n%s Makefile\n' \
             | bash \
             | cat > newMakefile
	for file in $$(find $S -name '*.cc'); do \
             cpp -MM $$file -Isrc ${plugins_hh} ${Dtesting} | perl -pe 's|^([^ ].*)|\$$O/$$1|' >> newMakefile; \
             echo '	@mkdir -p $$O plugins' >> newMakefile; \
             echo '	$${CXX} -o $$@ -c $$< $${CFLAGS} $${plugins_hh} ${Dtesting}' >> newMakefile; \
        done
	for file in $$(find $T -name '*.cc'); do \
             cpp -MM $$file -Isrc ${plugins_hh} ${Dtesting} | perl -pe 's|^([^ ].*)|\$${TO}/$$1|' >> newMakefile; \
             echo '	@mkdir -p $${TO} plugins' >> newMakefile; \
             echo '	$${CXX} -o $$@ -c $$< $${CFLAGS} $${plugins_hh} ${Dtesting}' >> newMakefile; \
        done
	mv newMakefile Makefile

######################################################################
# Everything (including this) will be deleted by ``make regen``
