# SIMD

## Support

Look for `sse4_2` and `avx` support in  `/proc/cpuinfo`.

## Building script
```bash
# Regular build
mkdir bin
gcc simd/simd.c -o bin/simd
bin/simd
```