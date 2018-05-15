mingw: build/plating-tests.exe
gcc: build/plating-tests

build/plating-tests.exe:
	gcc -o build/plating-tests.exe src/test/PlatingTests.c -g

build/plating-tests:
	gcc -o build/plating-tests src/test/PlatingTests.c -g