#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"../head/card_service.h"
#include"../head/admin.h"
// extern Card acard[100];
// extern int card_count;
extern Card* head;
extern Card* lastnode;
extern Admin three_admins[3];
extern int admin_count;
void menu()
{
    // 打印卡片信息
    printf("-------------打印读取的卡片信息--------------\n");
    printf("卡号\t状态\t余额\t开卡时间\n");
    PrintList(head);
    printf("-------------打印读取的卡片信息--------------\n");

    printf("欢迎进入计费管理系统\n");
    printf("本系统由王梓翔 1024005323开发\n");
    printf("您是否是管理员？\n");
    printf("如果是请输入1，如果不是请输入0：");
    int is_admin;
    scanf("%d", &is_admin);
    
    if (is_admin == 1) 
    {
        printf("请登录系统\n");
        int i=3;
        while (i){
            printf("请输入管理员账号<长度为1-18>：");
            char admin_card[30];
            scanf("%s", admin_card);
            if(strlen(admin_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                continue;
            }
            int admin_index = find_admin_by_aname(three_admins, admin_card);
            if (admin_index == -1) 
            {
                printf("管理员账号不存在！\n");
                i--;
                continue;
            }
            printf("请输入密码<长度为1-8>：");
            char admin_password[20];
            scanf("%s", admin_password);
            if(strlen(admin_password) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                continue;
            }
            if (strcmp(three_admins[admin_index].apwd, admin_password) != 0) 
            {
                printf("密码错误！\n");
                i--;
                continue;
            }
            if (three_admins[admin_index].nstatus != 0) 
            {
                printf("管理员账号已被冻结！\n");
                i--;
                continue;
            }
            else 
            {
                printf("登录成功！\n");
                break;
            }
            i--;
        }
        if (i == 0)
        {
            printf("登录失败，超过3次尝试，请重新启动程序。\n");
            exit(1);
        }
        printf("欢迎管理员使用本系统！\n");
        printf("请注意：管理员额外可以查询卡号,查询消费统计和添加管理员账号(菜单号9)等操作。\n");
    }
    if(is_admin!=1){
        if (is_admin == 0) 
            printf("欢迎用户使用本系统！\n");
        else 
        {
            printf("输入错误，请重新启动程序。\n");
            exit(1);
        }
    }
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
    
    while (1)
    {
        
        printf("-------------选择--------------\n");
        printf("请选择菜单项编号(0-8):");
        
        scanf("%d", &choice);
        
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
            if (is_admin == 0)
            {
                printf("error: 你不是管理员,没有权限查询卡号\n");
                printf("请联系管理员查询卡号\n");
                break;
            }
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
            printf("-------------上机------------\n");
            printf("请输入卡号<长度为1-18>：");
            char login_card[30];
            scanf("%s", login_card);
            if(strlen(login_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            Card*login_index = find_card_by_aname(head, login_card);
            if (login_index == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char login_password[20];
            scanf("%s", login_password);
            if(strlen(login_password) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                break;
            }
            if (strcmp(login_index->apwd, login_password))
            {
                printf("密码错误！\n");
                break;
            }
            if (login_index->nstatus != 0) 
            {
                printf("卡号已在使用中或已注销！\n");
                break;
            }
            // 更新卡片状态为使用中
            login_index->nstatus = 1;
            // 获取当前时间
            time_t now = time(NULL);
            login_index->last_time_t= now;
            struct tm *tm_info = localtime(&now);
            strftime(login_index->last_time, sizeof(login_index->last_time), "%Y-%m-%d %H:%M:%S", tm_info);
            printf("卡号\t状态\t余额\t上机时间\n");
            printf("%s\t%d\t%.2lf\t%s\n",
                login_index->aname,
                login_index->nstatus,
                login_index->balance,
                login_index->last_time);
            printf("上机成功\n");
            
            break;
        case 4:
            printf("-------------上机------------\n");
            printf("请输入卡号<长度为1-18>：");
            char logout_card[30];
            scanf("%s", logout_card);
            if(strlen(logout_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            Card*logout_index = find_card_by_aname(head, logout_card);
            if (logout_index == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char logout_password[20];
            scanf("%s", logout_password);
            if(strlen(logout_password) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                break;
            }
            if (strcmp(logout_index->apwd, logout_password))
            {
                printf("密码错误！\n");
                break;
            }
            if (logout_index->nstatus != 1) 
            {
                printf("卡号未在使用中或已注销！\n");
                break;
            }
            logout_index->nstatus = 0; // 更新卡片状态为未使用
            //存档上机时间
            char*login_time=(char*)malloc(80*sizeof(char));
            if (login_time == NULL) 
            {
                printf("内存分配失败！\n");
                break;
            }
            strcpy(login_time, logout_index->last_time);
            // 计算使用时间和消费金额
            time_t now_logout = time(NULL);
            double usage_time = difftime(now_logout, logout_index->last_time_t);
            double usage_amount = usage_time / 60.0 * 10.0; // 假设每分钟10.0元
            logout_index->totaluse += usage_amount; // 累计使用金额
            logout_index->balance -= usage_amount; // 扣除余额
            logout_index->use_times++; // 使用次数加1
            // 更新上次使用时间
            logout_index->last_time_t = now_logout;
            struct tm *tm_info_logout = localtime(&now_logout);
            strftime(logout_index->last_time, sizeof(logout_index->last_time), "%Y-%m-%d %H:%M:%S", tm_info_logout);
            printf("卡号\t状态\t余额\t上机时间\t\t下机时间\n");
            printf("%s\t%d\t%.2lf\t%s\t%s\n",
                logout_index->aname,
                logout_index->nstatus,
                logout_index->balance,
                login_time,
                logout_index->last_time);
            printf("使用时间为：%.2lf分钟\n", usage_time / 60.0);
            printf("消费金额为：%.2lf元\n", usage_amount);
            // 如果余额不足，提示用户充值
            if (logout_index->balance < 0) 
            {
                printf("亲,我们这边一分钟10元呢,不是fuger记得注意时间\n");
                printf("余额不足，请充值！\n");
                printf("请输入充值金额<RMB>：");
                double recharge_else;
                scanf("%lf", &recharge_else);
                logout_index->balance += recharge_else;
                printf("充值成功！");
                printf("当前余额为：%.2lf\n", logout_index->balance);
            }
            while(logout_index->balance < 0)
            {
                printf("余额还是不够呢,要不要试试我们的贷款功能？\n");
                printf("请输入贷款金额<RMB>：");
                double recharge_else;
                scanf("%lf", &recharge_else);
                logout_index->balance += recharge_else;
                printf("贷款成功！");
                printf("当前余额为：%.2lf\n", logout_index->balance);
                printf("当前利息为：1.6%%");
            }
            free(login_time); // 释放内存
            printf("请在前台领取消费明细单！\n");   
            printf("下机成功\n");
            break;
        case 5:
            printf("-------------充值------------\n");
            printf("请输入卡号<长度为1-18>：");
            char recharge_card[30];
            scanf("%s", recharge_card);
            if(strlen(recharge_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            Card * charge_return=find_card_by_aname(head,recharge_card);
            if (charge_return == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            if (charge_return->nstatus != 0) 
            {
                printf("卡号在使用中或已注销！\n");
                printf("充值失败！\n");
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
            char refund_card[30];
            scanf("%s", refund_card);
            if(strlen(refund_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            Card* refund_index = find_card_by_aname(head, refund_card);
            if (refund_index == NULL)
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char refund_password[20];
            scanf("%s", refund_password);
            if(strlen(refund_password) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                break;
            }
            if (strcmp(refund_index->apwd, refund_password) != 0) 
            {
                printf("密码错误！\n");
                break;
            }
            if (refund_index->nstatus != 0) 
            {
                printf("卡号在使用中或已注销！\n");
                printf("退费失败！\n");
                break;
            }
            if (refund_index->balance <= 0) 
            {
                printf("余额不足，无法退费！\n");
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
            if (is_admin == 0)
            {
                printf("error: 你不是管理员,没有权限查询卡号\n");
                printf("请联系管理员查询卡号\n");
                break;
            }
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
            char cancel_card[30];
            scanf("%s", cancel_card);
            if(strlen(cancel_card) > 18)
            {
                printf("error: 卡号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            Card*cancel_index = find_card_by_aname(head, cancel_card);
            if (cancel_index == NULL) 
            {
                printf("卡号不存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            char cancel_password[20];
            scanf("%s", cancel_password);
            if(strlen(cancel_password) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                break;
            }
            if (strcmp(cancel_index->apwd, cancel_password))
            {
                printf("密码错误！\n");
                break;
            }
            if (cancel_index->nstatus != 0) 
            {
                printf("卡号在使用中或已注销！\n");
                printf("注销失败！\n");
                break;
            }
            if( cancel_index->balance <= 0) 
            {
                printf("卡号余额不足，无法注销！\n");
                break;
            }
            printf("注销成功！\n");
            cancel_index->nstatus = 2; // 更新卡片状态为已注销
            printf("请在下机后到前台领取所退费用！谢谢！\n");
            printf("卡号\t退款金额\n");
            printf("%s\t%.2lf\n", cancel_index->aname, cancel_index->balance);
            cancel_index->balance = 0; // 清空余额
            break;
        case 9:
            if (is_admin == 0)
            {
                printf("error: 你不是管理员,没有权限添加管理员账号\n");
                printf("请联系管理员添加管理员账号\n");
                break;
            }
            printf("-------------添加管理员账号------------\n");
            if(admin_count >= 3)
            {
                printf("管理员数量已达上限，无法添加更多管理员。\n");
                break;
            }
            Admin new_admin;
            printf("请输入管理员账号<长度为1-18>：");
            scanf("%s", new_admin.aname);
            if(strlen(new_admin.aname) > 18)
            {
                printf("error: 管理员账号长度超过18位 ");
                printf("请重新输入\n");
                break;
            }
            if(find_admin_by_aname(three_admins, new_admin.aname) != -1)
            {
                printf("管理员账号已存在！\n");
                break;
            }
            printf("请输入密码<长度为1-8>：");
            scanf("%s", new_admin.apwd);
            if(strlen(new_admin.apwd) > 8)
            {
                printf("error: 密码长度超过8位 ");
                printf("请重新输入\n");
                break;
            }
            new_admin.nstatus = 0; // 设置管理员状态为正常
            three_admins[admin_count++] = new_admin; // 添加新管理员
            saveAdmin(new_admin); // 保存新管理员信息到文件
            printf("添加管理员账号成功！\n");
            break;
        case 0:
            printf("谢谢使用，再见！\n");
            printf("认准这个系统 by 王梓翔 1024005323\n");
            binwriteCardlist();
            saveallcard(); // 保存所有卡片信息到文本文件
            savealladmin(); // 保存所有管理员信息到文本文件
            // 将卡片信息写入二进制文件
            exit(0);
        default:
            printf("输入错误，请重新选择菜单项编号(0-8):");
            break;
        } 
    }
    
}