.DEFAULT: all

PLATFORM?=PLATFORM_DESKTOP
PLATFORM_OS?=LINUX
PLATFORM_ARCH?=x86_64

RELEASE=$(shell echo '$(PLATFORM_OS)-$(PLATFORM_ARCH)' | tr '[:upper:]' '[:lower:]')
BINDIR?=_bin-$(RELEASE)
BUILDDIR?=_build-$(RELEASE)

.PHONY: all
all: $(BUILDDIR) $(BINDIR) $(BINDIR)/pong

.PHONY: clean
clean:
	rm -rf _bin*
	rm -rf _build*

$(BINDIR):
	mkdir -p $(BINDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

DBG_OPT ?= -gdwarf-2 -O2 # symbols and optimization

CC ?= gcc

CFLAGS+=-std=gnu99
CFLAGS+=-Werror
CFLAGS+=-Wall

VPATH+=src
SRC=pong.c

src/$(SRC): Makefile
	touch $@

INC=-I src

SRC_OBJ=$(subst .c,.o,$(SRC))
OBJS=$(SRC_OBJ)

$(BINDIR)/pong: $(addprefix $(BUILDDIR)/, $(OBJS))
	$(CC) $(CFLAGS) $(DBG_OPT) $^ -o $@ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o:%.c
	$(CC) $(CFLAGS) $(DBG_OPT) $(DEPFLAGS) $(INC) -c $< -o $@


-include $(subst .o,.d,$(shell ls $(BUILDDIR)/*.o))
