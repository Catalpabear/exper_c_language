#include"../head/card_service.h"
#include"../head/admin.h"
#include"../head/billing_service.h"
extern Card* head;
extern Card* lastnode;
extern Admin three_admins[3];
extern int admin_count;
extern Loif* head_loif;
extern Liif* head_liif;
extern Reif* head_reif;
extern Rof* head_roif;
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
            Card* login_index = NULL;
            if (getCardAndPassword(&login_index, "请输入卡号", head)) 
            {    
                printf("error: 卡号或密码错误！\n");
                break; // 如果函数返回错误，则退出 case
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
            // 存档上机信息
            Liif login_info;
            strcpy(login_info.cardname, login_index->aname);
            strcpy(login_info.start_time, login_index->last_time);
            login_info.balance = login_index->balance;
            login_info.start_time_t = now; // 保存上机时间
            // 将上机信息写入文件
            write_login_info( &login_info);
            // 将上机信息添加到链表
            add_info_to_Liif(head_liif, &login_info);
            
            printf("上机成功\n");
            saveallcard();// 保存所有卡片信息到文本文件
            break;
        case 4:
            printf("-------------下机------------\n");
            Card* logout_index = NULL;
            if (getCardAndPassword(&logout_index, "请输入卡号", head)) 
            {    
                printf("error: 卡号或密码错误！\n");
                break; // 如果函数返回错误，则退出 case
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
            Liif* login_info_loif_need = find_liif_by_cardname(head_liif, logout_index->aname);
            double usage_time = difftime(now_logout,login_info_loif_need->start_time_t); // 计算使用时间);
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
            while (logout_index->balance < 0) 
            {
                printf("余额不足，请充值！\n");
                printf("请输入充值金额<RMB>：");
                double recharge_else;
                scanf("%lf", &recharge_else);
                logout_index->balance += recharge_else;
                // 存档充值信息
                Reif charge_info;
                strcpy(charge_info.cardname, logout_index->aname);
                strcpy(charge_info.recharge_time, logout_index->last_time);
                charge_info.amount = recharge_else;
                // 将充值信息写入文件
                write_recharge_info( &charge_info);
                // 将充值信息添加到链表
                add_info_to_Reif(head_reif, &charge_info);
                printf("充值成功！");
                printf("当前余额为：%.2lf\n", logout_index->balance);
            }
            // 存档下机信息
            Loif logout_info;
            strcpy(logout_info.cardname, logout_index->aname);
            strcpy(logout_info.start_time, login_time);
            logout_info.last_time_t = now_logout;
            logout_info.amount = usage_amount;
            logout_info.balance = logout_index->balance;
            strftime(logout_info.last_time, sizeof(logout_info.last_time), "%Y-%m-%d %H:%M:%S", tm_info_logout);
            // 将下机信息写入文件
            write_logout_info( &logout_info);
            // 将下机信息添加到链表
            add_info_to_loif(head_loif, &logout_info);
            // 释放内存
            free(login_time); 
            printf("请在前台领取消费明细单！\n");   
            printf("下机成功\n");
            saveallcard(); // 保存所有卡片信息到文本文件
            break;
        case 5:
            printf("-------------充值------------\n");
            Card* charge_return = NULL;
            if (getCardAndPassword(&charge_return, "请输入卡号", head)) 
            {    
                printf("error: 卡号或密码错误！\n");
                break; // 如果函数返回错误，则退出 case
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
            // 存档充值信息
            Reif charge_info;
            strcpy(charge_info.cardname, charge_return->aname);
            strcpy(charge_info.recharge_time, charge_return->last_time);
            charge_info.amount = recharge;
            // 将充值信息写入文件
            write_recharge_info( &charge_info);
            // 将充值信息添加到链表
            add_info_to_Reif(head_reif, &charge_info);
            printf("充值成功！");
            printf("当前余额为：%.2lf\n", charge_return->balance);
            saveallcard(); // 保存所有卡片信息到文本文件
            break;
        case 6:
            printf("-------------退费------------\n");
            Card* refund_index = NULL;
            if (getCardAndPassword(&refund_index, "请输入卡号", head)) 
            {    
                printf("error: 卡号或密码错误！\n");
                break; // 如果函数返回错误，则退出 case
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
             // 存档退费信息
            Rof refund_info;
            strcpy(refund_info.cardname, refund_index->aname);
            strcpy(refund_info.refund_time, refund_index->last_time);
            refund_info.amount = refund_index->balance;
            // 将退费信息写入文件
            write_refund_info( &refund_info);
            // 将退费信息添加到链表
            add_info_to_Rof(head_roif, &refund_info);
            printf("退费成功！\n");
            printf("当前余额为：%.2lf\n", refund_index->balance);
            printf("请在下机后到前台领取所退费用！谢谢！\n");
            saveallcard(); // 保存所有卡片信息到文本文件
            break;
        case 7:
            if (is_admin == 0)
            {
                printf("error: 你不是管理员,没有权限查询消费\n");
                break;
            }
            printf("-------------查询统计------------\n");
            printf("请输入0查询消费记录，输入1统计总营业额：");
            int stat_choice=-1;
            scanf("%d", &stat_choice);
            if (stat_choice==1)
            {
                printf("请输入0查询总营业额，输入1统计每个月营业额：");
                int seco_choice=-1;
                scanf("%d", &seco_choice);
                if(seco_choice==0)
                {
                    printf("请输入查询的时间段<格式为YYMM>\n");
                    char start_date[20], end_date[20];
                    printf("开始时间：");
                    scanf("%s", start_date);
                    printf("结束时间：");
                    scanf("%s", end_date);
                    // 时间段查询
                    int start_time=atoi(start_date),end_time=atoi(end_date);
                    int summ=calc_total_revenue(head_loif, start_time, end_time);
                    printf("该时间段的总营业额为：%d元\n", summ);
                }
                else if(seco_choice==1)
                {
                    printf("请输入月份<格式为YYMM>：");
                    char month[20];
                    scanf("%s", month);
                    int sum=calc_monthly_revenue(head_loif, month);
                    printf("该月份的总营业额为：%d元\n", sum);
                }
                else
                {
                    printf("输入错误，请重新输入0或1：");
                    break;
                }
            }
            else if(stat_choice==0)
            {
                printf("-------------查询消费记录------------\n");
                printf("请输入你要查询的卡号<长度为1-18>：");
                char stat_card[30];
                scanf("%s", stat_card);
                if(strlen(stat_card) > 18)
                {
                    printf("error: 卡号长度超过18位 ");
                    printf("请重新输入\n");
                    break;
                }
                printf("请输入查询的时间段<格式为YYMM>\n");
                char start_date[20], end_date[20];
                printf("开始时间：");
                scanf("%s", start_date);
                printf("结束时间：");
                scanf("%s", end_date);
                // 时间段查询
                int start_time=atoi(start_date),end_time=atoi(end_date);
                LoifMatches time_matches = find_loif_by_date(head_loif, start_time, end_time,stat_card);
                if (time_matches.count == 0) 
                {
                    printf("没有找到相关时间段的消费记录！\n");
                    free(time_matches.matches);
                    break;
                }
                printf("找到 %d 条时间段内的消费记录：\n", time_matches.count);
                printf("卡号\t上机时间\t\t下机时间\t\t消费金额\t余额\n");
                for (int i = 0; i < time_matches.count; i++) 
                {
                    printf("%s\t%s\t%s\t%.2lf\t\t%.2lf\n",
                        time_matches.matches[i]->cardname,
                        time_matches.matches[i]->start_time,
                        time_matches.matches[i]->last_time,
                        time_matches.matches[i]->amount,
                        time_matches.matches[i]->balance);
                }
                free(time_matches.matches); // 释放时间段查询结果的内存
            }
            else
            {
                printf("输入错误，请重新输入0或1：");
                break;
            }
            break;
        case 8:
            printf("-------------注销卡------------\n");
            Card* cancel_index = NULL;
            if (getCardAndPassword(&cancel_index, "请输入卡号", head)) 
            {    
                printf("error: 卡号或密码错误！\n");
                break; // 如果函数返回错误，则退出 case
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
            saveallcard(); // 保存所有卡片信息到文本文件
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
            return;
        default:
            printf("输入错误，请重新选择菜单项编号(0-8):");
            break;
        } 
    }
    
}