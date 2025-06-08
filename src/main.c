#include "../head/menu.h"
extern Card* head;
extern Card* lastnode;
extern Loif* head_loif;
extern Loif* move_loif;
extern Liif* head_liif;
extern Liif* move_liif;
extern Reif* head_reif;
extern Reif* move_reif;
extern Rof* head_roif;
extern Rof* move_roif;
int main()
{
    //初始化链表
    initLoifList(&head_loif, &move_loif);
    initCardList(&head,&lastnode);
    initLiifList(&head_liif, &move_liif);
    initReifList(&head_reif, &move_reif);
    initRofList(&head_roif, &move_roif);
    //二进制读取
    // binreadCardlist();
    //文本读取
    readCard();
    //读取管理员信息
    readAdmin();
    //读取消费信息
    read_logout_info();
    read_charge_info();
    read_login_info();
    read_refund_info();
    //启动菜单
    menu();
    //释放链表
    freelist(head);
    freeloiflist(head_loif);
    freeliiflist(head_liif);
    freereiflist(head_reif);
    freeroflist(head_roif);
    return 0;
}