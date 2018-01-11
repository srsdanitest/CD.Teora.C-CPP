#include <process.h>
#include <stdio.h>

void main(void)
 {
   char *env[] = { "FILE=EXECLPE.C", "LANGUAGE=C",
                   "OS=DOS", NULL};

   execlpe("CHILD.EXE", "CHILD.EXE", "Using-execlpe", 
      "BBB", NULL, env);
 }

