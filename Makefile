LIBS=-lcppunit
CPPFLAGS=-Wall -g
LDFLAGS=
CPPSOURCES = $(wildcard *.cpp)
CSOURCES = $(wildcard *.c)
all: ftest
ftest: $(CPPSOURCES:.cpp=.o) $(CSOURCES:.c=.o)
	echo Criando arquivo execut´avel: $@
	g++ -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	echo Compilando arquivo objeto: $@
	g++ -c $< $(CPPFLAGS) -o $@

%.o: %.c
	echo Compilando arquivo objeto: $@
	g++ -c $< $(CPPFLAGS) -o $@
clean:
	echo Limpando arquivos
	-rm -f *.o ftest *~
remade:
	$(MAKE) clean
	$(MAKE)
-include: $(CPPSOURCES:.cpp=.d) $(CSOURCES:.c=.d)
%.d: %.cpp
	g++ $< -MM -MT ’$*.o $*.d ’ -MD $(CPPFLAGS)
