#include"../head/card_service.h"
#include <stdio.h>
#include <stdlib.h>
// extern Card acard[100];
// extern int card_count;
extern Card* head;
extern Card* lastnode;

void saveCard(Card card)
{
    FILE *fp = fopen("user_data/card.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp,"%s##%s##%d##%s##%s##%.2f##%.2f##%d", 
        card.aname, 
        card.apwd, 
        card.nstatus, 
        card.start_time, 
        card.last_time, 
        card.totaluse, 
        card.balance, 
        card.use_times);
    fprintf(fp, "\n");
    fclose(fp);
}
void readCard() 
{
    FILE *fp = fopen("user_data/card.txt", "r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    char buffer[256];
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        Card* card=(Card*)malloc(sizeof(Card));
        // 使用 sscanf 解析每一行的卡信息
        if (sscanf(buffer, "%[^#]##%[^#]##%d##%[^#]##%[^#]##%lf##%lf##%d", 
                   card->aname, 
                   card->apwd, 
                   &card->nstatus, 
                   card->start_time, 
                   card->last_time, 
                   &card->totaluse, 
                   &card->balance, 
                   &card->use_times) == 8) {
            // 将解析出的卡信息存储到list中
            addList(head, card);
            lastnode = card;
        } 
        else 
            printf("Error parsing card data: %s\n", buffer);
        
    }
    fclose(fp);
}
void binwriteCardlist()
{
    FILE *fp = fopen("user_data/card.bin", "wb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    int count = 0;
    Card *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    fwrite(&count, sizeof(int), 1, fp);
    current = head;
    while (current != NULL)
    {
        fwrite(current, sizeof(Card), 1, fp);
        current = current->next;
    }
    fclose(fp);
}
void binreadCardlist()
{
    FILE *fp = fopen("user_data/card.bin", "rb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    int count = 0;
    fread(&count, sizeof(int), 1, fp);
    for (int i = 0; i < count; i++)
    {
        Card *newCard = (Card *)malloc(sizeof(Card));
        if (newCard == NULL)
        {
            printf("内存分配失败\n");
            fclose(fp);
            return;
        }
        fread(newCard, sizeof(Card), 1, fp);
        newCard->next = NULL;
        addList(lastnode, newCard);
        lastnode = newCard;
    }
    lastnode->next = NULL;
    // 关闭文件
    fclose(fp);
}