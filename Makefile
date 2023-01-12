SRC_DIR=src
INC_DIR=include
STRATEGY=include/strategy
SDAC_DIR=include/sdacs
IJK_DIR=include/ijk
PIJK_DIR=include/pijk
ASM_DIR=src/fp
OBJ_DIR=obj
TEST=test
MAIN=main

SCC=gcc 
GCCFLAGS=-O3 -Os -Wall -Wextra -funroll-loops -fomit-frame-pointer -m64 -mbmi2 -no-pie -fopenmp -fcommon
CLANGFLAGS=-O3 -Os -march=native -mtune=native -std=gnu99 -pedantic -Wall -Wextra -fopenmp\ -fcommon
DEBUG=-fsanitize=undefined -fsanitize=address
VALGRIND=-g


# -------------------------------
ifeq ($(findstring clang,$(CC)),)
  CFLAGS=$(GCCFLAGS)
else
  CFLAGS=$(CLANGFLAGS)
endif
# -------------------------------

SOPs=$(wildcard include/sdacs/p*)
PRIMES=$(SOPs:include/sdacs/p%.h=%)

all: csidh-all bench-all isog_bench-all

test: config fp$(BITS).test \
	mont-fp$(BITS).test \
	poly_mul_fp$(BITS).test \
	poly_redc_fp$(BITS).test 

	make isog-test BITS=$(BITS) CORES=1
	make isog-test BITS=$(BITS) CORES=2
	make isog-test BITS=$(BITS) CORES=4
	make gae-test BITS=$(BITS) STYLE=wd1 CORES=1
	make gae-test BITS=$(BITS) STYLE=wd2 CORES=1
	make gae-test BITS=$(BITS) STYLE=df  CORES=1
	make gae-test BITS=$(BITS) STYLE=wd1 CORES=2
	make gae-test BITS=$(BITS) STYLE=wd2 CORES=2
	make gae-test BITS=$(BITS) STYLE=df  CORES=2
	make gae-test BITS=$(BITS) STYLE=wd1 CORES=4
	make gae-test BITS=$(BITS) STYLE=wd2 CORES=4
	make gae-test BITS=$(BITS) STYLE=df  CORES=4

isog-test: isog-fp$(BITS)-$(CORES)core.test

gae-test: gae-$(STYLE)-fp$(BITS)-$(CORES)core.test

csidh: config csidh-$(BITS)-$(STYLE)-$(CORES)core.main

csidh-all:
	make csidh-all-styles CORES=1; \
	make csidh-all-styles CORES=2; \
	make csidh-all-styles CORES=4;

csidh-all-styles:
	@for b in $(PRIMES) ; do \
		make csidh BITS=$$b STYLE=wd2 CORES=$(CORES); \
		make csidh BITS=$$b STYLE=wd1 CORES=$(CORES) ; \
		make csidh BITS=$$b STYLE=df CORES=$(CORES) ; \
	done

bench: config csidh-$(BITS)-$(STYLE)-$(CORES)core.bench

bench-all: 
	make bench-all-styles CORES=1; \
	make bench-all-styles CORES=2; \
	make bench-all-styles CORES=4; \

bench-all-styles:
	@for b in $(PRIMES) ; do \
		make bench BITS=$$b STYLE=wd2 CORES=$(CORES) ; \
		make bench BITS=$$b STYLE=wd1 CORES=$(CORES) ; \
		make bench BITS=$$b STYLE=df CORES=$(CORES) ; \
	done

isog_bench: config csidh-$(BITS)-$(CORES)core.isog_bench

isog_bench-all:
	@for b in $(PRIMES) ; do \
		make isog_bench BITS=$$b CORES=1 ; \
		make isog_bench BITS=$$b CORES=2 ; \
		make isog_bench BITS=$$b CORES=4 ; \
	done

tune: config csidh-$(BITS)-$(STYLE)-$(CORES)core.tune

#====================================================================
#	 MAIN FILES
#====================================================================
# Test of a single CSIDH key exchange protocol
csidh-$(BITS)-$(STYLE)-$(CORES)core.main: $(MAIN)/csidh.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o \
	$(OBJ_DIR)/gae-$(STYLE)-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/csidh-$(BITS)-$(STYLE)-$(CORES)core.o
	$(CC) $(CFLAGS) -D$(STYLE) -DP$(BITS) -I$(INC_DIR) -DCORES=$(CORES) -o $@ $^
