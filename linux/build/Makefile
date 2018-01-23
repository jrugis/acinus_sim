###########################################################################################
## defaults
EXE = parotid_sim
CPP_DEFS = -fopenmp -std=c++11

###########################################################################################
## NOTE: uncomment for ...
#CPP_DEFS = -DVIENNACL_WITH_OPENMP -fopenmp -std=c++11

###########################################################################################
## NOTE: uncomment block for ONE of debug, profile or optimised

## debug
#EXE = parotid_sim_debug
#CPP_FLAGS =  $(CPP_DEFS) $(CPP_INCLUDES) -m64 -Og -Wall -Wextra

## profile
#CPP_FLAGS =  $(CPP_DEFS) $(CPP_INCLUDES) -m64 -O3 -pg 

## optimised
CPP_FLAGS =  $(CPP_DEFS) $(CPP_INCLUDES) -m64 -O3 -march=native -mtune=native 

###########################################################################################

CPP = g++
CPP_INCLUDES = -I/usr/include/eigen3

OBJS = main.o cParotid.o cAcinus.o cCell_x.o cVCLSolver.o cCellMesh.o
SRC = ../../src

all: $(EXE)

main.o: $(SRC)/main.cpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

cParotid.o: $(SRC)/cParotid.cpp $(SRC)/cParotid.hpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

cAcinus.o: $(SRC)/cAcinus.cpp $(SRC)/cAcinus.hpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

cCell_x.o: $(SRC)/cCell_x.cpp $(SRC)/cCell_x.hpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

cVCLSolver.o: $(SRC)/cVCLSolver.cpp $(SRC)/cVCLSolver.hpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

cCellMesh.o: $(SRC)/cCellMesh.cpp $(SRC)/cCellMesh.hpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

$(EXE): $(OBJS)
	$(CPP) $(CPP_FLAGS) -o ../test/$@ $+

clean:
	rm *.o


