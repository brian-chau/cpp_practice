# 'make'        build executable file 'exe'
# 'make clean'  removes all .o and executable files
#

USE_C = 0

ifeq ($(USE_C), 1)
CC = gcc-12
SRCS = $(wildcard ./sources/*.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -O3 -fPIC -g
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
else
CC = g++-12
SRCS = $(wildcard ./sources/*.cpp)
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -Wall -Werror -O3 -fPIC -std=c++20 -g
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
endif

# define any directories containing header files other than /usr/include
#
INCLUDES = -I./headers

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L./libs

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lncurses

# define the executable file
MAIN = exe

.PHONY: all clean

all:    $(MAIN)
	@echo $(MAIN) has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(RM) ./sources/*.o *~ $(MAIN)
