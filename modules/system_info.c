#include "system_info.h"
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

#ifdef _WIN32
    #include <Windows.h>
    #include <tchar.h>
    #include <wchar.h>
    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "kernel32.lib")
#endif

void getSystemInformation(struct SystemInformation *sysInfo) {
#ifdef _WIN32
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);

    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD computer_name_size = sizeof(computer_name) / sizeof(computer_name[0]);
    GetComputerNameA(computer_name, &computer_name_size);

    strcpy(sysInfo->manufacturer, "N/A"); // Windows não fornece facilmente o fabricante
    strcpy(sysInfo->model, "PC compatível com Windows");
    sprintf(sysInfo->osVersion, "%ld.%ld", sys_info.dwMajorVersion, sys_info.dwMinorVersion);
    sprintf(sysInfo->hostname, "%s", computer_name);

#elif __linux__
    struct utsname system_info;
    FILE *fp;
    char buffer[128];

    if (uname(&system_info) == 0) {
        fp = popen("hostnamectl | grep -i 'Hardware Vendor' | awk '{print $3}'", "r");
        if (fp != NULL) {
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                buffer[strcspn(buffer, "\n")] = '\0'; // Remover a quebra de linha
                strcpy(sysInfo->manufacturer, buffer);
            } else {
                strcpy(sysInfo->manufacturer, "N/A");
            }

            pclose(fp);
        } else {
            strcpy(sysInfo->manufacturer, "Erro ao obter informações do sistema");
        }

        fp = popen("hostnamectl | grep -i 'Hardware Model' | awk '{$1=\"\"; print $0}' | sed 's/^[ \t]*//;s/[ \t]*$//'", "r");
        if (fp != NULL) {
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                buffer[strcspn(buffer, "\n")] = '\0'; // Remover a quebra de linha
                strcpy(sysInfo->model, buffer);
            } else {
                strcpy(sysInfo->model, "N/A");
            }

            pclose(fp);
        } else {
            strcpy(sysInfo->model, "Erro ao obter informações do sistema");
        }

        sprintf(sysInfo->osVersion, "%s", system_info.release);
        sprintf(sysInfo->hostname, "%s", system_info.nodename);
    } else {
        strcpy(sysInfo->manufacturer, "Erro ao obter informações do sistema");
        strcpy(sysInfo->model, "N/A");
        strcpy(sysInfo->osVersion, "N/A");
        strcpy(sysInfo->hostname, "N/A");
    }

#else
    #error "Plataforma não suportada"
#endif
}
