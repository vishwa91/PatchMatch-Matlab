OPENCV = `pkg-config --cflags --libs opencv`
CXXFLAGS = "-fopenmp -O3 -fPIC"
LDFLAGS = "-fopenmp"

all: 
	mex CXXFLAGS=$(CXXFLAGS) LDFLAGS=$(LDFLAGS) -I./ pm_mex.cpp pm.cpp utils.cpp $(OPENCV)

clean:
	rm -rf pm_mex.mex*

