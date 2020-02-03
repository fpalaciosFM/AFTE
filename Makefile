# Modular Make - top level makefile
PROJPATH = $(PWD)
PROJNAME = $(notdir $(PROJPATH))

include $(wildcard make/*.mk)
TARGET := $(PROJNAME)$(EXT)
TSTTGT := testapp$(EXT)