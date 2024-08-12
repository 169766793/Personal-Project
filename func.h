#pragma once

#include "myheadfiles.h"

#define STUDENT_FILE "students.dat" // 学生信息文件名

typedef struct student {
    char academy[50]; // 记录学院 计科院、电科院、商学院
    char id[13];      // 记录学号 20210111xxxx 12位
    char name[50];    // 记录姓名 中文
    int  age;         // 记录年龄 18~22
    char sex;         // 记录性别 f女 m男
    struct student* next;
} Student;

void loadStudentsFromFile(); // 从students.dat文件中加载学生信息
void saveStudents(); // 保存学生信息到students.dat文件
void addStudent(); // 添加学生信息到链表中
void deleteStudent(); // 删除学生信息
void clearAllStudents();//清空学生信息
void modifyStudent(); // 修改学生信息
void findStudent(); // 查找学生信息
void displayAllStudents(); // 显示所有学生信息
void bubbleSort(Student** head); // 冒泡排序
void miniGame(); // 小游戏
