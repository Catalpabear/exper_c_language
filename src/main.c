#include "../head/menu.h"
extern Card* head;
extern Card* lastnode;
int main()
{
    
    initCardList(&head,&lastnode);
    //二进制读取
    // binreadCardlist();
    //文本读取
    readCard();

    menu();

    freelist(head);
}