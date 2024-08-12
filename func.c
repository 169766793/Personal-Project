#include "myheadfiles.h"
#include "func.h"  
#include "login.h"  //包含日志文件

Student* head = NULL; 

// 从文件中加载学生信息
void loadStudentsFromFile() {
    Log_action("Loading student information from file");
    // 打开文件
    FILE* fp = fopen(STUDENT_FILE, "rb");
    if (fp == NULL) {
        printf("\tCannot open file for reading!\n");
        return;
    }
    // 读取文件内容到链表中
    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp) == 1) {
        Student* newStudent = (Student*)malloc(sizeof(Student));//申请内存
        *newStudent = temp;
        newStudent->next = head;
        head = newStudent;
    }
    fclose(fp);
    Log_action("Student information loaded from file completed");
}
// 保存学生信息到文件
void saveStudents() {
    // 打开文件
    FILE* fp = fopen(STUDENT_FILE, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    // 写入链表中的所有学生信息到文件
    Student* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Student), 1, fp);
        current = current->next;
    }
    fclose(fp);
    Log_action("Student information saved to file");
}
// 添加学生信息到链表中
void addStudent() {
    Log_action("Adding student information started");
    // 申请内存
    Student* newStudent = (Student*)malloc(sizeof(Student));

    //1.0版本
    //无限制
    // printf("\tEnter student academy: ");//输入学生学院
    // scanf("%s", newStudent->academy);
    // printf("\tEnter student ID: ");//输入学生ID
    // scanf("%d", &newStudent->id);
    // printf("\tEnter student name: ");//输入学生姓名
    // scanf("%s", newStudent->name);
    // printf("\tEnter student age: ");//输入学生年龄
    // scanf("%d", &newStudent->age);
    // getchar();
    // printf("\tEnter student sex: ");//输入学生性别
    // scanf("%c", &newStudent->sex);
    
    //2.0版本
    //有限制
    // 1、输入学生ID
    // printf("\tEnter student ID: ");
    // scanf("%12s", newStudent->id);
    // //检查学号是否为12位数
    // if (strlen(newStudent->id) != 12) {
    //     printf("\tInvalid student ID. ID must be a 12-digit number.\n");
    //     free(newStudent);
    //     return;
    // }
    // //id唯一性,新添加学生id不能跟已添加学生id重复,否则打印错误信息
    // 2、输入学生姓名
    // printf("\tEnter student name: ");
    // scanf("%s", newStudent->name);
    // //判断学生输入姓名是否是汉字,不是汉字就打印错误信息
    // if (!is_chinese_name(newStudent->name)) {
    // printf("error: student name must be chinese\n");
    //添加重新输入的逻辑
    // 3、输入学生年龄
    // printf("\tEnter student age: ");
    // if (scanf("%d", &newStudent->age) != 1) {
    //     printf("\tError: Failed to read age input.\n");
    //     free(newStudent);
    //     return;
    // }
    // // 检查年龄是否在18~22之间
    // if (newStudent->age < 18 || newStudent->age > 22) {
    //     printf("Invalid age. Age must be between 18 and 22.\n");
    //     free(newStudent);
    //     return;
    // }
    // 4、输入学生性别
    // getchar();
    // printf("\tEnter student sex: ");
    // if (scanf(" %c", &newStudent->sex) != 1) {
    //     printf("\tError: Failed to read sex input.\n");
    //     free(newStudent);
    //     return;
    // }
    // // 检查性别是否为 'f' 或 'm'
    // if (newStudent->sex != 'f' && newStudent->sex != 'm') {
    //     printf("Invalid sex. Sex must be 'f' or 'm'.\n");
    //     free(newStudent);
    //     return;
    // }
    
    //3.0版本
    //有限制
    //1、输入学生学院 (仅限 "计科院", "电科院", "商学院")
    while (1) {
        printf("\tEnter student academy (计科院, 电科院, 商学院, 管理学院, 艺术学院): ");
        scanf("%49s", newStudent->academy);
        if (strcmp(newStudent->academy, "计科院") == 0 ||
            strcmp(newStudent->academy, "电科院") == 0 ||
            strcmp(newStudent->academy, "商学院") == 0 ||
            strcmp(newStudent->academy, "管理学院") == 0 ||
            strcmp(newStudent->academy, "艺术学院") == 0) {
            break;
        } else {
            printf("\tError: Invalid academy. Please enter one of the following: 计科院, 电科院, 商学院, 管理学院, 艺术学院\n");
        }
    }

    //2、输入学生ID
    //输入学生学号
    while (1) {
    printf("\tEnter student ID: ");
    scanf("%12s", newStudent->id);

    //检查学号是否为12位数
    if (strlen(newStudent->id) != 12) {
        printf("\tInvalid student ID. ID must be a 12-digit number.\n");
        continue;
    }
    // 检查ID是否唯一的函数
    bool isIdUnique(const char *id) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return false;  // ID已存在
        }
        current = current->next;
    }
    return true;  // ID是唯一的
    }
    // 检查ID是否唯一
    if (!isIdUnique(newStudent->id)) {
        printf("\tError: This student ID already exists. Please enter a unique ID.\n");
        continue;
    }
    // ID有效且唯一，跳出循环
    break;
    }

    //3、输入学生姓名
    //判断是否符合UTF-8编码的中文字符标准
    bool is_chinese_char(unsigned char c1, unsigned char c2, unsigned char c3) {
    return (c1 >= 0xE4 && c1 <= 0xE9) &&
           (c2 >= 0x80 && c2 <= 0xBF) &&
           (c3 >= 0x80 && c3 <= 0xBF);
    }
    //判断是否为UTF-8编码的中文姓名
    bool is_chinese_name(const char* name) {
    int len = strlen(name);
    //姓名长度必须大于等于2
    for (int i = 0; i < len;) {
        //检查是否为非ASCII字符
        if ((unsigned char)name[i] > 0x7F) {
            if (i + 2 < len && is_chinese_char(name[i], name[i+1], name[i+2])) {
                i += 3;
            } else {
                return false;
            }
            } else {
                return false;
            }
        }
        return true;
    }
    //输入姓名信息
    while (1) {
        printf("\tEnter student name: ");
        scanf("%s", newStudent->name);
        if (is_chinese_name(newStudent->name)) {
            break;
        } else {
            printf("\tError: Invalid name. Please enter a chinese name.\n");
        }
    }  

   
    //4、输入学生年龄
    while(1) {
    printf("\tEnter student age: ");
    if (scanf("%d", &newStudent->age) != 1) {
        // 清除输入缓冲区
        while (getchar() != '\n');
        printf("\tError: Invalid input. Please enter a number.\n");
        continue;
    }
    // 检查年龄是否在18~22之间
    if (newStudent->age < 18 || newStudent->age > 22) {
        printf("\tInvalid age. Age must be between 18 and 22. Please try again.\n");
        continue;
    }
    // 如果年龄有效,跳出循环
    break;
    }

    //  5、输入学生性别
    while(1)
    {
        // 输入学生性别
        printf("\tEnter student sex: ");
        if (scanf(" %c", &newStudent->sex) != 1) {
        // 清除输入缓冲区
        while (getchar() != '\n');
        printf("\tError: Failed to read sex input.\n");
        continue;
        }
        // 检查性别是否为 'f' 或 'm'
        if (newStudent->sex != 'f' && newStudent->sex != 'm') {
        printf("\tInvalid sex. Sex must be 'f' or 'm'.\n");
        continue;
        }
        break;
    }


    newStudent->next = head;
    head = newStudent;

    printf("\tStudent added successfully!\n");
    Log_action("Adding student information completed");
    saveStudents();
}
// 删除学生信息从链表中
void deleteStudent() {
    Log_action("Deleting single student information started");
    char id[13];
    printf("\tEnter student ID to delete: ");
    scanf("%12s", id);

    Student* current = head;
    Student* previous = NULL;
    
    while (current != NULL && strcmp(current->id, id) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\tStudent not found!\n");
        return;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("\tStudent deleted successfully!\n");
    Log_action("Student deleted completed");
    saveStudents();
}
// 清空所有学生信息
void clearAllStudents() {
    Log_action("Clearing all student information stared");
    //确认是否清空所有学生信息
    char confirm;
    printf("\t\033[1;5;31mWARNING: This will delete ALL student records. Are you sure? (y/n):");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("\t\033[1;5;33mOperation cancelled.\033[0m\n");
        return;
    }

    // 清空链表
    Student* current = head;
    Student* next;
    // 释放内存
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // 清空头指针
    head = NULL;
    printf("\tAll student records have been cleared.\n");
    Log_action("All student records cleared completed");
    saveStudents(); // 保存空的学生信息到文件
}
// 修改学生信息
void modifyStudent() {
    Log_action("Modifying single student information started");
    char id[13];
    printf("\tEnter student ID to modify: ");
    scanf("%12s", id);

    Student* current = head;
    while (current != NULL && strcmp(current->id, id) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\tStudent not found!\n");
        return;
    }

    printf("\tEnter new academy: ");
    scanf("%s", current->academy);
    printf("\tEnter new ID: ");
    scanf("%12s", current->id);
    printf("\tEnter new name: ");
    scanf("%s", current->name);
    printf("\tEnter new age: ");
    scanf("%d", &current->age);
    getchar();
    printf("\tEnter new sex: ");
    scanf("%c", &current->sex);

    printf("\tStudent information updated successfully!\n");
    Log_action("Student information modified completed");
    saveStudents();
}
// 查找学生信息
void findStudent() {
    Log_action("Searching student information started");
    char id[13];
    printf("\tEnter student ID to find: ");
    scanf("%12s", id);

    Student* current = head;
    while (current != NULL && strcmp(current->id, id) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\tStudent not found!\n");
    } else {
        printf("\tStudent found:\n");
        printf("\tAcademy: %s\n", current->academy);
        printf("\tID: %s\n", current->id);  // Use %s to print ID
        printf("\tName: %s\n", current->name);
        printf("\tAge: %d\n", current->age);
        printf("\tSex: %c\n", current->sex);
    }
    Log_action("Student information searched completed");
}
// 显示所有学生信息
void displayAllStudents() {
    Log_action("Displaying all student information started");
    if (head == NULL) {
        printf("\tNo students in the system.\n");
        return;
    }
    bubbleSort(&head); // 学生ID排序

    Student* current = head;
    int totalStudentCount = 0; // 总学生数量
    int academyCount[5] = {0}; // 统计各个学院的学生数量
    char* academies[5] = {"计科院", "电科院", "商学院", "管理学院", "艺术学院"};

    printf("\tAll Students:\n");
    while (current != NULL) {
        printf("\tAcademy: %s, ID: %s, Name: %s, Age: %d, Sex: %c\n",
               current->academy, current->id, current->name, current->age, current->sex);
        
        // 统计各个学院的学生数量
        for (int i = 0; i < 5; i++) {
            if (strcmp(current->academy, academies[i]) == 0) {
                academyCount[i]++;
                break;
            }
        }
        
        current = current->next;
        totalStudentCount++;
    }

    // 打印总学生数量
    printf("\tTotal number of students: %d\n", totalStudentCount);

    // 打印各个学院的学生数量
    printf("\tStudents per Academy:\n");
    for (int i = 0; i < 5; i++) {
        printf("\t%s: %d students\n", academies[i], academyCount[i]);
    }
    //日志记录
    Log_action("All student information displayed completed");
}


