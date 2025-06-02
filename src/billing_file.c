#include"../head/billing_service.h"
extern Loif* head_loif;
void write_logout_info(const char *filename, const Loif *logout_info)
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