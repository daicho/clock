TARGET = clock.exe

SRCS = clock.c shape.c
ICON = icon.rc

OBJS = ${SRCS:.c=.o} ${ICON:.rc=.o}

HEADERS = clock.h shape.h

CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = gcc
LDFLAGS =
LIBS = -lm -lglpng -lglut32 -lglu32 -lopengl32

$(TARGET) : $(OBJS)
	windres -i $(ICON) -o ${ICON:.rc=.o}
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

.c.o :
	$(CC) $(CCFLAGS) -c $<

$(OBJS) : $(HEADERS) Makefile

clean :
	rm -f $(TARGET) $(OBJS) core *-
	rm -f myicon.o
