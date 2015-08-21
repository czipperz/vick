CFLAGS=-lncurses -Wall
O=out
S=src
T=test
CC=g++

files = $O/newmove.o \
     $O/move.o \
     $O/key_listeners.o \
     $O/command_listeners.o \
     $O/show_message.o \
     $O/prefix_g.o \
     $O/int_to_str.o \
     $O/parse_init_contents.o \
     $O/configuration.o \
     $O/basic_commands.o \
     $O/file_contents.o

testfiles = ${TO}/int_to_str_tests.o \
     ${TO}/main.o \
     ${TO}/newmove_tests.o

all: testVI

testVI: ${files} $O/main.o
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

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CC} -o $@ -c $< $(CFLAGS)

$T/UnitTest++/Posix/%.o: $T/UnitTest++/Posix/%.cpp
	${CC} -o $@ -c $<

$T/UnitTest++/%.o: $T/UnitTest++/%.cpp
	${CC} -o $@ -c $<

clean:
	[ ! -d out ] || rm -R out
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ -z "`find -name '*.o'`" ] || rm `find -name '*.o'`

test: testVI $T/UnitTest++/AssertException.o \
             $T/UnitTest++/CurrentTest.o \
             $T/UnitTest++/MemoryOutStream.o \
             $T/UnitTest++/TestDetails.o \
             $T/UnitTest++/TestReporterStdout.o \
             $T/UnitTest++/TimeConstraint.o \
             $T/UnitTest++/Checks.o \
             $T/UnitTest++/DeferredTestReporter.o \
             $T/UnitTest++/ReportAssert.o \
             $T/UnitTest++/TestList.o \
             $T/UnitTest++/TestResults.o \
             $T/UnitTest++/XmlTestReporter.o \
             $T/UnitTest++/CompositeTestReporter.o \
             $T/UnitTest++/DeferredTestResult.o \
             $T/UnitTest++/Test.o \
             $T/UnitTest++/TestReporter.o \
             $T/UnitTest++/TestRunner.o \
             $T/UnitTest++/Posix/SignalTranslator.o \
             $T/UnitTest++/Posix/TimeHelpers.o \
             ${testfiles}
	${CC} -o $T/out \
             ${testfiles} \
             $T/UnitTest++/AssertException.o \
             $T/UnitTest++/CurrentTest.o \
             $T/UnitTest++/MemoryOutStream.o \
             $T/UnitTest++/TestDetails.o \
             $T/UnitTest++/TestReporterStdout.o \
             $T/UnitTest++/TimeConstraint.o \
             $T/UnitTest++/Checks.o \
             $T/UnitTest++/DeferredTestReporter.o \
             $T/UnitTest++/ReportAssert.o \
             $T/UnitTest++/TestList.o \
             $T/UnitTest++/TestResults.o \
             $T/UnitTest++/XmlTestReporter.o \
             $T/UnitTest++/CompositeTestReporter.o \
             $T/UnitTest++/DeferredTestResult.o \
             $T/UnitTest++/Test.o \
             $T/UnitTest++/TestReporter.o \
             $T/UnitTest++/TestRunner.o \
             $T/UnitTest++/Posix/SignalTranslator.o \
             $T/UnitTest++/Posix/TimeHelpers.o \
             ${files} \
             ${CFLAGS}
	./$T/out
