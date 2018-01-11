#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void main(void)
 {
    char szBuffer[MAX_PATH+100];
    UINT nRow = 0;
    UINT nDrive = 0;
    DWORD dwLogicalDrives = GetLogicalDrives();

    	for ( nDrive = 0; nDrive<32; nDrive++ )
       {
       	if ( dwLogicalDrives & (1 << nDrive) )
          { // Is drive available?
          	UINT  uType;                 // type of drive.
            DWORD dwBytesPerSector = 0;  // bytes per sector
            DWORD dwSectorsPerCluster=0; // sectors per cluster
            DWORD dwTotalClusters = 0;   // total clusters
            DWORD dwFreeClusters = 0;    // free clusters
            DWORD dwVolumeSerialNumber=0;// volume ser number
            DWORD dwMaxNameLength=0;     // max component length
            DWORD dwFileSystemFlags=0;   // file system flags
            DWORD dwFreeSpace = 0;       // free space
            DWORD dwTotalSpace = 0;      // total space
            char szFileSysName[129];     // name of file system
            char szLabel[129];           // name of volume

            // Get disk information.
            wsprintf( szBuffer, "%c:\\", nDrive+'A' );
            uType = GetDriveType(szBuffer);
            GetDiskFreeSpace(szBuffer, &dwBytesPerSector,
            						&dwSectorsPerCluster, &dwFreeClusters, &dwTotalClusters);
            GetVolumeInformation(szBuffer, szLabel, sizeof( szLabel ) - 1,
                                 &dwVolumeSerialNumber, &dwMaxNameLength,
                                 &dwFileSystemFlags, szFileSysName,
                                 sizeof( szFileSysName ) - 1 );
            dwFreeSpace = dwBytesPerSector * dwSectorsPerCluster * dwFreeClusters;
            dwTotalSpace = dwBytesPerSector * dwSectorsPerCluster * dwTotalClusters;

            // Print out information.
            wsprintf(&szBuffer[3], " Label: %s, System: %s, Long Names: %s ",
                     szLabel, szFileSysName, (dwMaxNameLength == 255) ? "TRUE" : "FALSE" );
            printf("%s\n", szBuffer);
            wsprintf(szBuffer, " Type: %s, Disk Space: %ld, Free: %ld",
            						(uType == DRIVE_REMOVABLE) ? "FLOPPY" :
                              ((uType == DRIVE_FIXED) ?  "HARD DISK" :
                              ((uType == DRIVE_REMOTE) ? "NETWORK" :
                              ((uType == DRIVE_CDROM) ?  "CDROM" :
                              ((uType == DRIVE_RAMDISK) ? "RAMDISK" :
                              ((uType == 1) ? "DOES NOT EXIST" :
                              "UNKNOWN DRIVE TYPE" ))))), dwTotalSpace, dwFreeSpace );
            printf("%s\n", szBuffer);
          }
         }
}
