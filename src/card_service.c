#include"../head/card_service.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> // 用于字符分类函数
// Card acard[100];
// int card_count = 0;
Card*head,*lastnode;
// 添加卡函数
int add_card()
{
    Card *card = (Card *)malloc(sizeof(Card));
    if (card == NULL)
    {
        printf("内存分配失败\n");
        return 0;
    }
    printf("-------------添加卡------------\n");
    //last_time init
    strcpy(card->last_time, "0000-00-00 00:00:00");
    card->nstatus = 0; // 设置卡片状态为未使用
    printf("请输入卡号<长度为1-18>：");
    char input_card[30];
    scanf("%s", input_card);
    if(strlen(input_card) > 18)
    {
        printf("error: 卡号长度超过18位 ");
        printf("请重新输入\n");
        return 0;
    }
    if(find_card_by_aname(head,input_card) != NULL)
    {
        printf("卡号已存在！\n");
        printf("添加卡信息失败！\n");
        return 0;
    }
    strncpy(card->aname, input_card, sizeof(card->aname) - 1);
    card->aname[sizeof(card->aname) - 1] = '\0'; // 确保字符串以null结尾
    printf("请输入密码<长度为1-8>：");
    char password[20];
    scanf("%s", password);
    if(strlen(password) > 8)
    {
        printf("error: 密码长度超过8位 ");
        printf("请重新输入\n");
        return 0;
    }
    strncpy(card->apwd, password, sizeof(card->apwd) - 1);
    inputAmount(&card->balance);
    card->start_time_t=time(NULL);
    struct tm*lt=localtime(&card->start_time_t);
    strftime(card->start_time, sizeof(card->start_time), "%Y-%m-%d %H:%M:%S", lt);
    printf("卡号\t状态\t余额\t开卡时间\n");
                    printf("%s\t%d\t%.2lf\t%s\n",
                           card->aname,
                           card->nstatus,
                           card->balance,
                           card->start_time);
    printf("添加卡信息成功！\n");
    
    saveCard(*card); // 保存卡信息到文件
    // 将新卡添加到链表
    addList(lastnode, card);
    return 1;
}

// 查找卡号函数
Card* find_card_by_aname(Card *head,  const char *query_card) 
{
    while (head != NULL) 
    {
        if (strcmp(head->aname, query_card) == 0) 
        {
            return head; // 找到卡号
        }
        head = head->next;
    }
    return NULL; // 未找到卡号
}

// 充值函数
void inputAmount(double *amount) {
    char input[100]; // 用于存储用户输入的字符串
    while (1) {
        printf("请输入金额：");
        scanf("%s", input);
        // 检查输入是否为有效数字
        int valid = 1; // 假设输入有效
        int decimalPointCount = 0; // 用于检查小数点数量

        for (int i = 0; input[i] != '\0'; i++) 
        {
            if (input[i] == '.') 
            {
                decimalPointCount++;
                if (decimalPointCount > 1) 
                    valid = 0; // 多个小数点，无效
            } 
            else if (!isdigit(input[i])) 
                valid = 0; // 非数字字符，无效
        }
        if (valid) 
        {
            *amount = atof(input); // 将转换后的金额存储到传入的变量中
            break; 
        } 
        else 
            printf("error: 输入的金额无效，请重新输入。\n");
    }
}
void initCardList(Card **head, Card **lastnode)
{
    *head = (Card *)malloc(sizeof(Card)); // 修改的是 head 的原始地址
    if (*head == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    *lastnode = (Card *)malloc(sizeof(Card)); // 修改的是 lastnode 的原始地址
    if (*lastnode == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    (*head)->next = *lastnode;
    (*lastnode)->next = NULL;
    // 初始化 head 的内容
    (*head)->nstatus = 0;
    (*head)->balance = 0.0;
    (*head)->totaluse = 0.0;
    (*head)->use_times = 0;
    strcpy((*head)->aname, "HEAD");
    strcpy((*head)->apwd, "00000000");
    strcpy((*head)->start_time, "0000-00-00 00:00:00");
    strcpy((*head)->last_time, "0000-00-00 00:00:00");
}
void addList(Card *lastnode, Card *newCard)
{
    Card *current = lastnode;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newCard;
    newCard->next = NULL;
}
void PrintList(Card *head)
{
    Card *current = head;
    current=current->next; // 跳过头节点
    current=current->next;
    while (current != NULL) 
    {
        printf("%s\t%d\t%.2lf\t%s\n",
               current->aname,
               current->nstatus,
               current->balance,
               current->start_time);
        current = current->next;
    }
}
void freelist(Card *head)
{
    Card *current = head;
    Card *nextNode;
    while (current != NULL) 
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
//模糊匹配
Card** find_cards_by_part(Card *head, const char *query_card, int *result_count) 
{
    // 动态数组，用于存储匹配的卡片指针
    int capacity = 10; // 初始容量
    Card **results = (Card **)malloc(capacity * sizeof(Card *));
    if (results == NULL) 
    {
        printf("内存分配失败！\n");
        *result_count = 0;
        return NULL;
    }
    *result_count = 0; // 初始化匹配结果计数
    while (head != NULL) 
    {
        // 使用 strstr 进行模糊匹配
        if (strstr(head->aname, query_card) != NULL) 
        {
            // 扩容
            if (*result_count >= capacity) 
            {
                capacity *= 2;
                results = (Card **)realloc(results, capacity * sizeof(Card *));
                if (results == NULL) 
                {
                    printf("内存分配失败！\n");
                    *result_count = 0;
                    return NULL;
                }
            }
            results[*result_count] = head;
            (*result_count)++;
        }
        head = head->next;
    }
    // 如果没有匹配结果，释放内存并返回 NULL
    if (*result_count == 0) 
    {
        free(results);
        return NULL;
    }
    return results;
}