# Benchmark of the protocol
csidh-$(BITS)-$(STYLE)-$(CORES)core.bench: $(MAIN)/bench.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o \
	$(OBJ_DIR)/gae-$(STYLE)-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/csidh-$(BITS)-$(STYLE)-$(CORES)core.o
	$(CC) $(CFLAGS) -D$(STYLE) -DP$(BITS) -I$(INC_DIR) -DCORES=$(CORES) -o $@ $^ -lm
# Benchmark of each isogeny calculation
csidh-$(BITS)-$(CORES)core.isog_bench: $(MAIN)/isog_bench.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o 
	$(CC) $(CFLAGS) -DP$(BITS) -I$(INC_DIR) -DCORES=$(CORES) -o $@ $^ -lm
# Tuning the parameters for I,J,K sizes
csidh-$(BITS)-$(STYLE)-$(CORES)core.tune: $(MAIN)/tune.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o 
	$(CC) $(CFLAGS) -D$(STYLE) -DP$(BITS) -I$(INC_DIR) -DCORES=$(CORES) -o $@ $^ -lm
#====================================================================



#====================================================================
#	 TEST FILES
#====================================================================
# Tests regarding group action evaluation
gae-$(STYLE)-fp$(BITS)-$(CORES)core.test: $(TEST)/gae-$(STYLE).c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o \
	$(OBJ_DIR)/gae-$(STYLE)-fp$(BITS)-$(CORES)core.o 
	$(CC) $(CFLAGS) -D$(STYLE) -DP$(BITS) -DCORES=$(CORES) -I$(INC_DIR) -o $@ $^
# --------------------------------------------------------
# Tests regarding isogenies (kps, xeval, and xisog blocks)
isog-fp$(BITS)-$(CORES)core.test: $(TEST)/isog-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o \
	$(OBJ_DIR)/mont-fp$(BITS).o $(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o $(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o
	$(CC) $(CFLAGS) -DP$(BITS) -DCORES=$(CORES) -I$(INC_DIR) -o $@ $^
# --------------------------------------------------------
# Tests regarding Montgomery curve point arithmetic
mont-fp$(BITS).test: $(TEST)/mont-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/mont-fp$(BITS).o
	$(CC) $(CFLAGS) -DP$(BITS) -I$(INC_DIR) -o $@ $^
# ---------------------------------------------------------------------
# Tests regarding polynomial reduction in fp with assembly
poly_redc_fp$(BITS).test: $(TEST)/poly_redc-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o $(OBJ_DIR)/poly_redc_fp$(BITS).o
	$(CC) $(CFLAGS) -DP$(BITS) -I$(INC_DIR) -o $@ $^
# ---------------------------------------------------------------------
# Tests regarding polynomial multiplication in fp with assembly
poly_mul_fp$(BITS).test: $(TEST)/poly_mul-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o $(OBJ_DIR)/poly_mul_fp$(BITS).o
	$(CC) $(CFLAGS) -DP$(BITS) -I$(INC_DIR) -o $@ $^
# ---------------------------------------------------------------------------------
# Tests regarding to the prime field fp with assembly
fp$(BITS).test: $(TEST)/fp-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o
	$(CC) $(CFLAGS) -DP$(BITS) -I$(INC_DIR) -o fp$(BITS).test $(TEST)/fp-test.c $(OBJ_DIR)/rng.o $(OBJ_DIR)/uint$(BITS).o $(OBJ_DIR)/fp$(BITS).o
#====================================================================



#====================================================================
#	 OBJECT FILES
#====================================================================
# Objects corresponding with the key exchange procedures
$(OBJ_DIR)/csidh-$(BITS)-$(STYLE)-$(CORES)core.o: $(SRC_DIR)/csidh.c $(STRATEGY)/csidh-$(BITS)-$(STYLE).h $(INC_DIR)/styles.h $(INC_DIR)/csidh.h $(INC_DIR)/isog.h $(INC_DIR)/mont.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -D$(STYLE) -DP$(BITS) -DCORES=$(CORES) -c $< -o $@
# ----------------------------------------------------------------------------------------------------------------
#  Objects corresponding with the Group Action Evaluiation
$(OBJ_DIR)/gae-$(STYLE)-fp$(BITS)-$(CORES)core.o: $(SRC_DIR)/gae-$(STYLE).c $(STRATEGY)/csidh-$(BITS)-$(STYLE).h $(INC_DIR)/styles.h $(INC_DIR)/csidh.h $(INC_DIR)/isog.h $(INC_DIR)/mont.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -D$(STYLE) -DP$(BITS) -DCORES=$(CORES)  -c $< -o $@
# -----------------------------------------------------------------
#  Objects corresponding with xEVAL procedure
$(OBJ_DIR)/xeval-fp$(BITS)-$(CORES)core.o: $(SRC_DIR)/xeval.c $(INC_DIR)/isog.h $(INC_DIR)/mont.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) $(CFLAGS) -DP$(BITS) -DCORES=$(CORES) -c $< -o $@
# -----------------------------------------------------------------
#  Objects corresponding with xISOG procedure
$(OBJ_DIR)/xisog-fp$(BITS)-$(CORES)core.o: $(SRC_DIR)/xisog.c $(INC_DIR)/isog.h $(INC_DIR)/mont.h $(INC_DIR)/poly.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) $(CFLAGS) -DP$(BITS) -DCORES=$(CORES) -c $< -o $@
# -----------------------------------------------------------------
#  Objects corresponding with KPs
$(OBJ_DIR)/kps-fp$(BITS)-$(CORES)core.o: $(SRC_DIR)/kps.c $(INC_DIR)/isog.h $(INC_DIR)/mont.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) $(CFLAGS) -DP$(BITS) -DCORES=$(CORES) -c $< -o $@
# -----------------------------------------------------------------
#  Objects corresponding with the Montgomery curve point arithmetic
$(OBJ_DIR)/mont-fp$(BITS).o: $(SRC_DIR)/mont.c $(INC_DIR)/mont.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) $(CFLAGS) -DP$(BITS) -c $< -o $@
# -------------------------------------------------
# Objects corresponding to polynomial reduction
$(OBJ_DIR)/poly_redc_fp$(BITS).o: $(SRC_DIR)/poly_redc.c $(INC_DIR)/poly.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) -DP$(BITS) -c $< -o $@
# -------------------------------------------------
# Objects corresponding to polynomial multiplication
$(OBJ_DIR)/poly_mul_fp$(BITS).o: $(SRC_DIR)/poly_mul.c $(INC_DIR)/poly.h $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(IJK_DIR)/p$(BITS).h $(SDAC_DIR)/p$(BITS).h $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) -DP$(BITS) -c $< -o $@
# -------------------------------------------------------------------------------------------------------------
# Objects corresponding with the prime field arithmetic written in ASM code: just files with prejfix fp or uint
$(OBJ_DIR)/fp$(BITS).o: $(ASM_DIR)/fp$(BITS).s $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(INC_DIR)/rng.h
	$(SCC) -DP$(BITS) -c $< -o $@
