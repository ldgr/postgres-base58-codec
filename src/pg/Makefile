MODULES = base58

PG_CONFIG = pg_config
PGXS = $(shell $(PG_CONFIG) --pgxs)
INCLUDEDIR = $(shell $(PG_CONFIG) --includedir-server)
include $(PGXS)

base58.so: base58.o
	gcc -shared -o ../../target/base58.so ../../target/base58.o ../../target/base58_codec.o -I../../src -lgmp

base58.o: base58.c
	gcc -o ../../target/base58.o -c base58.c $(CFLAGS) -I$(INCLUDEDIR) -I../../src -lgmp

install:
	cp ../../target/base58.so `pg_config --pkglibdir`
