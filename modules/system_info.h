#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

struct SystemInformation {
    char manufacturer[128];
    char model[128];
    char osVersion[128];
    char hostname[128];
};

void getSystemInformation(struct SystemInformation *sysInfo);

#endif