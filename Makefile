LIBS=-lcppunit
CPPFLAGS=-Wall -g
LDFLAGS=
CPPSOURCES = $(wildcard *.cpp)
CSOURCES = $(wildcard *.c)
all: KindaC
KindaC: $(CPPSOURCES:.cpp=.o) $(CSOURCES:.c=.o)
	g++ -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	g++ -c $< $(CPPFLAGS) -o $@

%.o: %.c
	g++ -c $< $(CPPFLAGS) -o $@
clean:
	-rm -f *.o KindaC *~
remade:
	$(MAKE) clean
	$(MAKE)

-include: $(CPPSOURCES:.cpp=.d) $(CSOURCES:.c=.d)
%.d: %.cpp
	g++ $< -MM -MT ’$*.o $*.d ’ -MD $(CPPFLAGS)
