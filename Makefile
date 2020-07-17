a.out: 
	CProject.o CProjectFunctions. 
	gcc CProject.o CProjectFunctions.o 

CProject.o: 
	CProject.c CProjectHeaders.h 
	gcc -c CProject.c 

CProjectFunctions.o: 
	CProjectFunctions.c CProjectHeaders.h 
	gcc -c CProjectFunctions.c 