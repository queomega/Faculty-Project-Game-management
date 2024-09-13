#include "lanPartyLib.h"
int main (int argc, char* argv[]) 
{
printf("Number of input files: %d\n", argc);
printf("Exec name: %s\n", argv[0]);
printf("File1: %s\n", argv[1]);
printf("File2: %s\n", argv[2]);
printf("File3: %s\n", argv[3]);

FILE *f_task = fopen( argv[1],"r");
FILE *f_in = fopen( argv[2], "r" );
FILE *f_out = fopen(argv[3],"w");


task1(f_task,f_in,f_out);
task2(f_task,f_in,f_out);
task3(f_task,f_in,f_out);
task4(f_task,f_in,f_out);



fclose(f_in);
fclose(f_out);
fclose(f_task);
return 0;
} 