# Names of the source files
SRCS     = hashtable.c util.c simple_dict.c

# Name of the executable file
EXE     = simple_dict.exe

# Flags for compilation (add warnings)
CFLAGS  = -Wall

# Use GCC linking
CC	= gcc

# Create a lists of object files from source files

OBJS 	= $(SRCS:.c=.o)
	
# This will link the executable from the object files
all: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o  $(EXE)

# Compile all needed source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Target to clean up after us
clean: 
	-rm -f $(EXE) $(OBJS) # Remove the executable file

