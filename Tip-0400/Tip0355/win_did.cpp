#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
 {
    char szBuffer[MAX_PATH+100];
    DWORD dwLogicalDrives = GetLogicalDrives();

    	for ( nDrive = 0; nDrive<32; nDrive++ )
       {
       	if ( dwLogicalDrives & (1 << nDrive) )
          { // Is drive available?
          	UINT  uType;                 // type of drive.

            // Get disk information.
            wsprintf( szBuffer, "%c:\\", nDrive+'A' );
            uType = GetDriveType(szBuffer);

            // Print out information.
            wsprintf(&szBuffer[3], " Id: %u, Type: %s ", uType,
           		       (uType == DRIVE_REMOVABLE) ? "FLOPPY" :
                              ((uType == DRIVE_FIXED) ?  "HARD DISK" :
                              ((uType == DRIVE_REMOTE) ? "NETWORK" :
                              ((uType == DRIVE_CDROM) ?  "CDROM" :
                              ((uType == DRIVE_RAMDISK) ? "RAMDISK" :
                              ((uType == 1) ? "DOES NOT EXIST" :
                              "UNKNOWN DRIVE TYPE" ))))));
            printf("%s\n", szBuffer);
          }
         }
}
