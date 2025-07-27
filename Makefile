CC = gcc

# CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c11 -pedantic -Iinclude -D_GNU_SOURCE


LDFLAGS = -lsqlite3

SRCDIR = src

OBJDIR = obj

TARGET = game

SRCS = $(wildcard $(SRCDIR)/*.c)


OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJS) | $(OBJDIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET)
	@rm -rf $(OBJDIR)
	@echo "Clean complete."

