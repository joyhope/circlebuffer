CFLAGS = -I. -Wall -m32 -g

ifeq ($(OSTYPE),linux)
EXE =
else
EXE = .exe
endif

all: circlebuffer$(EXE)

CC=gcc

.c.o: 
	@echo [CC]: $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.out:
	@echo [OUT]: $^
	@$(CC) $(CFLAGS) $^ $(LDFLAGS)  -o $@

%.exe:
	@echo [EXE]: $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(sources)

%.a:
	@echo [AR]: $@
	@ar rcs $@ $^

%.d: %.c
	@echo [DEP]: $<
	@$(SHELL) -ec '$(CC) -MM -MQ $*.o $(CFLAGS) $< > $@'


sources = mirrorringbuffer.c mirrorringbuffer_test.c

ifneq ($(MAKECMDGOALS),mrproper)
ifneq ($(MAKECMDGOALS),clean)
-include $(sources:.c=.d)
endif
endif

circlebuffer$(EXE): $(sources:.c=.o)

.PHONY: clean mrproper
clean:
	rm -f *.o *.out, *$(EXE)

mrproper: clean
	rm -f *.d
