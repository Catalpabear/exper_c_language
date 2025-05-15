#define max_cardname 19
#define max_cardpwd 9
#include<time.h>
typedef struct Card
{
    char aname[19];
    char apwd[8];
    int nstatus;// 0:未使用 1:使用中 2:已注销 3:已冻结
    char start_time[80];//开卡时间
    time_t start_time_t;
    char last_time[80];//上次使用时间
    double totaluse;//累计使用金额
    double balance;//余额
    int use_times;//累计使用次数
    struct Card *next;//链表指针
}Card;
int add_card();
Card* find_card_by_aname(Card *head, const char *query_card);
void inputAmount(double *amount);
void saveCard(Card card);
void readCard();
void binwriteCardlist();
void binreadCardlist();
void initCardList(Card **head,Card **lastnode);
void addList(Card *head, Card *new_card);
void PrintList(Card *head);
void freelist(Card *head);
Card** find_cards_by_part(Card *head, const char *query_card, int *result_count);