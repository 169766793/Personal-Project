#include "login.h"
//#include "func.h"

//登录
//日志文件
void Log_action(const char* action) {
    //打开日志文件
    FILE* log_fp = fopen(LOG_FILE, "a");
    if (log_fp == NULL) {
        printf("Unable to open log file!\n");
        return;
    }
    //获取当前时间
    time_t now;
    time(&now);//
    //将时间转换为可读字符串
    char* date = ctime(&now);
    date[strlen(date) - 1] = '\0'; // 移除换行符  将换行符替换为字符串结束符 '\0'
    
    //写入日志
    fprintf(log_fp, "[%s] %s\n", date, action);
    fclose(log_fp);
}
//查看日志
void PrintLogFile() {
    Log_action("Printing log file contents started");    
    //打开日志文件
    FILE* log_fp = fopen(LOG_FILE, "r");
    if (log_fp == NULL) {
        printf("Unable to open log file!\n");
        return;
    }

    //读取日志文件内容
    char line[256];
    printf("\n\t--- Log File Contents ---\n");
    while (fgets(line, sizeof(line), log_fp)) {
        printf("\t%s", line);
    }
    printf("\t--- End of Log File ---\n");

    fclose(log_fp);
    Log_action("Log file contents printed completed");
}
//注册
void RegisterUser()
{
    Log_action("User registration started");
    struct users Newuser;
    int userExists;
    //打开用户文件
    FILE* fp=fopen(USER_FILE,"ab");
    if(fp==NULL)
    {
        printf("CANT OPEN FILE!\n");
        return;
    }
    //输入用户名和密码
    do {
        printf("\t\033[1;5;36mPLEASE ENTER USERNAME:");
        scanf("%s", Newuser.username);
    //判断用户名是否已经注册（已注册0 未注册-1）
        userExists = (Finduser(Newuser.username) != -1);
        if (userExists) {
            printf("\t\033[1;5;31mUSERNAME ALRAEDY EXISTS!\033[0m\n");
        }
    } while (userExists);//已注册则重新输入用户名
       
    //输入密码
    printf("\t\033[1;5;36mPLEASE ENTER YOUR PASSWORD:");
    getchar(); // 消耗换行符
    InputCode(Newuser.password);
    //scanf("%s",Newuser.password);
    
    //选择角色
    printf("\n\tPLEASE CHOICE ROEL:\n\t0、STUDENT\n\t1、TEACHER\n");
    printf("\t");
    scanf("\t%d",&Newuser.role);

    //保存用户信息到文件
    Saveuser(Newuser);
    printf("\tREGISTER SUCCESS!\n");
    Log_action("User registration completed");
}
//登录
int Login(int *role)
{   
    Log_action("Login attempt started");
    //输入用户名和密码
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("\tPLEASE ENTER YOUR USERNAME:");
    scanf("%s",username);
    getchar(); // 消耗换行符
    printf("\tPLEASE ENTER YOUR PASSWORD:");
    InputCode(password);//密文
    //scanf("%s",password);//明文

    //打开用户文件
    FILE* fp=fopen(USER_FILE,"rb");
    if(fp==NULL)
    {
        printf("\tCANT OPEN FILE!\n");
        Log_action("Failed to open user file");
        return 0; 
    }
    //判断用户名和密码是否匹配
    struct users user;
    while (fread(&user,sizeof(struct users),1,fp))
    {
       if(strcmp(user.username,username)==0 && strcmp(user.password,password)==0)
       {
        fclose(fp);
        *role = user.role; // 存储用户的角色
        Log_action("Login successful");
        return 1;
       }
    }
    fclose(fp);
    Log_action("Login failed");
    return 0;
}
//使密码以*号输出
char* InputCode(char *pass)
{
    Log_action("Password input started");
	int i=0;
	system("stty -icanon"); //设置一次性读完操作，即getchar()不用回车也能获取字符
	system("stty -echo");   //关闭回显，即输入任何字符都不显示
    
	while(i < 16)
	{
		pass[i]=getchar();  //获取键盘的值到数组中
		if(i == 0 && pass[i] == BACKSPACE)
		{
			i=0;            //若开始没有值，输入删除，则不算值
			pass[i]='\0';
			continue;
		}
		else if(pass[i] == BACKSPACE)
		{
			printf("\b \b"); //若删除，则光标前移，输空格覆盖，再光标前移
			pass[i]='\0';
			i=i-1;           //返回到前一个值继续输入
			continue;        //结束当前循环
		}
		else if(pass[i] == '\n') //若按回车则，输入结束
		{
			pass[i]='\0';
			break;
		}
		else
		{
			printf("*");
		}
		i++;
	}
	system("stty echo");   //开启回显
	system("stty icanon"); //关闭一次性读完操作，即getchar()必须回车才能获取字符
	Log_action("Password input completed");
    return pass;//返回最后结果
}
//保存用户
void Saveuser(struct users user)
{
    //打开用户文件
    FILE* fp=fopen(USER_FILE,"ab");
    if(fp==NULL)
    {
        printf("CANT OPEN FILE!\n");
    }
    //保存用户信息到文件
    fwrite(&user,sizeof(struct users),1,fp);
    fclose(fp);
}
//判断用户名是否已经注册
int Finduser(char* username)
{
    //打开用户文件
    FILE* fp=fopen(USER_FILE,"rb");
    if(fp==NULL)
    {
        printf("\tCANT OPEN FIEL!\n");
        return 0;
    }

    //判断用户名是否已经注册
    int Userindex=0;
    struct users user;
    //用户结构体入口地址
    while(fread(&user,sizeof(struct users),1,fp))
    {
        if(strcmp(user.username,username)==0)
        {
            fclose(fp);
            //return Userindex; // 返回用户索引
            return 0;
        }
    Userindex++;
    }
    fclose(fp);
    return -1;
}
//1.0进度条
// void Progressbar(int n)
// {   
//     printf("\t\033[1;5;32;42mLOADING");
//     for(int i=0;i<n;i++)
//     {
//         for(int i=0;i<n;i++)
//         {
//             printf("\033[1;5;32;42m*的\033[0m");
//             fflush(stdout);
//             sleep(1);
//         }
//     }
//     printf("\n");
// }

//2.0进度条
void Progressbar(int n)
{   
    printf("\t\033[1;5;32;42mLOADING\033[0m");
    fflush(stdout);
    
    for (int i = 0; i < n; i++)
    {
        if (i > 0) {
            printf("\033[1;5;32;42m\b \b");// 光标回退一格，打印空格覆盖，再回退一格
        }
        //打印新的星号
        printf("\033[1;5;32;42m🐌\033[0m");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}