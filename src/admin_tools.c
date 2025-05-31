#include"../head/admin.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
Admin three_admins[3];
int admin_count = 0;
void saveAdmin(Admin admin)
{
    FILE *fp = fopen("user_data/admin.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s##%s##%d\n", admin.aname, admin.apwd, admin.nstatus);
    fclose(fp);
}
void readAdmin()
{
    FILE *fp = fopen("user_data/admin.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    admin_count = 0; // 初始化 admin_count 为 0
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL && admin_count < 3)
    {
        Admin admin;
        // 使用 sscanf 解析每一行的管理员信息
        if (sscanf(buffer, "%[^#]##%[^#]##%d", admin.aname, admin.apwd, &admin.nstatus) == 3)
        {
            three_admins[admin_count] = admin;
            admin_count++;
        }
        else
            printf("Error parsing admin data: %s\n", buffer);
    }
    fclose(fp);
}
void savealladmin()
{
    FILE *fp = fopen("user_data/admin.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < admin_count; i++)
    {
        fprintf(fp, "%s##%s##%d\n", three_admins[i].aname, three_admins[i].apwd, three_admins[i].nstatus);
    }
    fclose(fp);
}
int find_admin_by_aname(Admin *admins, const char *query_admin)
{
    for (int i = 0; i < admin_count; i++)
    {
        if (strcmp(admins[i].aname, query_admin) == 0)
        {
            return i; // 返回找到的管理员索引
        }
    }
    return -1; // 未找到管理员
}
