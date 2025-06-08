#include"../head/billing_service.h"
extern Loif* head_loif;
extern Liif* head_liif;
extern Reif* head_reif;
extern Rof* head_roif;
void write_logout_info(const Loif *logout_info)
{
    FILE *fp = fopen("user_data/logout.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s##%s##%s##%.2lf##%.2lf\n", 
            logout_info->cardname, 
            logout_info->start_time,
            logout_info->last_time,
            logout_info->amount, 
            logout_info->balance);
    fclose(fp);
}
void read_logout_info()
{
    FILE *fp = fopen("user_data/logout.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        Loif* logout_info = (Loif*)malloc(sizeof(Loif));
        if (sscanf(buffer, "%[^#]##%[^#]##%[^#]##%lf##%lf", 
                   logout_info->cardname, 
                   logout_info->start_time, 
                   logout_info->last_time, 
                   &logout_info->amount, 
                   &logout_info->balance) == 5) 
            add_info_to_loif(head_loif, logout_info);
        else 
        {
            printf("Error parsing logout data: %s\n", buffer);
            free(logout_info);
        }
    }
    fclose(fp);
}

void write_login_info(const Liif *login_info)
{
    FILE *fp = fopen("user_data/login.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s##%s##%.2lf##%ld\n", 
            login_info->cardname, 
            login_info->start_time, 
            login_info->balance,
            login_info->start_time_t);
    fclose(fp);
}
void read_login_info()
{
    FILE *fp = fopen("user_data/login.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        Liif* login_info = (Liif*)malloc(sizeof(Liif));
        if (sscanf(buffer, "%[^#]##%[^#]##%lf##%ld", 
                   login_info->cardname, 
                   login_info->start_time, 
                   &login_info->balance,
                &login_info->start_time_t) == 4) 
            add_info_to_Liif(head_liif, login_info);
        else 
        {
            printf("Error parsing login data: %s\n", buffer);
            free(login_info);
        }
    }
    fclose(fp);
}

void write_recharge_info(const Reif *recharge_info)
{
    FILE *fp = fopen("user_data/charge.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s##%.2lf##%s\n", 
            recharge_info->cardname, 
            recharge_info->amount, 
            recharge_info->recharge_time);
    fclose(fp);
}
void read_charge_info()
{
    FILE *fp = fopen("user_data/charge.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        Reif* recharge_info = (Reif*)malloc(sizeof(Reif));
        if (sscanf(buffer, "%[^#]##%lf##%[^#]", 
                   recharge_info->cardname, 
                   &recharge_info->amount, 
                   recharge_info->recharge_time) == 3) 
            add_info_to_Reif(head_reif, recharge_info);
        else 
        {
            printf("Error parsing recharge data: %s\n", buffer);
            free(recharge_info);
        }
    }
    fclose(fp);
}

void write_refund_info(const Rof *refund_info)
{
    FILE *fp = fopen("user_data/refund.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s##%.2lf##%s\n", 
            refund_info->cardname, 
            refund_info->amount, 
            refund_info->refund_time);
    fclose(fp);
}
void read_refund_info()
{
    FILE *fp = fopen("user_data/refund.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        Rof* refund_info = (Rof*)malloc(sizeof(Rof));
        if (sscanf(buffer, "%[^#]##%lf##%[^#]", 
                   refund_info->cardname, 
                   &refund_info->amount, 
                   refund_info->refund_time) == 3) 
            add_info_to_Rof(head_roif, refund_info);
        else 
        {
            printf("Error parsing refund data: %s\n", buffer);
            free(refund_info);
        }
    }
    fclose(fp);
}