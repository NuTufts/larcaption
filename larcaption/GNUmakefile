# Include your header file location

# COMPILER
CXX = g++
CXXFLAGS = -g -fPIC

# INCLUDE DIRECTORIES FOR HEADERS
INCLUDES = -I.  # here

# for many of our dependencies, they all create a little script or binary that tells you
# where their headers and libraries are. A common trick.
INCLUDES += $(shell root-config --cflags)  # ROOT
INCLUDES += $(shell larlite-config --includes)
INCLUDES += $(shell larlite-config --includes)/../UserDev
INCLUDES += $(shell larcv-config --includes)
INCLUDES += $(shell larcv-config --includes)/../app
INCLUDES += $(shell larlitecv-config --includes)
INCLUDES += $(shell larlitecv-config --includes)/../app

# Include your shared object lib location
# we use thxe same program trick
LDFLAGS =  $(shell root-config --libs) -lPhysics -lMatrix -g
LDFLAGS += $(shell larlite-config --libs)
LDFLAGS += $(shell larcv-config --libs)
LDFLAGS += $(shell larlitecv-config --libs)

# Add your program below with a space after the previous one.
# This makefile compiles all binaries specified below.
PROGRAMS = dump_mctruth main

# We sweep up the sources in the folder so that they are built using $(wildcard pattern)
# however, we do not want to include the source files where any main functions might live
# so we filter out any possible names with $(filter-out pattern, input)
# note $(var:=.suffix) appends a suffix to all the words in the variable, var.
SOURCES_CXX =  $(filter-out $(PROGRAMS:=.cxx), $(wildcard *.cxx) )
SOURCES_CPP = $(filter-out $(PROGRAMS:=.cpp), $(wildcard *.cpp) )

# we make a list of object files from the list of sources
OBJECTS  = $(SOURCES_CXX:.cxx=.o)
OBJECTS += $(SOURCES_CPP:.cpp=.o)


# DEFINE OUR MAKE FILES

all:		$(PROGRAMS)

# rules for our main function (if it has the suffix cxx)
# we make it dependent on it's own source, but also the
# object files from all the different sources swept up in SOURCE_CXX, SOURCE_CPP
%: %.cxx $(OBJECTS)
	@echo '<<compiling and linking' $@'.cxx>>'
	@$(CXX) $@.cxx -o $@ $(CXXFLAGS) $(INCLUDES) $(OBJECTS) $(LDFLAGS)

# similar rule, except for .cpp
%: %.cpp $(OBJECTS)
	@echo '<<compiling and linking' $@'.cpp>>'
	@$(CXX) $@.cpp -o $@ $(CXXFLAGS) $(INCLUDES) $(OBJECTS) $(LDFLAGS)


# rules to build the object files from source and header files
# cpp version
%.o: %.cpp %.hpp
	@echo '<<compiling ' $@'>>'
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 
# cxx version
%.o: %.cxx %.h
	@echo '<<compiling ' $@'>>'
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

clean:	
	rm -f $(PROGRAMS) *.o

# RULES TO HELP DEBUG
# run with: make [rule name]


listsrcs:
	@echo "source list: ${SOURCES}"

listobjs:
	@echo "objects list: ${OBJECTS}"

listincludes:
	@echo "list includes: ${INCLUDES}"
