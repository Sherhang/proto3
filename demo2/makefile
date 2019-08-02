CXX = g++ -std=c++11

src = $(wildcard *.cpp) $(wildcard *.cc)
target = demo 

INCS = 
LIBS = -lpthread  -lprotobuf `pkg-config --cflags --libs protobuf`

CFLAGS += -g 

$(target): $(src)   	
	$(CXX) $(INCS) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY:all clean
clean:
	@echo "clean all .o and exe: "
	rm -rf   $(target) *.cc *.h *.txt
