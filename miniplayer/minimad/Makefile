INCLUDE_FLAGS 	= -I. \
				  -I../MP3-Lib/include

CFLAGS	     	= $(INCLUDE_FLAGS) -Wall -g -static
CC			 	= gcc

LFLAGS 		 	= -L../MP3-Lib/lib -lmad
SHELL 		 	= /bin/bash
SUBDIRS 	 	=

TARGET = minimad

SOUCE_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SOUCE_FILES))

%.o : %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS) libs
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(LFLAGS)

libs:
	@ for subdir in $(SUBDIRS); do \
        (cd $$subdir && $(MAKE)); \
	done

.PHONY:clean

clean:
	$(RM) $(TARGET) $(OBJS)
	@ for subdir in $(SUBDIRS); do \
        (cd $$subdir && $(MAKE) clean); \
    done
