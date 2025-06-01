#include "../head/menu.h"
extern Card* head;
extern Card* lastnode;
extern Loif* head_loif;
extern Loif* move_loif;
int main()
{
    //初始化链表
    initLoifList(&head_loif, &move_loif);
    initCardList(&head,&lastnode);
    //二进制读取
    // binreadCardlist();
    //文本读取
    readCard();
    //读取管理员信息
    readAdmin();
    //读取消费信息
    read_logout_info();
    //启动菜单
    menu();
    //释放链表
    freelist(head);
    freeloiflist(head_loif);
}