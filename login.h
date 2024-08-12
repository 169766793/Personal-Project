#pragma once

#include "myheadfiles.h"

#define MAX_USERNAME 100 
#define MAX_PASSWORD 100 
#define USER_FILE "users.dat"//用户文件
#define LOG_FILE  "program_log.txt"//程序日志文件
#define BACKSPACE  0x08   //删除的asccll码值 退格键的控制字符


typedef struct users
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int  role;//0学生 1老师；
}user;

void Log_action(const char* action);//程序日志文件
void PrintLogFile();//查看程序日志文件
void RegisterUser();//注册
int Login();//登录
char* InputCode(char *pass);//密文
void MainMenu();//主菜单
void Saveuser(struct users);//保存用户密码
int Finduser(char* username);//判断用户是否已经注册
void Progressbar(int n);//进度条
