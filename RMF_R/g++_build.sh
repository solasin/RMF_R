#! /bin/bash

g++ -o rmfr_1M *.cpp -fopenmp -O3 -I/opt/intel/mkl/include -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64 -lm -lmkl_intel_lp64 -lmkl_intel_thread -liomp5 -lmkl_core -lpthread -mfpmath=sse -mmmx -msse -msse2 -msse3 -m3dnow -mssse3 -msse4 -maccumulate-outgoing-args -minline-stringops-dynamically -momit-leaf-frame-pointer -m64 --fast-math

