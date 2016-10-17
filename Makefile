all: build
	rm ./build/gui
	cd src/gui && qmake && make
	ln -s $(shell pwd)/src/gui/build/debug/gui.app/Contents/MacOS/gui ./build/gui

clean:
	cd src/gui && qmake && make clean

build:
	mkdir build

run:
	./build/gui
