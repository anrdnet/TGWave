
CPPC:=g++
CPPFLAGS:= -c -Wall -std=c++0x -I. -O3 -ffast-math 
LD:=g++
LDFLAGS:= -lGL -lSDL -lGLU -O3 -ffast-math
MMFLAGS:= -I.
BINDIR:=bin
CPPSRCFILES:=$(shell find -mindepth 0 -maxdepth 3 -name "*.cpp")
OBJFILES:=$(patsubst %.cpp, $(BINDIR)/%.o, $(CPPSRCFILES))
DEPS:=$(OBJFILES:.o=.d)

.PHONY: all
all: tgwave
	@echo "Build successfull"

.PHONY: test
test: all
	./tgwave

-include $(DEPS)

tgwave: $(OBJFILES)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BINDIR)/%.o: %.cpp Makefile
	$(CPPC) $(CPPFLAGS) -o $@ $<
	$(CPPC) -MM -MT $@ $(MMFLAGS) $< > $(BINDIR)/$*.d

.PHONY: clean

clean:
	-@ rm -f tgwave
	-@ rm -f gmon.out
	-@ find $(BINDIR) -type f | xargs -- rm -f

run: test
