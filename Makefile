
C=gcc 
CFLAGS= -g -pedantic -Wall -Wextra

all: final
final: final.cxx dataAnalysis.cxx train.cxx naiveMetric.cxx SynScan.cxx
  $(C) $(CFLAGS) -o final.exe final.cxx dataAnalysis.cxx train.cxx naiveMetric.cxx SynScan.cxx -lm

clean: 
  rm -f final.exe
