# Parallel implementation of the Square-root velu formulas for SQALE'd CSIDH 

This repository ilustrates the practical speedups obtained from parallelizing the new square-root velu formulas, both on
their own and as part of the CSIDH protocol, SQALE'd CSIDH, and CTIDH.
## Description of the C-code implementation

The C-code is an adaptation of the one in https://github.com/JJChiDguez/sqale-csidh-velusqrt introducing parallel square-root velu algorithms
using OpenMP with 2 or 4 cores.

The implementation works for the original CSIDH primes (https://eprint.iacr.org/2018/383): p512, p1024, p1792 
as well as the ones introduced in SQALE'd CSIDH (https://eprint.iacr.org/2020/1520): p2048, p3072, p4096, p5120, p6144, p8192, p9216
and each implementation is available in OAYT style (`wd1`), MCR style (`wd2`) and dummy-free style (`df`) as described in https://eprint.iacr.org/2020/1520.

For the primes p512, p1024 and p2048, a simulation of the CTIDH protocol is available by using the `ctidh` style. Note that this implementation does not
compute the actual group action of CTIDH, but simulates its constant-time cost by performing only isogenies of the largest degree per batch.

### Compilation
```
The syntax and option for the compilation can be check by running `make help`, which prints the following

Syntax:
        make [csidh/bench/bench_isog/tune] BITS=[512/1024/1792/2048/3072/4096/5120/6144/8192/9216] STYLE=[wd1/wd2/df/ctidh] CORES=[1/2/4]

Options:
        csidh - compute a randomized instance of the protocol
        bench - benchmark several instances of the protocol
        bench_isog - benchmark the performace of idividual isogenies of each degree (does not require STYLE)
        tune - the exhaustive search program to tune the ijk parameters of square-root velu (does not require STYLE)

        BITS - the prime size
        STYLE - choice of MCR(wd1), OAYT (wd2), dummy-free (df) or ctidh (only available for p512 and p1024)
        CORES - number of cores

Tests:
        make test BITS=[512/1024/1792/2048/3072/4096/5120/6144/8192/9216]

        Compiles binaries for tests at all the layers of the code.

Cleanup:
        make clean
        make deepclean
```

### Examples of runs
```bash
# Tests
make test BITS=1024
./fp-1024.test
./poly_mul_fp1024.test
./poly_redc_fp1024.test
./mont-fp1024.test
./isog-fp1024.test
# One run of equential CSIDH
make csidh BITS=2048 STYLE=wd2 CORES=1
./csidh.2048-wd2.main
# Benchmark of parallel SQALE'd CSIDH
make bench BITS=4096 STYLE=df CORES=2
./csidh-4096-df-2core.bench
```

## License

This project is licensed under the GNU general public license - see the [LICENSE](LICENSE) file for details