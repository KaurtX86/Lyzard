CC = g++

compile-lyzard:
	mkdir -p bin
	${CC} *.cxx -o ./bin/lyzard

install:
	@if ! [ "$(shell id -u)" = 0 ]; then
		@echo "You are not root, run this target as root please"
		exit 1
	fi
	mv ./bin/lyzard

clean:
	rm -rf bin

help:
	echo "Available targets:"
	echo "compile-lyzard -- ...in to bin/lyzard"
	echo "install -- ... bin/lyzard in /usr/local/bin/lyzard"
	echo "clean -- delete bin/ after compile-lyzard"

