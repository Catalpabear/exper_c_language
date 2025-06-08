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
void write_logout_info(const Loif *logout_info);
int initLoifList(Loif **head_, Loif **move_loif);
void freeloiflist(Loif *head);
void read_logout_info();
void add_info_to_loif(Loif *head, const Loif *new_info);
LoifMatches find_loif_by_date(Loif *head, const int start_date, const int end_date,const char* query_card);

int combine_to_four_digit_int_specially(int *arr) ;
int* extract_and_convert_specially(const char *str) ;
double calc_monthly_revenue(Loif* head, char *month);
double calc_total_revenue(Loif* head_loif, int start_time,int end_time);

//声明上机结构体
typedef struct Login_info
{
    char cardname[30];
    char start_time[80];//上机时间
    time_t start_time_t;
    double balance;//余额
    struct Login_info *next; // 链表指针
}Liif;
int initLiifList(Liif **head_, Liif **move_loif);
void freeliiflist(Liif *head);
void write_login_info(const Liif *login_info);
void read_login_info();
void add_info_to_Liif(Liif *head, const Liif *new_info);
Liif* find_liif_by_cardname(Liif *head, const char *cardname);

//声明充值结构体
typedef struct Recharge_info
{
    char cardname[30];
    double amount;//充值金额
    char recharge_time[80];//充值时间
    struct Recharge_info *next; // 链表指针
}Reif;
int initReifList(Reif **head_, Reif **move_reif);
void freereiflist(Reif *head);
void write_recharge_info(const Reif *recharge_info);
void read_charge_info();
void add_info_to_Reif(Reif *head, const Reif *new_info);

//声明退费结构体
typedef struct Refund_info
{
    char cardname[30];
    double amount;//退费金额
    char refund_time[80];//退费时间
    struct Refund_info *next; // 链表指针
}Rof;
int initRofList(Rof **head_, Rof **move_rof);
void freeroflist(Rof *head);
void write_refund_info(const Rof *refund_info);
void read_refund_info();
void add_info_to_Rof(Rof *head, const Rof *new_info);
#endif // BILLING_SERVICE_H