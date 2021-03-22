.PHONY: all
all: format test build

.PHONY: format
format:
	clang-format src/* include/* -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: test
test:
	g++-9 -std=c++17 test.cpp src/format.cpp src/process.cpp src/processor.cpp src/linux_parser.cpp src/system.cpp -Iinclude

.PHONY: test-clean
test-clean:
	rm a.out