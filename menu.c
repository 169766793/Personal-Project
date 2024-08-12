#include "menu.h"
#include "login.h"
#include "func.h"

//登录菜单
void LoginMenu()
{
    // printf("\t\033[1;5;36mWelcome To Use! Mr Dylanjiang\n");
    // printf("\t\033[1;5;36mSir Can I Service?\n");
    printf("\t\033[1;5;36mWelcome To Use! <Student Mangement System>\n");
    printf("\t\033[1;5;36mSir Can I Service?\n");
    //Progressbar(2);
    printf("\t1、REGISTER\n\t2、LOGIN\n\t3、EXIT\n");
    printf("\tPLEASE ENTER YOUR OPTION:");
}
//功能菜单
void FuncMenu(int role)
{
    int option;
    static int modifyNum=0;//学生端记录修改次数
    system("clear");
    printf("\t\033[1;5;33m----STUDENTMANAGEMENTSYSTEM---\n");
    
    if (role == 1) { // Teacher menu
        printf("\t\033[1;5;33m|1、SHOW ALL STUDENTS INFO   |\n");
        printf("\t\033[1;5;33m|2、ADD STUDENT INFO         |\n");
        printf("\t\033[1;5;33m|3、DEL STUDENT INFO         |\n");
        printf("\t\033[1;5;33m|4、CHANGE STUDENT INFO      |\n");
        printf("\t\033[1;5;33m|5、FIND STUDENT INFO        |\n");
        printf("\t\033[1;5;33m|6、VIEW LOG FILE            |\n");
        printf("\t\033[1;5;33m|7、EXIT SYSTEM              |\n");
    } else { // Student menu
        printf("\t\033[1;5;33m|1、SHOW MY INFO             |\n");
        printf("\t\033[1;5;33m|2、CHANGE MY INFO           |\n");
        printf("\t\033[1;5;33m|3、MINI-GAME                |\n");
        printf("\t\033[1;5;33m|4、EXIT SYSTEM              |\n");
    }   
    
    printf("\t\033[1;5;33m------------------------------\n");
    printf("\t\033[1;5;33mPLEASE ENTER YOUR OPTION:\033");
    

    scanf("%d",&option);

    if (role == 1) { // Teacher options
        switch (option)
        {
        case 1:
            Log_action("User selected displayinfo option");
            system("clear");
            displayAllStudents();
            break;
        case 2:
            Log_action("User selected aadinfo option");
            system("clear");
            addStudent();
            break;
        case 3:
            system("clear");
            Log_action("User selected delinfo option");
            printf("\t\033[1;5;33m3.1、DEL STUDENT INFO\033[0m\n");
            printf("\t\033[1;5;33m3.2、DEL ALL STUDENT INFO\n");
            printf("\t\033[1;5;33mPLEASE ENTER YOUR OPTION:\033");
            scanf("%d",&option);
            switch (option)
            {   
                case 1:Log_action("User selected delsingleinfo option");
                       deleteStudent();break;
                case 2:Log_action("User selected delallinfo option");
                       clearAllStudents();break;
                default:printf("\t\033[1;5;31mINVALID OPTION!\033[0m\n");
                break;
            }
            break;
        case 4:
            Log_action("User selected modifyinfo option");
            system("clear");
            modifyStudent();
            break;
        case 5:
            Log_action("User selected findinfo option");
            system("clear");
            findStudent();
            break;
        case 6:
            Log_action("User selected viewlog option");
            system("clear");
            PrintLogFile();
            break;
        case 7:
            Log_action("User selected exit option");
            saveStudents();

            system("clear"); 
            printf("\tTHANKS FOR USING AND GOODBYE!\n");
            Progressbar(1);
            system("clear"); 
            exit(-1);
        default:
            printf("\t\033[1;5;31mINVALID OPTION!\033[0m\n");
            break;
        }
    } else { // Student options
        switch (option)
        {
        case 1:
            Log_action("User selected showmyinfo option");
            system("clear");
            findStudent();
            break;
        case 2:
            if(modifyNum>=1)
            {
                printf("\t\033[1;5;31mYOU CAN ONLY MODIFY YOUR OWN INFO!\033[0m\n");
                //modifyNum=0;
            }
            else{
            Log_action("User selected changemyinfo option");
            system("clear");
            modifyStudent();
            modifyNum++;
            }
            break;
        case 3:
            Log_action("User selected minigame option");
            system("clear");
            miniGame();
            break;
        case 4:
            Log_action("User selected exit option");
            saveStudents();
            system("clear"); 
            printf("\tTHANKS FOR USING AND GOODBYE!\n");
            Progressbar(1);
            system("clear"); 
            exit(-1);
        default:
            printf("\t\033[1;5;31mINVALID OPTION!\033[0m\n");
            break;
        }
    }
    Progressbar(3);//小蜗速度
    FuncMenu(role);
}

//1.0版本菜单
// void MainMenu()
// {
//     int option;
//     system("clear");
//     printf("\t\033[1;5;33m----STUDENTMANAGEMENTSYSTEM---\n");
//     printf("\t\033[1;5;33m|1、SHOW ALL STUDENTS INFO   |\n");
//     printf("\t\033[1;5;33m|2、ADD STUDENT INFO         |\n");
//     printf("\t\033[1;5;33m|3、DEL STUDENT INFO         |\n");
//     printf("\t\033[1;5;33m|4、CHANGE STUDENT INFO      |\n");
//     printf("\t\033[1;5;33m|5、FIND STUDENT INFO        |\n");
//     printf("\t\033[1;5;33m|6、VIEW LOG FILE            |\n");
//     printf("\t\033[1;5;33m|7、EXIT SYSTEM              |\n");
//     printf("\t\033[1;5;33m------------------------------\n");
//     printf("\t\033[1;5;33mPLEASE ENTER YOUR OPTION:\033");
//     scanf("%d",&option);
//     switch (option)
//     {
//     case 1:
//         // struct users user;
//         // if(user.role==1){
//         displayAllStudents();
//         // }
//         // else{
//         //     printf("\t\033[1;5;31mYOU ARE NOT A TEACHER!\033[0m\n");
//         //     printf("\t\033[1;5;31mCANT SEE THIS SECRET INFORMATION!\033[0m\n");
//         // }
//         break;
//     case 2:
//         addStudent();
//         break;
//     case 3:
//         deleteStudent();
//         break;
//     case 4:
//         modifyStudent();
//         break;
//     case 5:
//         findStudent();
//         break;
//     case 6:
//         PrintLogFile();
//         break;
//     case 7:
//         exit(-1);
//     default:
//         printf("\t\033[1;5;31mINVALID OPTION!\033[0m\n");
//     }
//     Progressbar(2);
//     MainMenu();
// }


