CXX = g++
CXXFLAGS =
TARGET ?= NextUnitEngine

SRC_DIRS ?= src
OBJ_DIR ?= obj

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

INCLUDES = -L/usr/include/ -L/usr/include/GL/
LIBS = -lm -lglut -lGL -lGLU

$(OBJ_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(INCLUDES) $(LIBS)

$(OBJ_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)

-include $(DEPS)
