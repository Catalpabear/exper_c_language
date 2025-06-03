#include <time.h>
#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H
#define MAX_MATCHES 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Logout_info
{
    char cardname[30];
    char start_time[80];//上机时间
    time_t last_time_t;
    char last_time[80];//下机时间
    double amount;//消费金额
    double balance;//余额
    struct Logout_info *next; // 链表指针
} Loif;
typedef struct {
    Loif** matches;
    int count;
} LoifMatches;//for billing search
void write_logout_info(const char *filename, const Loif *logout_info);
int initLoifList(Loif **head_, Loif **move_loif);
void freeloiflist(Loif *head);
void read_logout_info();
void add_info_to_loif(Loif *head, const Loif *new_info);
LoifMatches find_loif_by_date(Loif *head, const int start_date, const int end_date,const char* query_card);
int combine_to_four_digit_int_specially(int *arr) ;
int* extract_and_convert_specially(const char *str) ;
double calc_monthly_revenue(Loif* head, char *month);
double calc_total_revenue(Loif* head_loif, int start_time,int end_time);
#endif // BILLING_SERVICE_H