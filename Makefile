###############################
##### Project Information #####
###############################

PROJECT = Ticket
VERSION = v0.2
EXE = ticket

SRCDIR = src
INCDIR = include
BUILDDIR = bin/build
OBJDIR = bin/obj

######################################
##### Other Settings and Targets #####
######################################

.PHONY: build obj run clean

SRCS = $(wildcard $(SRCDIR)/*.c) # Source File List
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS)) # Object File List

# Default Target
all: $(BUILDDIR) $(OBJDIR) build

### Target for Final Build and Object Files ###

build: $(BUILDDIR)/$(EXE)
obj: $(OBJS)

run: build
	@$(BUILDDIR)/$(EXE)

$(BUILDDIR)/$(EXE): $(OBJS)
	gcc $(OBJS) -I$(INCDIR) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	gcc -DVERSION=\"$(VERSION)\" $< -I$(INCDIR) -c -o $@

# Creating Important Diectories
$(BUILDDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@

# Cleaning Target
clean:
	rm -rf $(BUILDDIR)/* $(OBJDIR)/*