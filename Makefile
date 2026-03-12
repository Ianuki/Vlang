CXX = gcc

SRCS = $(wildcard Source/*.c)

build: $(SRCS)
	mkdir Builds
	$(CXX) $(CXXFLAGS) -o Builds/$@ $(SRCS) $(CXXLIBS)

clean:
	rm -f build

.PHONY: clean
