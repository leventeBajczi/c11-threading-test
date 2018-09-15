.PHONY: run build clean

objects := $(patsubst src/%.c,build/obj/%.o,$(wildcard src/*.c))

flags := -static -pthread

CC=riscv64-linux-gnu-gcc

out := build/riscv.bin

QEMU=qemu-riscv64

GDB=gdb

run: build
	$(QEMU) $(out)

build: $(objects)
	$(CC) $(flags) -O0 -g -o $(out) $(objects)

%.o:
	mkdir -p $(dir $@)
	$(CC) -c -g -o $@ $(patsubst build/obj/%.o,src/%.c,$@)

debug:
	$(MAKE) build CC=gcc
	$(GDB) $(out)

clean:
	rm -rf build
