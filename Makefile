CC = gcc
CFLAGS = -Wall -g -std=c99
LIBS = -lgmp

compile:
	$(CC) $(CFLAGS) -fPIC -c -o target/base58_codec.o src/base58_codec.c $(LIBS)
	# ar rcs target/libbase58_codec.a target/base58_codec.o

test:
	$(CC) $(CFLAGS) -static -Isrc -o target/test_base58_codec src/base58_codec.c tests/test_base58_codec.c $(LIBS)
	tests/run_tests.sh
