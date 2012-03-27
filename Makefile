
CPPC:=g++
INCFLAGS:= -I. $(shell pkg-config --cflags gtkmm-3.0)
CPPFLAGS:= -c -Wall -std=c++0x -O3 -ffast-math $(INCFLAGS)
LD:=g++
LDFLAGS:= -lGL -lSDL -lGLU -O3 -ffast-math $(shell pkg-config --libs gtkmm-3.0)
MMFLAGS:= $(INCFLAGS)
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
