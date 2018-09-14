.PHONY: run build clean

objects := $(patsubst src/%.c,build/obj/%.o,$(wildcard src/*.c))

flags := -static -pthread

CC=riscv64-linux-gnu-gcc

out := build/riscv.bin

QEMU=qemu-riscv64

run: build
	$(QEMU) $(out)

build: $(objects)
	$(CC) $(flags) -o $(out) $(objects)

%.o:
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $(patsubst build/obj/%.o,src/%.c,$@)

clean:
	rm -rf build