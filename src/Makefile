ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)

BINDIR = ../bin

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

# -- Linux with egcs
ifeq ($(shell uname),Linux)
CXX           = $(shell root-config --cxx)
CXXFLAGS      = -g -Wall -fPIC
LD            = $(shell root-config --ld)
LDFLAGS       = $(shell root-config --ldflags)
SOFLAGS       = -shared
endif

# -- Mac OS X - Darwin
ifeq ($(shell uname),Darwin)
CXX           = $(shell root-config --cxx)
CXXFLAGS      = -Wall -fPIC -g
LD            = $(shell root-config --ld)
LDFLAGS       = $(shell root-config --ldflags)
SOFLAGS       = -dylib
endif

LIBS += $(ROOTLIBS)

.SUFFIXES: .cc,.C

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

all: root2tv root2spe root2rw mat2root nmerge GeAngles ConvertMarabou CDAngles collategosiaoutput makechisq

root2tv:  root2tv.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


root2spe:  root2spe.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


root2rw:  root2rw.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


mat2root:  mat2root.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


nmerge:  nmerge.cc
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


GeAngles:  GeAngles.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


ConvertMarabou:  ConvertMarabou.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(LIBS) $< -o $(BINDIR)/$@


CDAngles:  CDAngles.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $< -o $(BINDIR)/$@


collategosiaoutput:  collategosiaoutput.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $< -o $(BINDIR)/$@


makechisq:  makechisq.cpp
# -----------------------------------------------------------------------------
	$(CXX) $(CXXFLAGS) $< -o $(BINDIR)/$@


