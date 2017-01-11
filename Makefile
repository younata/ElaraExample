CC=clang

SPEC_SRC=$(filter-out Source/main.c, $(wildcard Spec/*.c) $(wildcard Source/*.c))
CFLAGS=-fblocks -ISpecDependencies/Elara/Elara -IInclude -g
SPEC_LFLAGS=-lelara -LSpecDependencies/Elara/Elara -lm

SPEC_OBJ=$(SPEC_SRC:.c=.o)

.PHONY: Elara clean

all: spec

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

Elara:
	cd SpecDependencies/Elara && make

examplespec: $(SPEC_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(SPEC_LFLAGS)

.PHONY: clean spec

spec: Elara examplespec
	DYLD_LIBRARY_PATH=SpecDependencies/Elara/Elara:$(DYLD_LIBRARY_PATH) ./examplespec

debugspec: Elara examplespec
	DYLD_LIBRARY_PATH=SpecDependencies/Elara/Elara:$(DYLD_LIBRARY_PATH) lldb examplespec

clean:
	rm -rf Spec/*.o
	rm -f examplespec
	cd SpecDependencies/Elara && make clean
