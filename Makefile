a.out: 
	MimicDelgroup.o MimicDelgroupFunctions.c
	gcc MimicDelgroup.o MimicDelgroupFunctions.o 

MimicDelgroup.o: 
	MimicDelgroup.c MimicDelgroupHeaders.h 
	gcc -c MimicDelgroup.c 

MimicDelgroupFunctions.o: 
	MimicDelgroupFunctions.c MimicDelgroupHeaders.h 
	gcc -c MimicDelgroupFunctions.c 
