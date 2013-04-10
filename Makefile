# libbiscuit
# shane tully (shane@shanetully.com)
# shanetully.com

CC=gcc
LANG=c

PROJ_NAME = libbiscuit
VERSION = "\"1.0.0\""

SO          = $(PROJ_NAME).so
ARCHIVE     = $(PROJ_NAME).a
TEST_BINARY = bisc_unit_tests

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.$(LANG)=.o)

TEST_SOURCES = $(wildcard tests/*.c)

INCLUDE_DIRS = -Iinclude/

TEST_LIB_INCLUDE_DIRS = -Lbin/static
TEST_LIBS = -lbiscuit -lcunit

CFLAGS      = -std=c99 -Wall -Wextra $(INCLUDE_DIRS) -fPIC -DVERSION=$(VERSION) -D_BSD_SOURCE
TEST_CFLAGS = -std=c99 -Wall -Wextra $(INCLUDE_DIRS)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb -DDEBUG
else
	CFLAGS += -O2
endif

.PHONY = all test install remove clean

all: $(OBJECTS)
	$(CC) -shared -o bin/shared/$(SO) $^
	ar rcs bin/static/$(ARCHIVE) $(OBJECTS)

test: all
	$(CC) $(TEST_CFLAGS) -o bin/tests/$(TEST_BINARY) $(TEST_SOURCES) $(TEST_LIB_INCLUDE_DIRS) $(TEST_LIBS)
	bin/tests/$(TEST_BINARY)

install:
	echo "Not implemented."

remove:
	rm $(INSTALL_DIR)$(BINARY)

.$(LANG).o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f bin/shared/$(SO)
	rm -f bin/static/$(ARCHIVE)
	rm -f bin/tests/$(TEST_BINARY)
