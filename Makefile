CXX = gcc

SRCS = $(wildcard Source/*.c)

build: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(CXXLIBS)

clean:
	rm -f build

.PHONY: clean
