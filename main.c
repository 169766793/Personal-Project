//#include "myheadfiles.h"
#include "login.h"
#include "func.h"
#include "menu.h"

int main()
{
    int option;//用户选择
    int role;  //用户角色 0-学生 1-教师 
    Log_action("Program started");
    loadStudentsFromFile();//加载学生信息
    LoginMenu();//登录菜单
    while (1)
    {
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            //注册用户
            Log_action("User selected Register option");
            RegisterUser();
            system("clear");
            LoginMenu();//登录菜单
            break;
        case 2:
            //登录用户
            Log_action("User selected Login option");
            if(Login(&role))
            {
                printf("\n\tLOGIN SUCCESS!\n");
                printf("\t\033[1;5;36mCopyright© 2024-08-09 By Dylanjiang\033[0m\n");//版权信息
                Progressbar(2);
                FuncMenu(role);
            }
            else
            {
                printf("\n\t\033[1;5;31mLOGIN FAILED!\033[0m\n");
                Progressbar(2);
                system("clear");
                LoginMenu();//登录菜单
            }
            break;
        case 3:
            //退出程序
            Log_action("User selected Login option");
            system("clear"); 
            printf("\tTHANKS FOR USING AND GOODBYE!\n");
            Progressbar(1);
            system("clear"); 
            exit(-1);
            break;
        default:
            Log_action("Invalid option selected");
            printf("\033[1;5;31m\tINPUT ORDER INVAILD!\033[0m\n");
            Progressbar(2);
            system("clear");
            LoginMenu();//登录菜单
            break;
        }
    }
    return 0;
}