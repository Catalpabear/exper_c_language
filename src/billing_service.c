#include"../head/billing_service.h"
Loif*head_loif,*move_loif;
int initLoifList(Loif **head_, Loif **move_loif)
{
    *head_ = (Loif *)malloc(sizeof(Loif)); // 分配内存
    if (*head_ == NULL) 
    {
        printf("内存分配失败\n");
        return 0;
    }
    (*head_)->next = NULL; // 初始化链表头
    *move_loif = *head_; // 设置移动指针
    // 初始化链表头的其他字段
    strcpy((*head_)->cardname, "head"); // 初始化卡号为空
    strcpy((*head_)->start_time, "0000-00-00 00:00:00"); // 初始化上机时间为空
    (*head_)->last_time_t = 0; // 初始化上次使用时间为0
    (*head_)->amount = 0.0; // 初始化消费金额为0
    (*head_)->balance = 0.0; // 初始化余额为0
    (*head_)->next = NULL; // 确保链表头的下一个指针为空
    return 1; // 成功初始化
}
LoifMatches find_loif_by_cardname(Loif *head, const char *query_card) {
    LoifMatches result = {NULL, 0};
    Loif** matches = (Loif**)malloc(sizeof(Loif*) * MAX_MATCHES);
    if (matches == NULL) 
    {
        perror("内存分配失败");
        return result; // 返回空的 LoifMatches
    }

    int match_count = 0;
    while (head != NULL) 
    {
        if (strcmp(head->cardname, query_card) == 0) 
        {
            if (match_count < MAX_MATCHES) 
                matches[match_count++] = head; // 存储匹配的指针
            else 
            {
                printf("超过最大匹配数量，忽略更多匹配项\n");
                break; // 停止查找更多匹配项
            }
        }
        head = head->next; // 移动到下一个节点
    }
    result.matches = matches;
    result.count = match_count;
    return result;
}
void freeloiflist(Loif*head)
{
    Loif *current = head;
    Loif *nextNode;
    while (current != NULL) 
    {
        nextNode = current->next; // 保存下一个节点
        free(current); // 释放当前节点
        current = nextNode; // 移动到下一个节点
    }
}
void add_info_to_loif(Loif *head, const Loif *new_info) {
    Loif *new_node = (Loif *)malloc(sizeof(Loif));
    if (new_node == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    // 复制新信息到新节点
    strcpy(new_node->cardname, new_info->cardname);
    strcpy(new_node->start_time, new_info->start_time);
    strcpy(new_node->last_time, new_info->last_time);
    new_node->last_time_t = new_info->last_time_t;
    new_node->amount = new_info->amount;
    new_node->balance = new_info->balance;
    new_node->next = NULL;

    // 将新节点添加到链表末尾
    Loif *current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_node; // 将新节点链接到链表末尾
}