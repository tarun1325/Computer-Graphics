COMMAND = g++
PROG = *.cpp
OUTPUT = MT2015120_Assignment_04
TITLE = Assignment__04__MT2015120__Tarun_Jain
EXTRA = -lglut -lGL -lGLU -std=c++11
PLYFILES = canstick.ply canstick.ply canstick.ply canstick.ply apple.ply

all:
	$(COMMAND) $(PROG) -o $(OUTPUT) $(EXTRA)
	./$(OUTPUT) $(TITLE) $(PLYFILES)
	
clean: 
	rm -f $(OUTPUT) 