// 冒泡排序
void bubbleSort(Student** headRef) {
    int swapped;
    Student* ptr1;
    Student* lptr = NULL;

    if (*headRef == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = *headRef;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->id, ptr1->next->id) > 0) {
                // 交换节点数据
                char tempAcademy[50];
                char tempId[13];
                char tempName[50];
                int tempAge;
                char tempSex;
                //1、使用临时变量存储当前节点的数据
                strcpy(tempAcademy, ptr1->academy);
                strcpy(tempId, ptr1->id);
                strcpy(tempName, ptr1->name);
                tempAge = ptr1->age;
                tempSex = ptr1->sex;
                //2、将下一个节点的数据赋值给当前节点
                strcpy(ptr1->academy, ptr1->next->academy);
                strcpy(ptr1->id, ptr1->next->id);
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->age = ptr1->next->age;
                ptr1->sex = ptr1->next->sex;
                //3、将临时变量的数据赋值给下一个节点
                strcpy(ptr1->next->academy, tempAcademy);
                strcpy(ptr1->next->id, tempId);
                strcpy(ptr1->next->name, tempName);
                ptr1->next->age = tempAge;
                ptr1->next->sex = tempSex;

                swapped = 1;// 发生交换记录
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
// MINI GAME
void miniGame() {
    Log_action("Mini game start");
    srand((unsigned int)time(NULL));
    int num = rand() % 10;
    int guess;

    printf("\t\033[1;5;33mARE YOU READY, LET'S BEGIN!\n");
    for (int i = 0; i < 5; i++) {
        sleep(1);
        printf("\t\033[1;5;33mPLEASE ENTER A NUMBER:\n\t");
        scanf("%d", &guess);
        if (guess > num) {
            printf("\t\033[1;5;33mYOUR GUESS IS TOO BIG\n");
        } else if (guess == num) {
            printf("\t\033[1;5;33mCONFIRM, YOU WIN!\n");
            break;
        } else {
            printf("\t\033[1;5;33mYOUR GUESS IS TOO SMALL\n");
        }
    }
    if (num != guess) {
        printf("\t\033[1;5;33mAPOLOGY, YOU LOSE ALL YOUR CHANCES\n");
        printf("\t\033[1;5;33mTHE TRUE ANSWER IS: %d\n", num);
    }
    Log_action("Mini game end");
}

