#include"../head/billing_service.h"
Loif*head_loif,*move_loif;
Liif*head_liif,*move_liif;
Reif*head_reif,*move_reif;
Rof*head_roif,*move_roif;
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
    printf("logout_info链表已释放\n");
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

//查找上机记录
Liif* find_liif_by_cardname(Liif *head, const char *cardname) 
{
    if (head == NULL || cardname == NULL) {
        return NULL;
    }
    Liif *current = head->next;
    Liif *last_match = NULL; // 用于保存最后一个匹配的节点

    while (current != NULL) {
        if (strcmp(current->cardname, cardname) == 0) {
            last_match = current; // 更新最后一个匹配的节点
        }
        current = current->next;
    }
    return last_match; // 返回最后一个匹配的节点，如果没有找到则返回 NULL
}
//转化int数组为数字
int combine_to_four_digit_int_specially(int *arr) 
{
    int size=4;
    if (arr == NULL || size != 4) {
        return -1; // 返回一个错误代码
    }

    int result = 0;
    for (int i = 0; i < size; i++) {
        result = result * 10 + arr[i];
    }
    return result;
}
//提取YYMMint数组
int* extract_and_convert_specially(const char *str) 
{
    int positions[]={2,3,5,6};
    int num_positions=4;
    if (str == NULL || num_positions <= 0) {
        return NULL;
    }

    int *result = (int*)malloc(sizeof(int) * num_positions);
    if (result == NULL) {
        perror("内存分配失败");
        return NULL;
    }

    for (int i = 0; i < num_positions; i++) {
        if (positions[i] >= 0 && positions[i] < strlen(str)) {
            // 提取字符并转换为 int
            char char_to_convert[2];
            char_to_convert[0] = str[positions[i]];
            char_to_convert[1] = '\0';
            result[i] = atoi(char_to_convert);
        } else {
            result[i] = 0; // 如果位置无效，则设置为 0 或其他默认值
        }
    }

    return result;
}

LoifMatches find_loif_by_date(Loif *head, const int start_date, const int end_date, const char* query_card) 
{
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
        int*need_free=extract_and_convert_specially(head->start_time);
        int*need_free2=extract_and_convert_specially(head->last_time);

        int start_1=combine_to_four_digit_int_specially(need_free);
        int end_1=combine_to_four_digit_int_specially(need_free2);
        if (start_date<=start_1&&end_1<=end_date&& 
            (strcmp(head->cardname, query_card) == 0))
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
        free(need_free);
        free(need_free2);
    }
    result.matches = matches;
    result.count = match_count;
    return result;
}
double calc_monthly_revenue(Loif* head, char *month)
{
    double sum=0;
    while (head_loif != NULL) 
    {
        int month_int = atoi(month);
        int* month_arr = extract_and_convert_specially(head_loif->last_time);
        int month_num = combine_to_four_digit_int_specially(month_arr);
        free(month_arr);
        if(month_int==month_num)
        {
            sum+= head_loif->amount;
        }
        head_loif = head_loif->next; // 移动到下一个节点
    }
    return sum;
}
double calc_total_revenue(Loif* head_loif, int start_time,int end_time)
{
    double sum = 0;
    while (head_loif != NULL) 
    {
        int*need_free=extract_and_convert_specially(head_loif->last_time);
        int*need_free2=extract_and_convert_specially(head_loif->start_time);
        int start_1=combine_to_four_digit_int_specially(need_free2);
        int end_1=combine_to_four_digit_int_specially(need_free);
        if (start_time <= start_1 && end_1 <= end_time) 
        {
            sum += head_loif->amount; // 累加消费金额
        }
        head_loif = head_loif->next; // 移动到下一个节点
        free(need_free);
        free(need_free2);
    }
    return sum;
}



