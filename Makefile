CCOPTION = Wall std=gnu++11 D__USE_MINGW_ANSI_STDIO=1
FLAGS = $(addprefix -,$(CCOPTION))
CC = g++
OBJ = SuffixArray.o 
SRC_DIR = /mnt/GYAHU/Stuff/FCFM/Semestres/9o_Semestre/Algoritmos/Tareas/T2/T2DAA

output.out: $(OBJ) 
	 $(CC) $(FLAGS) $(OBJ) -o output.out 

SuffixArray.o: $(SRC_DIR)/SuffixArray.cpp 
	 $(CC) $(FLAGS) -c $(SRC_DIR)/SuffixArray.cpp -o SuffixArray.o 


clean: 
	rm $(OBJ_DIR)/*.o
	rm $(BUILD_DIR)/*.out
