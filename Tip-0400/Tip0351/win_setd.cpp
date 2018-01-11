#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
 {
    char szBuffer[MAX_PATH+100];
    UINT nDrive, AvailDrive = 0;
    int dwLogicalDrives = GetLogicalDrives();
    DWORD Success;

    printf("Number of logical drives: %d\n", dwLogicalDrives);
    	for (nDrive = 0; nDrive < 32; nDrive++)
       {
       	if (dwLogicalDrives & (1 << nDrive))
          { // Is drive available?
            AvailDrive++;
            // Get disk information.
            wsprintf(szBuffer, "%c:\\", nDrive+'A', '\0');
            // Print out information.
 	         if(SetCurrentDirectory(szBuffer))
              printf("%s Is Now Current\n", szBuffer);
	         else
              printf("Could not set %s as the current drive\n", szBuffer);
          }
       }
      printf("Number of drives available: %d\n", AvailDrive);

 }
