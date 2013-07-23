GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = utility.o pa05.o
HDRS = pa05.h
TARGET = pa05
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06

pa05: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06

test_ch01: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase1_ch outputs/output_ch01
	diff expected/ch_expected/solution1 outputs/output_ch01
	$(VALGRIND) --log-file=outputs/memoutput_ch01 ./pa05 inputs/ch_header_inputs/testcase1_ch outputs/output_ch01 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch01 

test_ch02: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase2_ch outputs/output_ch02
	diff expected/ch_expected/solution2 outputs/output_ch02
	$(VALGRIND) --log-file=outputs/memoutput_ch02 ./pa05 inputs/ch_header_inputs/testcase2_ch outputs/output_ch02 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch02

test_ch03: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase3_ch outputs/output_ch03
	diff expected/ch_expected/solution3 outputs/output_ch03
	$(VALGRIND) --log-file=outputs/memoutput_ch03 ./pa05 inputs/ch_header_inputs/testcase3_ch outputs/output_ch03 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch03

test_ch04: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase4_ch outputs/output_ch04
	diff expected/ch_expected/solution4 outputs/output_ch04
	$(VALGRIND) --log-file=outputs/memoutput_ch04 ./pa05 inputs/ch_header_inputs/testcase4_ch outputs/output_ch04 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch04

test_ch05: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase5_ch outputs/output_ch05
	diff expected/ch_expected/solution5 outputs/output_ch05
	$(VALGRIND) --log-file=outputs/memoutput_ch05 ./pa05 inputs/ch_header_inputs/testcase5_ch outputs/output_ch05 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch05

test_ch06: $(TARGET) | environment
	./$(TARGET) inputs/ch_header_inputs/testcase6_ch outputs/output_ch06
	diff expected/ch_expected/solution6 outputs/output_ch06
	$(VALGRIND) --log-file=outputs/memoutput_ch06 ./pa05 inputs/ch_header_inputs/testcase6_ch outputs/output_ch06 >/dev/null
	@bin/valgrind-checker.sh outputs/memoutput_ch06

test_bit01: $(TARGET) | environment
	./$(TARGET) inputs/bit_header_inputs/description_bit outputs/output_bit01
	diff expected/bit_expected/description_sol outputs/output_bit01
	$(VALGRIND) --log-file=outputs/memoutput_bit01 ./pa05 inputs/bit_header_inputs/description_bit outputs/output_bit01
	@bin/valgrind-checker.sh outputs/memoutput_bit01

test_bit02: $(TARGET) | environment
	./$(TARGET) inputs/bit_header_inputs/gophers_bit outputs/output_bit02
	diff expected/bit_expected/gophers_sol outputs/output_bit02
	$(VALGRIND) --log-file=outputs/memoutput_bit02 ./pa05 inputs/bit_header_inputs/gophers_bit outputs/output_bit02
	@bin/valgrind-checker.sh outputs/memoutput_bit02