# Parallel implementation of the Square-root velu formulas for SQALE'd CSIDH 

This repository ilustrates the practical speedups obtained from parallelizing the new square-root velu formulas, both on
their own and as part of the CSIDH protocol, SQALE'd CSIDH, and CTIDH.
## Description of the C-code implementation

The C-code is an adaptation of the one in https://github.com/JJChiDguez/sqale-csidh-velusqrt introducing parallel square-root velu algorithms
using OpenMP with 2, 4 or 8 cores.

The implementation works for the original CSIDH primes (https://eprint.iacr.org/2018/383): p512, p1024, p1792 
as well as the ones introduced in SQALE'd CSIDH (https://eprint.iacr.org/2020/1520): p2048, p3072, p4096, p5120, p6144, p8192, p9216
and each implementation is available in OAYT style (`wd1`), MCR style (`wd2`) and dummy-free style (`df`) as described in https://eprint.iacr.org/2020/1520.

We have incorporated a new 1792-bit prime

ptest:= 4FA4E8C57C4EFF02D0650FE3AFC0413536E72253101645B1387DA2DD519C17FBEC
69843C04DEAEA2DB59CDDDA7876B514C101A1DF0D96778BD72A3C51844BB0196
F73F1DDBFEC980A4BB3B200A4E618C54621ADB35B5E4B0545F5BE025D63
BC914AB11A882AD78B6203C57A31031B98B6C104DC99AC9A4532DEC0C293
0F8AE51B008E4BA6D26E56C736D3C067C8F2DFDF7F8206B444A42D39E0F4D82FF
3FD0EB1DF44B31DDCDE876E658489E1CA359DAF5868A6C22E8455B4A4F7679F6
2B0C30D8883D2B79931C19E4737C3CC33056461E9C96A175D94B594B2A9EAB4B6B6303

where ptest+1 is the product of 4 by 107 odd primes that are roughly evenly spaced between 19 and  321193 (the degree of the isogeny in the attack of https://eprint.iacr.org/2023/640).

### Compilation
```
The syntax and option for the compilation can be check by running `make help`, which prints the following

Syntax:
        make [csidh/bench/bench_isog/tune] BITS=[512/1024/1792/2048/3072/4096/5120/6144/8192/9216/test] STYLE=[df] CORES=[1/2/4/8]

Options:
        csidh - compute a randomized instance of the protocol
        bench - benchmark several instances of the protocol
        bench_isog - benchmark the performace of idividual isogenies of each degree (does not require STYLE)
        tune - the exhaustive search program to tune the ijk parameters of square-root velu (does not require STYLE)

        BITS - the prime size
        STYLE - choice of MCR(wd1), OAYT (wd2), dummy-free (df)
        CORES - number of cores (8 only available for ptest)

        *BITS=test only compatible with bench_isog* 

Tests:
        make test BITS=[512/1024/1792/2048/3072/4096/5120/6144/8192/9216/test] 

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
# One run of sequential CSIDH
make csidh BITS=2048 STYLE=wd2 CORES=1
./csidh.2048-wd2.main
# Benchmark parallel isogenies 
make bench-isog BITS=test STYLE=df CORES=2
./csidh-test-df-2core.bench-isog
```

## License

This project is licensed under the GNU general public license - see the [LICENSE](LICENSE) file for details
