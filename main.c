#include <stdio.h>
#include <string.h>
#include "disk_info.h"
#include "system_info.h"


int main() {
    struct SystemInformation sysInfo;
    getSystemInformation(&sysInfo);

    printf("=== Informações do Sistema ===\n");
    printf("Fabricante: %s\n", sysInfo.manufacturer);
    printf("Modelo: %s\n", sysInfo.model);
    printf("Versão do SO: %s\n", sysInfo.osVersion);
    printf("Hostname: %s\n", sysInfo.hostname);
    
    printf("\n=== Informações do Disco ===\n");
    // getDiskInfo();
    struct DiskInformation diskInfo;
    getDiskInfo(&diskInfo);

    printf("Capacidade total do disco: %s\n", diskInfo.totalSize);
    printf("Espaço livre no disco: %s\n", diskInfo.freeSpace);
    return 0;
}