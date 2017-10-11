DIR = ./
DEBUG =
OBJDIR = bin
TARGET = STREX

RDFOX-INCLUDE = $(DIR)/RDFox/include
TREX-INCLUDE = $(DIR)/TRex/include
ANTLR-INCLUDE = $(DIR)/antlr/antlr4-runtime

RDFOX-LIB = $(DIR)/RDFox/build/release-dll
TREX-LIB = $(DIR)/TRex/lib
ANTLR-LIB = $(DIR)/antlr/lib

INCLUDE = \
-I $(TREX-INCLUDE) \
-I $(ANTLR-INCLUDE) \
-I $(RDFOX-INCLUDE)

LIBS = \
-L $(TREX-LIB) \
-L $(ANTLR-LIB) \
-L $(RDFOX-LIB) \
-l CppRDFox \
-l TRex2 \
-l antlr4-runtime

CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wall $(DEBUG)

SRCS = $(wildcard *.cpp) \
	$(wildcard Parser/*.cpp) \
	$(wildcard RDFStore/*.cpp) \
	$(wildcard RDFConstructor/*.cpp) \
	$(wildcard Eval/*.cpp) \
	$(wildcard Test/*.cpp)

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
DEPS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.d))

all: $(OBJDIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/Parser
	mkdir $(OBJDIR)/RDFStore
	mkdir $(OBJDIR)/RDFConstructor
	mkdir $(OBJDIR)/Eval
	mkdir $(OBJDIR)/Test

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -fPIC -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

-include $(DEPS)
