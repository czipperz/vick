plugins_o  = `[ "$$(ls plugins)" ] && \
              [ "$$(find plugins -name out -type d)" ] && \
                 find plugins -name out -type d \
                   | xargs -n 1 printf "find %s -type f\n" \
                   | bash;`
plugins_hh = `[ "$$(ls plugins)" ] && \
              [ "$$(find plugins -name src -type d)" ] && \
                 find plugins -name src -type d \
                   | xargs -n 1 printf "-I%s\n"` -Isrc
CFLAGS=-std=c++11 \
       -Wold-style-cast -Wnon-virtual-dtor -Wnarrowing \
       -Wdelete-non-virtual-dtor -Wctor-dtor-privacy \
       -Woverloaded-virtual -Wsign-promo
LDFLAGS=-lboost_regex -lncurses -lpthread
O=out
S=src
T=test
TO=testout
CXX=clang++
B=vick

ifeq (${CXX},g++)
CFLAGS += -Wstrict-null-sentinel -Wnoexcept
endif

.PHONY: all begin clean doc test tags regen

files=$O/basic_commands.o     \
      $O/change.o             \
      $O/contents.o           \
      $O/command_listeners.o  \
      $O/file_contents.o      \
      $O/hooks.o              \
      $O/inter_space.o        \
      $O/key_listeners.o      \
      $O/mode.o               \
      $O/prefix.o             \
      $O/prefix_key.o         \
      $O/prompt.o             \
      $O/show_message.o       \
      $O/visual.o             \

testfiles = ${TO}/inter_space_tests.o        \
            ${TO}/visual_tests.o             \

all: ${files} $O/main.o $O/configuration.o
	@mkdir -p plugins
	@for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do          \
             cd $$dir;                                                          \
             make CXX="${CXX}" CFLAGS="${CFLAGS}" -j 5 || exit $$!; cd ../..;   \
        done
	${CXX} -o $B ${plugins_o} $^ ${LDFLAGS}

begin:
	@mkdir -p plugins
	git pull
	[ -d plugins/vick-move ] || git clone 'https://github.com/czipperz/vick-move' plugins/vick-move
	cd plugins/vick-move && make begin
	[ -d plugins/vick-insert-mode ] || git clone 'https://github.com/czipperz/vick-insert-mode' plugins/vick-insert-mode
	cd plugins/vick-insert-mode && make begin
	[ -d plugins/vick-find ] || git clone 'https://github.com/czipperz/vick-find' plugins/vick-find
	cd plugins/vick-find && make begin
	[ -d plugins/vick-open-line ] || git clone 'https://github.com/czipperz/vick-open-line' plugins/vick-open-line
	cd plugins/vick-open-line && make begin
	[ -d plugins/vick-join ] || git clone 'https://github.com/czipperz/vick-join' plugins/vick-join
	cd plugins/vick-join && make begin

clean:
	@mkdir -p plugins
	@for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX="${CXX}" CFLAGS="${CFLAGS}" clean || exit $$!; cd ../..; \
        done
	[ ! -d $O ] || rm -R $O
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ -z "`find -name '#*#'`" ] || rm `find -name '#*#'`
	[ ! -e $B ] || rm $B
	[ ! -d ${TO} ] || rm -R ${TO}

doc:
	(cat Doxyfile && echo INPUT = src $$([ "$$(ls plugins)" ] && \
                                             [ "$$(find plugins -name out -type d)" ] && \
                                             find plugins -name src -type d)) \
              > Doxyfile.$$ && ( \
        doxygen Doxyfile.$$; \
        rm Doxyfile.$$)

test: ${files} ${testfiles} ${TO}/test_main.o
	@mkdir -p plugins
	@for dir in `find plugins -maxdepth 1 -mindepth 1 -type d`; do \
             cd $$dir; \
             make CXX="${CXX}" CFLAGS="${CFLAGS}" test -j 5 || exit $$!; cd ../..; \
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
	@for file in $$(find $S -name '*.cc'); do \
             cpp -MM -std=c++11 $$file -Isrc ${plugins_hh} ${Dtesting} | perl -pe 's|^([^ ].*)|\$$O/$$1|' >> newMakefile; \
             echo '	@mkdir -p $$O plugins' >> newMakefile; \
             echo '	$${CXX} -o $$@ -c $$< $${CFLAGS} $${plugins_hh} ${Dtesting}' >> newMakefile; \
        done
	@for file in $$(find $T -name '*.cc'); do \
             cpp -MM -std=c++11 $$file -Isrc ${plugins_hh} ${Dtesting} | perl -pe 's|^([^ ].*)|\$${TO}/$$1|' >> newMakefile; \
             echo '	@mkdir -p $${TO} plugins' >> newMakefile; \
             echo '	$${CXX} -o $$@ -c $$< $${CFLAGS} $${plugins_hh} ${Dtesting}' >> newMakefile; \
        done
	mv newMakefile Makefile

######################################################################
# Everything past and including this will be deleted by ``make regen``
