CFLAGS = -I. -Wall -m32 -g

all: circlebuffer.out

CC=gcc

.c.o: 
	@echo --[CC]-- $<
	@$(CC) $(CFLAGS) -c $< -o $@

%.out:
	@echo --[OUT]-- $^
	@$(CC) $(CFLAGS) $^ $(LDFLAGS)  -o $@

%.a:
	@echo --[AR]-- $@
	@ar rcs $@ $^

%.d: %.c
	@echo --[DEP]-- $<
	@$(SHELL) -ec '$(CC) -MM -MQ $*.o $(CFLAGS) $< > $@'


sources = mirrorringbuffer.c mirrorringbuffer_test.c

ifneq ($(MAKECMDGOALS),mrproper)
ifneq ($(MAKECMDGOALS),clean)
-include $(sources:.c=.d)
endif
endif

circlebuffer.out: $(sources:.c=.o)

.PHONY: clean mrproper
clean:
	rm -f *.o *.out

mrproper: clean
	rm -f *.d
