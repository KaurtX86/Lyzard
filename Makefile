CPP = g++

compile-lyzard:
	@mkdir -p bin
	${CPP} *.cxx -o ./bin/lyzard

install:
	@if ! [ "$(shell id -u)" = 0 ]; then\
		cp ./bin/lyzard ~/.local/bin/lyzard;\
	else\
		cp ./bin/lyzard /usr/local/bin/lyzard;\
	fi

uninstall:
	@if ! [ "$(shell id -u)" = 0 ]; then\
		rm ~/.local/bin/lyzard;\
	else\
		rm /usr/local/bin/lyzard;\
	fi

clean:
	@rm -r ./bin

help:
	@echo "Available targets:"
	@echo "compile-lyzard - compile to to bin/lyzard"
	@echo "clean - remove binary from bin"
	@echo "install - copy binary to /usr/local/bin if root, else to ~/.local/bin"
	@echo "uninstall - remove binary from /usr/local/bin if root, else from ~/.local/bin"
	@echo "Default target: compile-lyzard"
	@echo ""
