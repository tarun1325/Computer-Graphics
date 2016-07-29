COMMAND = g++
PROG = *.cpp
OUTPUT = MT2015120_Assignment_05
TITLE = Assignment__05__MT2015120__Tarun_Jain_SceneGraph_Animation
EXTRA = -lglut -lGL -lGLU -std=c++11
PLYFILES = ply_files/hind.ply 	ply_files/hind.ply 	ply_files/chopper.ply		ply_files/bunny.ply

all:
	$(COMMAND) $(PROG) -o $(OUTPUT) $(EXTRA)
	./$(OUTPUT) $(TITLE) $(PLYFILES)
	
clean: 
	rm -f $(OUTPUT) 