int initLiifList(Liif **head_, Liif **move_loif)
{
    *head_ = (Liif *)malloc(sizeof(Liif)); // 分配内存
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
    (*head_)->balance = 0.0; // 初始化余额为0
    (*head_)->next = NULL; // 确保链表头的下一个指针为空
    return 1; // 成功初始化
}
void freeliiflist(Liif *head)
{
    Liif *current = head;
    Liif *nextNode;
    while (current != NULL) 
    {
        nextNode = current->next; // 保存下一个节点
        free(current); // 释放当前节点
        current = nextNode; // 移动到下一个节点
    }
    printf("login_info链表已释放\n");
}
void add_info_to_Liif(Liif *head, const Liif *new_info) {
    Liif *new_node = (Liif *)malloc(sizeof(Liif));
    if (new_node == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    // 复制新信息到新节点
    strcpy(new_node->cardname, new_info->cardname);
    strcpy(new_node->start_time, new_info->start_time);
    new_node->start_time_t = new_info->start_time_t;
    new_node->balance = new_info->balance;
    new_node->next = NULL;

    // 将新节点添加到链表末尾
    Liif *current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_node; // 将新节点链接到链表末尾
}



int initReifList(Reif **head_, Reif **move_reif)
{
    *head_ = (Reif *)malloc(sizeof(Reif)); // 分配内存
    if (*head_ == NULL) 
    {
        printf("内存分配失败\n");
        return 0;
    }
    (*head_)->next = NULL; // 初始化链表头
    *move_reif = *head_; // 设置移动指针
    // 初始化链表头的其他字段
    strcpy((*head_)->cardname, "head"); // 初始化卡号为空
    strcpy((*head_)->recharge_time, "0000-00-00 00:00:00"); // 初始化充值时间为空
    (*head_)->amount = 0.0; // 初始化充值金额为0
    (*head_)->next = NULL; // 确保链表头的下一个指针为空
    return 1; // 成功初始化
}
void freereiflist(Reif *head)
{
    Reif *current = head;
    Reif *nextNode;
    while (current != NULL) 
    {
        nextNode = current->next; // 保存下一个节点
        free(current); // 释放当前节点
        current = nextNode; // 移动到下一个节点
    }
    printf("recharge_info链表已释放\n");
}

void add_info_to_Reif(Reif *head, const Reif *new_info)
{
    Reif *new_node = (Reif *)malloc(sizeof(Reif));
    if (new_node == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    // 复制新信息到新节点
    strcpy(new_node->cardname, new_info->cardname);
    new_node->amount = new_info->amount;
    strcpy(new_node->recharge_time, new_info->recharge_time);
    new_node->next = NULL;

    // 将新节点添加到链表末尾
    Reif *current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_node; // 将新节点链接到链表末尾
}





int initRofList(Rof **head_, Rof **move_rof)
{
    *head_ = (Rof *)malloc(sizeof(Rof)); // 分配内存
    if (*head_ == NULL) 
    {
        printf("内存分配失败\n");
        return 0;
    }
    (*head_)->next = NULL; // 初始化链表头
    *move_rof = *head_; // 设置移动指针
    // 初始化链表头的其他字段
    strcpy((*head_)->cardname, "head"); // 初始化卡号为空
    strcpy((*head_)->refund_time, "0000-00-00 00:00:00"); // 初始化退费时间为空
    (*head_)->amount = 0.0; // 初始化退费金额为0
    (*head_)->next = NULL; // 确保链表头的下一个指针为空
    return 1; // 成功初始化
}
void freeroflist(Rof *head)
{
    Rof *current = head;
    Rof *nextNode;
    while (current != NULL) 
    {
        nextNode = current->next; // 保存下一个节点
        free(current); // 释放当前节点
        current = nextNode; // 移动到下一个节点
    }
    printf("refund_info链表已释放\n");
}

void add_info_to_Rof(Rof *head, const Rof *new_info)
{
    Rof *new_node = (Rof *)malloc(sizeof(Rof));
    if (new_node == NULL) 
    {
        printf("内存分配失败\n");
        return;
    }
    // 复制新信息到新节点
    strcpy(new_node->cardname, new_info->cardname);
    new_node->amount = new_info->amount;
    strcpy(new_node->refund_time, new_info->refund_time);
    new_node->next = NULL;

    // 将新节点添加到链表末尾
    Rof *current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = new_node; // 将新节点链接到链表末尾
}