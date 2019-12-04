TARGET = clock.exe

SRCS = clock.c

OBJS = ${SRCS:.c=.o}

HEADERS =

CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = gcc
LDFLAGS =
LIBS = -lm -lglpng -lglut32 -lglu32 -lopengl32

$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

.c.o :
	$(CC) $(CCFLAGS) -c $<

$(OBJS) : $(HEADERS) Makefile

clean :
	rm -f $(TARGET) $(OBJS) core *-
