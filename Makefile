
CPPC:=g++
CPPFLAGS:= -c -Wall -std=c++0x -ggdb -I.
LD:=g++
LDFLAGS:= -lGL -lSDL 
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
	$(LD) $(LDFLAGS) -o $@ $^

$(BINDIR)/%.o: %.cpp Makefile
	$(CPPC) $(CPPFLAGS) -o $@ $<
	$(CPPC) -MM -MT $@ $(MMFLAGS) $< > $(BINDIR)/$*.d

.PHONY: clean

clean:
	-@ rm -f tgwave $(BINDIR)/*.o $(BINDIR)/*.d $(BINDIR)/*/*.o $(BINDIR)/*/*.d $(BINDIR)/*/*/*.o $(BINDIR)/*/*/*.d
