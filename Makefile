CC = gcc
CCFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
LDFLAGS = -fsanitize=address

CFILES = $(wildcard *.c)
HDRFILES = $(wildcard *.h)

OBJ = $(CFILES:.c=.o)

DLISTC = $(wildcard /home/clement/my_repo/my_tools/dlist_string/*.c)
DLISTH = $(wildcard /home/clement/my_repo/my_tools/dlist_string/*.h)

TARGET = a.out

RM = rm -f

all: clang-format $(TARGET) valgrind clean

$(TARGET):
	$(CC) $(CCFLAGS) $(CFILES) $(DLISTC) $(DLISTH) $(HDRFILES) -o $@

clang-format:
	clang-format -i $(CFILES) $(HDRFILES)

exec:
	./$(TARGET)

valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) lexer.c

push:
	git add *
	git commit -m adv4
	git push

clean:
	$(RM) $(OBJ) $(TARGET)