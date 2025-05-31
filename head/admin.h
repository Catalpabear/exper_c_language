typedef struct Admin
{
    char aname[20]; // 管理员用户名
    char apwd[20];  // 管理员密码
    int nstatus; // 管理员状态 0:正常 1:冻结
}Admin;
void saveAdmin(Admin admin);
void readAdmin();
int find_admin_by_aname(Admin *admins, const char *query_admin);
void savealladmin();