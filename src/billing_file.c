#include"../head/billing_service.h"

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
Loif* read_logout_info()
{
    FILE *fp = fopen("user_data/logout.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return NULL;
    }
    Loif *head = NULL, *tail = NULL;
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        Loif *new_node = (Loif *)malloc(sizeof(Loif));
        if (sscanf(buffer, "%[^#]##%[^#]##%lf##%lf", 
                   new_node->cardname, 
                   new_node->start_time, 
                   &new_node->amount, 
                   &new_node->balance) == 4)
        {
            new_node->next = NULL;
            if (head == NULL)
            {
                head = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }
        }
        else
        {
            free(new_node);
            printf("Error parsing logout data: %s\n", buffer);
        }
    }
    fclose(fp);
    return head;
}