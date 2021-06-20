CC=g++-9
ACC=arm-linux-gnueabi-g++-9

SRCDIR=src
TSTDIR=test
DBGDIR=debug
RELDIR=release
ANDDIR=android
LIBDIR=$(SRCDIR)/lib
INCDIR=$(SRCDIR)/include

BIN=contains

SRCNAM=main
SRCEXT=cpp
SRC=$(SRCNAM).$(SRCEXT)

SRCPTH=$(SRCDIR)/$(SRC)

TSTPTH=$(TSTDIR)/$(BIN)
DBGPTH=$(DBGDIR)/$(BIN)
RELPTH=$(RELDIR)/$(BIN)
ANDPTH=$(ANDDIR)/$(BIN).arm

CF_DBG=-g -Wall -Wextra -fsanitize=leak -fsanitize=address
CF_REL=-O2
CF_AND=$(CF_REL) -static -march=armv8-a

TSTARG=--help

$(SRCNAM): $(SRCPTH)
	mkdir -p $(RELDIR)
	$(CC) $(CF_REL) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(RELPTH)

android: $(SRCPTH)
	mkdir -p $(ANDDIR)
	$(ACC) $(CF_AND) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(ANDPTH)

debug:
	mkdir -p $(DBGDIR)
	$(CC) $(CF_DBG) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(DBGPTH)

test:
	mkdir -p $(TSTDIR)
	$(CC) $(CF_DBG) -I$(INCDIR) -L$(LIBDIR) $(SRCPTH) -o $(TSTPTH)
	./$(TSTPTH) $(TSTARG)

install: $(SRCNAM)
	cp -f "$(RELPTH)" "/usr/bin/$(BIN)"

clean:
	rm -rf $(RELDIR)
	rm -rf $(TSTDIR)
	rm -rf $(DBGDIR)
	rm -rf $(ANDDIR)

