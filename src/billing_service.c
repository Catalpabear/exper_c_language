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
