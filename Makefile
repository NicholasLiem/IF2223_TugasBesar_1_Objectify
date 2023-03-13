TARGET_EXEC := main

BUILD_DIR := bin
SRC_DIRS := src
DRIVER_DIR := src/driver

SRCS := $(shell find $(SRC_DIRS) -path *driver -prune -o -name '*.cpp' -print)

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -path *apps -prune -o -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -std=c++17 -ggdb -MMD -MP

DEPS := $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean all
all: $(OBJS)
clean:
	rm -r $(BUILD_DIR)
driver: $(OBJS)
	@mkdir -p $(BUILD_DIR)/driver
	@$(CXX) $(CPPFLAGS) $(filter-out %/main.cpp.o,$(OBJS)) \
		$(DRIVER_DIR)/$(DRIVER_SRC) -o $(BUILD_DIR)/driver/$(basename $(DRIVER_SRC))

-include $(DEPS)
