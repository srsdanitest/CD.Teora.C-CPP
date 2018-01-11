#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
 {
    char szBuffer[MAX_PATH+100];
    UINT nDrive = 0;
    DWORD dwLogicalDrives = GetLogicalDrives();

	 if ( dwLogicalDrives & (1 << nDrive) )
     { // Is drive available?
       	UINT  uType;                 // type of drive.

       	// Get disk information.
       	wsprintf( szBuffer, "%c:\\", nDrive+'A' );
       	uType = GetDriveType(szBuffer);

       	// Print out information.
       	wsprintf(&szBuffer[3], " Type: %s, ",
            						(uType == DRIVE_REMOVABLE) ? "FLOPPY" :
                              ((uType == DRIVE_FIXED) ?  "HARD DISK" :
                              ((uType == DRIVE_REMOTE) ? "NETWORK" :
                              ((uType == DRIVE_CDROM) ?  "CDROM" :
                              ((uType == DRIVE_RAMDISK) ? "RAMDISK" :
                              ((uType == 1) ? "DOES NOT EXIST" :
                              "UNKNOWN DRIVE TYPE" ))))));
       	printf("%s\n", szBuffer);
      }
     else
      {
     		wsprintf(szBuffer, "%c:\\", nDrive+'A');
      	printf("%s not available", szBuffer);
      }
}
