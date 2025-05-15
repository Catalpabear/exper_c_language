#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../head/card_service.h"
// extern Card acard[100];
// extern int card_count;
extern Card* head;
extern Card* lastnode;
void menu()
{
    // 打印卡片信息
    printf("-------------打印读取的卡片信息--------------\n");
    printf("卡号\t状态\t余额\t开卡时间\n");
    PrintList(head);
    printf("-------------打印读取的卡片信息--------------\n");

    printf("欢迎进入计费管理系统\n");
    printf("本系统由王梓翔 1024005323开发\n");
    printf("-------------菜单--------------\n");
    printf("1.添加卡\n");
    printf("2.查询卡\n");
    printf("3.上机\n");
    printf("4.下机\n");
    printf("5.充值\n");
    printf("6.退费\n");
    printf("7.查询统计\n");
    printf("8.注销卡\n");
    printf("0.退出\n");
    int choice=0;
    //char input[100]={'\0'};
    while (1)
    {
        
        printf("-------------选择--------------\n");
        printf("请选择菜单项编号(0-8):");
        // getchar();
        scanf("%d", &choice);
        // strcpy(input, "0");
        // if (fgets(input, sizeof(input), stdin) == NULL) {
        //     printf("输入错误，请重新选择菜单项编号(0-8):\n");
        //     continue;
        // }

        // // 尝试将输入解析为整数
        // if (sscanf(input, "%d", &choice) != 1) {
        //     printf("输入无效，请输入数字(0-8):\n");
        //     continue;
        // }

        // // 检查输入是否在有效范围内
        // if (choice < 0 || choice > 8) {
        //     printf("输入超出范围，请输入数字(0-8):\n");
        //     continue;
        // }
        
        switch (choice)
        {
        case 1:
            if(add_card()==1)
                lastnode=lastnode->next;
            break;
        case 2:
            printf("-------------查询卡------------\n");
            printf("请输入卡号<长度为1-18>：");
            char query_card[30];
            scanf("%s", query_card);
            if(strlen(query_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            int result_count = 0;
            Card**results=find_cards_by_part(head, query_card, &result_count);
            if(results== NULL)
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("找到 %d 个匹配的卡号：\n", result_count);
            printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
            for (int i = 0; i < result_count; i++) 
            {
                printf("%s\t%d\t%.2lf\t%.2lf\t\t%d\t\t%s\n",
                    results[i]->aname,
                    results[i]->nstatus,
                    results[i]->balance,
                    results[i]->totaluse,
                    results[i]->use_times,
                    results[i]->last_time);
            }
            free(results);
            break;
        case 3:
            printf("上机成功\n");
            
            break;
        case 4:
            
            printf("下机成功\n");
            break;
        case 5:
            printf("-------------充值------------\n");
            printf("请输入卡号<长度为1-18>：");
            char recharge_card[19];
            scanf("%s", recharge_card);
            Card * charge_return=find_card_by_aname(head,recharge_card);
            if (charge_return == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入充值金额<RMB>：");
            double recharge;
            scanf("%lf", &recharge);
            charge_return->balance += recharge;
            printf("充值成功！");
            printf("当前余额为：%.2lf\n", charge_return->balance);
            break;
        case 6:
            printf("-------------退费------------\n");
            printf("请输入卡号<长度为1-18>：");
            char refund_card[19];
            scanf("%s", refund_card);
            Card* refund_index = find_card_by_aname(head, refund_card);
            if (refund_index == NULL)
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char refund_password[9];
            scanf("%s", refund_password);
            if (strcmp(refund_index->apwd, refund_password) != 0) 
            {
                printf("密码错误！\n");
                break;
            }
            printf("请输入退费金额<RMB>：");
            double refund;
            scanf("%lf", &refund);
            if (refund > refund_index->balance) 
            {
                printf("退费金额超过余额！\n");
                break;
            }
            refund_index->balance -= refund;
            printf("退费成功！\n");
            printf("当前余额为：%.2lf\n", refund_index->balance);
            printf("请在下机后到前台领取所退费用！谢谢！\n");
            break;
        case 7:
            printf("-------------查询统计------------\n");
            printf("请输入0查询消费记录，输入1统计总营业额：");
            int stat_choice;
            scanf("%d", &stat_choice);
            if (stat_choice)
                printf("总营业额为：%lf\n", 1000.00);
            else
                printf("消费记录为：%d\n",1);
            break;
        case 8:
            printf("-------------注销卡------------\n");
            printf("请输入卡号<长度为1-18>：");
            char cancel_card[19];
            scanf("%s", cancel_card);
            Card*cancel_index = find_card_by_aname(head, cancel_card);
            if (cancel_index == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char cancel_password[9];
            scanf("%s", cancel_password);
            if (strcmp(cancel_index->apwd, cancel_password))
            {
                printf("密码错误！\n");
                break;
            }
            printf("注销成功！\n");
            printf("目前delete功能未实现，注销后卡号仍然存在！\n");
            printf("请在下机后到前台领取所退费用！谢谢！\n");
            break;
        case 0:
            printf("谢谢使用，再见！\n");
            printf("认准这个系统 by 王梓翔 1024005323\n");
            binwriteCardlist();
            // 将卡片信息写入二进制文件
            exit(0);
        default:
            printf("输入错误，请重新选择菜单项编号(0-8):");
            break;
        } 
    }
    
}