INCLUDE_FLAGS = -I.
CFLAGS	     = $(INCLUDE_FLAGS) -O2 -Wall -lm --static -std=c99 -DONLINE_JUDGE -Wno-unused-result
CC			 = gcc

LFLAGS 		 = 
SHELL 		 = /bin/bash
SUBDIRS 	 =

TARGET = test

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
