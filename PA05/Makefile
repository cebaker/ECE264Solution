GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --leak-check=yes --verbose

answer05:  answer05.o bst.o tree.o
	$(GCC) $(CFLAGS)  bst.o  tree.o answer05.o -o answer05

answer05.o: answer05.c
	$(GCC) $(CFLAGS)  -c answer05.c

bst.o: utility.h bst.c
	$(GCC) $(CFLAGS)  -c bst.c

clean:
	rm *.o answer05

test:  answer05
	./answer05 inputs/bit_header_inputs/description_bit outputs/output_bit01
	diff expected/bit_expected/description_sol outputs/output_bit01
	./answer05 inputs/bit_header_inputs/gophers_bit outputs/output_bit02
	diff expected/bit_expected/gophers_sol outputs/output_bit02
	./answer05 inputs/bit_header_inputs/poetry1_bit outputs/output_bit03
	diff expected/bit_expected/poetry1_sol outputs/output_bit03
	./answer05 inputs/bit_header_inputs/poetry2_bit outputs/output_bit04
	diff expected/bit_expected/poetry2_sol outputs/output_bit04
	./answer05  inputs/bit_header_inputs/prefixcodes_bit outputs/output_bit05
	diff expected/bit_expected/prefixcodes_sol outputs/output_bit05
	./answer05 inputs/bit_header_inputs/stone_bit outputs/output_bit06
	diff expected/bit_expected/stone_sol outputs/output_bit06
	./answer05 inputs/bit_header_inputs/woods_bit outputs/output_bit07
	diff expected/bit_expected/woods_sol outputs/output_bit07

# In this testcase, make test will display an error message.  Since in
# this case we'll have return value 1 while make expects 0.


testmem: answer05
	$(VALGRIND) --log-file=outputs/memoutput_bit01 ./pa05 inputs/bit_header_inputs/description_bit outputs/output_bit01
	
	$(VALGRIND) --log-file=outputs/memoutput_bit02 ./pa05 inputs/bit_header_inputs/gophers_bit outputs/output_bit02
	
	$(VALGRIND) --log-file=outputs/memoutput_bit03 ./pa05 inputs/bit_header_inputs/poetry1_bit outputs/output_bit03
	
	$(VALGRIND) --log-file=outputs/memoutput_bit04 ./pa05 inputs/bit_header_inputs/poetry2_bit outputs/output_bit04
	
	$(VALGRIND) --log-file=outputs/memoutput_bit05 ./pa05 inputs/bit_header_inputs/prefixcodes_bit outputs/output_bit05
	
	$(VALGRIND) --log-file=outputs/memoutput_bit06 ./pa05 inputs/bit_header_inputs/stone_bit outputs/output_bit06
	
	$(VALGRIND) --log-file=outputs/memoutput_bit07 ./pa05 inputs/bit_header_inputs/woods_bit outputs/output_bit07