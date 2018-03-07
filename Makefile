CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt phonebook_hash phonebook_bst phonebook_memorypool phonebook_smaz
all: $(EXEC) phonebook_fuzzy

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		-DOPT=0 \
		$(SRCS_common) $@.c

phonebook_hash: $(SRCS_common) phonebook_hash.c phonebook_hash.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
                -DIMPL="\"$@.h\"" -o $@ \
                -DHASH=0 \
                $(SRCS_common) $@.c

phonebook_bst: $(SRCS_common) phonebook_bst.c phonebook_bst.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
				-DIMPL="\"$@.h\"" -o $@ \
				-DBST=0 \
				$(SRCS_common) $@.c
 
phonebook_memorypool: $(SRCS_common) phonebook_memorypool.c phonebook_memorypool.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
				-DIMPL="\"$@.h\"" -o $@ \
				-DPOOL=0 \
				$(SRCS_common) $@.c

phonebook_smaz: $(SRCS_common) phonebook_smaz.c phonebook_smaz.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
				-DIMPL="\"$@.h\"" -o $@ \
				-DSMAZ=0\
				$(SRCS_common) $@.c

phonebook_fuzzy: $(SRCS_common) phonebook_fuzzy.c phonebook_fuzzy.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
				-DIMPL="\"$@.h\"" -o $@ \
				-DFUZZY=0\
				$(SRCS_common) $@.c


run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt
	perf stat --repeat 100 \
                -e cache-misses,cache-references,instructions,cycles \
                ./phonebook_hash
	perf stat --repeat 100 \
 				-e cache-misses,cache-references,instructions,cycles \
				./phonebook_bst
	perf stat --repeat 100 \
                -e cache-misses,cache-references,instructions,cycles \
                ./phonebook_memorypool
	perf stat --repeat 100 \
                -e cache-misses,cache-references,instructions,cycles \
                ./phonebook_smaz


output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png bst.txt hash.txt memorypool.txt smaz.txt phonebook_fuzzy
