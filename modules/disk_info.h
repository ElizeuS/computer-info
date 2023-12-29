#ifndef DISK_INFO_H
#define DISK_INFO_H

struct DiskInformation {
    char totalSize[20];
    char freeSpace[20];
};

void getDiskInfo(struct DiskInformation *diskInfo);

#endif