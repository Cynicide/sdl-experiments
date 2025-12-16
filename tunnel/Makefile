CC = clang++
CFLAGS = -std=c++17
INCLUDES = -IC:\msys64\ucrt64\include -ID:\Dev\Libs\spdlog\include
LDFLAGS = -LC:\msys64\ucrt64\lib
LIBS = -lstdc++ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

MAIN_OBJS = tunnel.o

ALL_OBJS = $(MAIN_OBJS)
all: Tunnel.exe

Tunnel.exe: $(ALL_OBJS)
	@echo Linking...
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo Build complete! Executable: Tunnel.exe

main: $(MAIN_OBJS)
	@echo Compiled main and globals

%.o: %.cpp
	@echo Compiling $<...
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o
	rm -f Tunnel.exe

remake: clean all
	@echo Remake complete!

help:
	@echo Available targets:
	@echo   all        - Build complete project
	@echo   remake     - Clean then build complete project
	@echo   main       - Build main and globals only
	@echo   clean      - Remove all object files and executable
	@echo   help       - Show this help

.PHONY: all remake main clean help