$(OBJ_DIR)/uint$(BITS).o: $(ASM_DIR)/uint$(BITS).s $(INC_DIR)/fp.h $(INC_DIR)/primes.h $(INC_DIR)/rng.h
	$(SCC) -DP$(BITS) -c $< -o $@
# ------------------------------
# Object corresponding to the pseudo random number generator
$(OBJ_DIR)/rng.o: $(SRC_DIR)/rng.c $(INC_DIR)/rng.h
	$(CC) -I$(INC_DIR) -c $(SRC_DIR)/rng.c -o $@
#====================================================================


# ----------------
# Clean and Config 
clean:
	rm -f *.test
	rm -f *.main
	rm -f *.bench
	rm -f *.isog_bench
	rm -f *.tune

config:
	mkdir -p $(OBJ_DIR)

deepclean:
	rm -f $(OBJ_DIR)/*
	rm -f *.test
	rm -f *.main
	rm -f *.bench
	rm -f *.isog_bench
	rm -f *.tune
	rm -f *.valgrind

# ....................
# For help compilation
help:
	@echo "Syntax:"
	@echo "        make [csidh/bench/bench_isog/tune] BITS=[512/1024/1792/2048.3072/4096/5120/6144/8192/9216] STYLE=[wd1/wd2/df/ctidh] CORES=[1/2/4]"
	@echo ""
	@echo "Options:"
	@echo "        csidh - compute a randomized instance of the protocol"
	@echo "        bench - benchmark several instances of the protocol"
	@echo "        bench_isog - benchmark the performace of idividual isogenies of each degree (does not require STYLE)"
	@echo "        tune - the exhaustive search program to tune the ijk parameters of square-root velu (does not require STYLE)"
	@echo ""
	@echo "        BITS - the prime size"
	@echo "        STYLE - choice of MCR(wd1), OAYT (wd2), dummy-free (df) or ctidh (only available for p512 and p1024)"
	@echo "        CORES - number of cores"
	@echo ""
	@echo "Tests:"
	@echo "        make test BITS=[512/1024/1792/2048/3072/4096/5120/6144/8192/9216]"
	@echo ""
	@echo "        Compiles binaries for tests at all the layers of the code."
	@echo ""
	@echo "Cleanup:"
	@echo "        make clean"
	@echo "        make deepclean"

