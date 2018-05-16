mingw-debug:
	gcc -o build/plating-tests.exe src/test/PlatingTests.c -g

gcc-expand-macros:
	gcc -o src/test/PlatingTests-expanded.c src/test/PlatingTests.c -E

mingw-debug-expanded: gcc-expand-macros
	gcc -o build/plating-tests.exe src/test/PlatingTests-expanded.c -g