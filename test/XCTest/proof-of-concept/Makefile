SOURCES=main.c

CC=clang

all: compile_driver config.yaml

config.yaml:
	echo "fork: true" > config.yaml
	echo "bitcode_files:" >> config.yaml
	echo "  - $(PWD)/MUT_XCTestDriver.bc" >> config.yaml

compile_driver:
	clang -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/Library/Frameworks -c -emit-llvm MUT_XCTestDriver.m
	clang -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/Library/Frameworks -S -emit-llvm MUT_XCTestDriver.m

compile_test:
	clang -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/Library/Frameworks -S -emit-llvm XCTest_TwoTests.m

clean:
	rm -f config.yaml

