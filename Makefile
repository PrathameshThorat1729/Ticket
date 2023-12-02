###############################
##### Project Information #####
###############################

PROJECT = Ticket
VERSION = v0.7
EXE = ticket

SRCDIR = src
INCDIR = include
BUILDDIR = bin/build
OBJDIR = bin/obj

######################################
##### Other Settings and Targets #####
######################################

.PHONY: build obj run clean install

SRCS = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*/*.c) # Source File List
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS)) # Object File List

# Default Target
all: $(BUILDDIR) $(OBJDIR) build

### Target for Final Build and Object Files ###

build: $(BUILDDIR)/$(EXE)
obj: $(OBJS)

run: install
	@$(BUILDDIR)/$(EXE)

$(BUILDDIR)/$(EXE): $(OBJS)
	gcc $(OBJS) -I$(INCDIR) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	gcc -DVERSION=\"$(VERSION)\" $< -I$(INCDIR) -c -o $@

# Creating Important Diectories
$(BUILDDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@ $@/games

# Cleaning Target
clean:
	rm -rf $(BUILDDIR) $(OBJDIR) ~/.config/$(PROJECT)

install: all
	mkdir -p ~/.config/$(PROJECT)
	cp -r resource/* ~/.config/$(PROJECT)