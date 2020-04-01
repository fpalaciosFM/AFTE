CXX		:= g++
TARGET	:= AFTE$(EXT)

HDRS	:= $(shell python make/pyfind.py Source .hpp)

USRCS	:= $(wildcard *.cpp)
LSRCS	:= $(shell python make/pyfind.py Source .cpp)
ALLSRCS := $(USRCS) $(LSRCS)

UOBJS   := $(USRCS:.cpp=.o)
LOBJS   := $(LSRCS:.cpp=.o)

ifeq ($(PLATFORM), Windows)
	DOBJS := $(subst /,\,$(UOBJS)) $(subst /.\,$(LOBJS))
else
	DOBJS := $(UOBJS) $(LOBJS)
endif

CFLAGS	:= -std=c++11 # -Iinclude
# LFLAGS	:= -std=c++11 # -Iinclude

$(TARGET):	$(UOBJS) $(LOBJS)
	g++ -o $@ $^ $(LFLAGS)

%.o:	%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY:	run
run:	$(TARGET)	## launch primary build application
	$(PREFIX)$(TARGET)

clean:
	$(RM) $(TARGET) $(DOBJS)