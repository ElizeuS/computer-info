#include <stdio.h>
#include "disk_info.h"

void convertBytes(unsigned long long bytes, char* result) {
    const char* suffixes[] = {"B", "KB", "MB", "GB", "TB"};
    int suffixIndex = 0;

    double size = bytes;
    while (size >= 1024 && suffixIndex < 4) {
        size /= 1024;
        suffixIndex++;
    }

    sprintf(result, "%.2f %s", size, suffixes[suffixIndex]);
}

#ifdef _WIN32
    #include <Windows.h>

    void getDiskInfo(struct DiskInformation *diskInfo) {
        ULARGE_INTEGER total_bytes, free_bytes, total_free_bytes;

        if (GetDiskFreeSpaceEx(NULL, &free_bytes, &total_bytes, &total_free_bytes)) {
            convertBytes(total_bytes.QuadPart, diskInfo->totalSize);
            convertBytes(free_bytes.QuadPart, diskInfo->freeSpace);
        } else {
            perror("Erro ao obter informações do disco");
        }
    }

#elif __linux__
    #include <sys/statvfs.h>

    void getDiskInfo(struct DiskInformation *diskInfo) {
        struct statvfs stat;

        if (statvfs("/", &stat) == 0) {
            convertBytes(stat.f_frsize * stat.f_blocks, diskInfo->totalSize);
            convertBytes(stat.f_frsize * stat.f_bfree, diskInfo->freeSpace);
        } else {
            perror("Erro ao obter informações do disco");
        }
    }

#endif