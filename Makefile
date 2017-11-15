SRC := src
TEST_DIR := unittest

TARGET_LIB := libtarget.a
UT_BIN := ut_bin

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:%.c=%.o)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(TEST_SRCS:%.c=%.o)

INCLUDES := -Iinlcude

CFLAGS := -Wall -Werror
CFLAGS += -g

all: $(TARGET_LIB) unittest

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_LIB): $(OBJS)
	ar rcs $@ $< 

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

unittest: $(UT_BIN)
	@echo "Runnning unit test"
	@./$(UT_BIN)

$(UT_BIN): $(TARGET_LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(TARGET_LIB) $(UT_BIN) $(TEST_OBJS) $(OBJS)
