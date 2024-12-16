#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>  // 用于Windows系统的控制台设置

#define MAX_NUM 2000

// 学生信息结构体
typedef struct {
    char no[30];          // 学号
    char name[30];        // 姓名
    char sex[10];         // 性别
    char thought[20];     // 思想道德
    char major[30];       // 学科专业
    float practice;       // 实践能力
    float health;         // 身心素质
    float extraPoints;    // 附加分
    float totalScore;     // 总成绩
    float averageScore;   // 平均成绩
} student;

// 学生数据库结构体
typedef struct {
    student stu[MAX_NUM];
    int number;
} studentDB;


// 计算总成绩和平均成绩
void calculate_scores(studentDB *temp) {
    for (int i = 0; i < temp->number; i++) {
        temp->stu[i].totalScore = temp->stu[i].practice + temp->stu[i].health + temp->stu[i].extraPoints;
        temp->stu[i].averageScore = temp->stu[i].totalScore / 3;
    }
}

// 读取学生数据
void read(studentDB *temp) {
    FILE *infile = fopen("./数据.txt", "r");
    if (!infile) {
        printf("文件打开失败！\n");
        exit(0);
    }
    
    temp->number = 0;
    while (fscanf(infile, "%s %s %s %s %s %f %f %f",
                  temp->stu[temp->number].no,
                  temp->stu[temp->number].name,
                  temp->stu[temp->number].sex,
                  temp->stu[temp->number].thought,
                  temp->stu[temp->number].major,
                  &temp->stu[temp->number].practice,
                  &temp->stu[temp->number].health,
                  &temp->stu[temp->number].extraPoints) == 8) {
        
        if (temp->number >= MAX_NUM) {
            printf("警告：数据超过最大限制 %d 条，后续数据将被忽略！\n", MAX_NUM);
            break;
        }
        temp->number++;
    }
    fclose(infile);
    calculate_scores(temp);
    printf("成功读取 %d 条学生记录！\n", temp->number);
}

// 显示学生信息
void display(studentDB *temp) {
    int page_size = 20; // 每页显示20条记录
    int current_page = 0;
    int total_pages = (temp->number + page_size - 1) / page_size;
    char choice;

    while (1) {
        system("cls"); // 清屏
        printf("\n当前第 %d/%d 页\n", current_page + 1, total_pages);
        printf("================================================================================================================\n");
        printf("|%-11s|%-10s|%-6s|%-10s|%-15s|%-10s|%-10s|%-8s|%-8s|%-8s|\n",
               "学号", "姓名", "性别", "思想道德", "学科专业", "实践能力", "身心素质", "附加分", "总成绩", "平均成绩");
        printf("================================================================================================================\n");

        int start = current_page * page_size;
        int end = start + page_size;
        if (end > temp->number) end = temp->number;

        for (int i = start; i < end; i++) {
            printf("|%-11s|%-10s|%-6s|%-10s|%-15s|%-10.2f|%-10.2f|%-8.2f|%-8.2f|%-8.2f|\n",
                   temp->stu[i].no,
                   temp->stu[i].name,
                   temp->stu[i].sex,
                   temp->stu[i].thought,
                   temp->stu[i].major,
                   temp->stu[i].practice,
                   temp->stu[i].health,
                   temp->stu[i].extraPoints,
                   temp->stu[i].totalScore,
                   temp->stu[i].averageScore);
        }
        printf("================================================================================================================\n");
        printf("n-下一页, p-上一页, q-退出\n请选择: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'n':
            case 'N':
                if (current_page < total_pages - 1) current_page++;
                break;
            case 'p':
            case 'P':
                if (current_page > 0) current_page--;
                break;
            case 'q':
            case 'Q':
                return;
            default:
                printf("无效输入！\n");
        }
    }
}

// 删除学生信息 
void d(studentDB *temp) {
    char no[30];
    printf("请输入要删除的学生学号：");
    scanf("%s", no);

    // 查找学生并删除
    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            // 从数组中删除学生
            for (int j = i; j < temp->number - 1; j++) {
                temp->stu[j] = temp->stu[j + 1]; // 将后面的学生数据前移
            }
            temp->number--; // 减少学生数量
            printf("学生信息已删除！\n");
            return; // 找到并删除后退出
        }
    }
    // 如果未找到该学号的学生
    printf("未找到该学号的学生！\n");
}

// 显示菜单
void menu() {
    printf("\n\n\t****************************学生综合成绩管理系统*********************\n");
    printf("\t*                              1.显示学生信息                           *\n");
    printf("\t*                              2.增加学生信息                           *\n");
    printf("\t*                              3.删除学生信息                           *\n");
    printf("\t*                              4.修改学生信息                           *\n");
    printf("\t*                              5.查询学生信息                           *\n");
    printf("\t*                              6.排序学生成绩                           *\n");
    printf("\t*                              7.计算学生平均成绩                       *\n");
    printf("\t*                              8.保存学生信息                           *\n");
    printf("\t*                              9.用户权限管理及登录系统（未实现）       *\n");
    printf("\t*                              10.班级数据统计（未实现）                *\n");
    printf("\t*                              0.退出系统                               *\n");
    printf("\t***********************************************************************\n");
    printf("请选择操作: ");
}

// 插入学生信息
void insert(studentDB *temp) {
    char no[30];
    printf("请输入学生的学号：");
    scanf("%s", no);

    // 学号有效性检查
    if (strlen(no) != 11) {
        printf("学号应为11位，请重新输入！\n");
        return;
    }

    // 检查学号是否已存在
    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("该学号的学生已存在！\n");
            return;
        }
    }

    // 输入学生信息
    strcpy(temp->stu[temp->number].no, no);
    printf("请输入姓名：");
    scanf("%s", temp->stu[temp->number].name);
    printf("请输入性别：");
    scanf("%s", temp->stu[temp->number].sex);
    printf("请输入思想道德：");
    scanf("%s", temp->stu[temp->number].thought);
    printf("请输入学科专业：");
    scanf("%s", temp->stu[temp->number].major);
    printf("请输入实践能力成绩：");
    scanf("%f", &temp->stu[temp->number].practice);
    printf("请输入身心素质成绩：");
    scanf("%f", &temp->stu[temp->number].health);
    printf("请输入附加分：");
    scanf("%f", &temp->stu[temp->number].extraPoints);

    // 更新总成绩和平均成绩
    calculate_scores(temp);

    temp->number++;
    printf("学生信息插入成功！\n");
}

// 修改学生信息
void modify(studentDB *temp) {
    char no[30];
    printf("请输入要修改的学生学号：");
    scanf("%s", no);

    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("当前信息：%s %s %s %s %s %.2f %.2f %.2f\n", temp->stu[i].no, temp->stu[i].name, temp->stu[i].sex,
                   temp->stu[i].thought, temp->stu[i].major, temp->stu[i].practice, temp->stu[i].health, temp->stu[i].extraPoints);
            printf("请输入要修改的项目：\n");
            printf("1. 姓名\n2. 性别\n3. 思想道德\n4. 学科专业\n5. 实践能力\n6. 身心素质\n7. 附加分\n");
            printf("请选择：");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("请输入新的姓名：");
                    scanf("%s", temp->stu[i].name);
                    break;
                case 2:
                    printf("请输入新的性别：");
                    scanf("%s", temp->stu[i].sex);
                    break;
                case 3:
                    printf("请输入新的思想道德：");
                    scanf("%s", temp->stu[i].thought);
                    break;
                case 4:
                    printf("请输入新的学科专业：");
                    scanf("%s", temp->stu[i].major);
                    break;
                case 5:
                    printf("请输入新的实践能力：");
                    scanf("%f", &temp->stu[i].practice);
                    break;
                case 6:
                    printf("请输入新的身心素质：");
                    scanf("%f", &temp->stu[i].health);
                    break;
                case 7:
                    printf("请输入新的附加分：");
                    scanf("%f", &temp->stu[i].extraPoints);
                    break;
                default:
                    printf("无效选项！\n");
                    return;
            }
            // 更新总成绩和平均成绩
            calculate_scores(temp);
            printf("信息修改成功！\n");
            return;
        }
    }
    printf("未找到该学号的学生！\n");
}

// 查询学生信息
void search(studentDB *temp) {
    char no[30];
    printf("请输入要查询的学生学号：");
    scanf("%s", no);

    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("学生信息：%s %s %s %s %s %.2f %.2f %.2f %.2f %.2f\n", temp->stu[i].no, temp->stu[i].name, temp->stu[i].sex,
                   temp->stu[i].thought, temp->stu[i].major, temp->stu[i].practice, temp->stu[i].health, temp->stu[i].extraPoints,
                   temp->stu[i].totalScore, temp->stu[i].averageScore);
            return;
        }
    }
    printf("未找到该学号的学生！\n");
}

// 排序比较函数，用于比较两个学生记录
int compareStudents(student *a, student *b, int criteria[], int numCriteria) {
    for (int i = 0; i < numCriteria; i++) {
        float diff = 0;
        switch (criteria[i]) {
            case 1: // 总成绩
                diff = b->totalScore - a->totalScore;
                break;
            case 2: // 平均成绩
                diff = b->averageScore - a->averageScore;
                break;
            case 3: // 实践能力
                diff = b->practice - a->practice;
                break;
            case 4: // 身心素质
                diff = b->health - a->health;
                break;
            case 5: // 附加分
                diff = b->extraPoints - a->extraPoints;
                break;
            case 6: // 学号
                diff = strcmp(a->no, b->no);
                break;
        }
        if (diff != 0) {
            return (diff > 0) ? 1 : -1;
        }
    }
    return 0;
}

// 排序学生成绩
void sort(studentDB *temp) {
    int criteria[6]; // 存储排序关键字
    int numCriteria = 0; // 关键字数量
    
    printf("\n多关键字排序\n");
    printf("排序关键字选项：\n");
    printf("1. 总成绩\n2. 平均成绩\n3. 实践能力\n4. 身心素质\n5. 附加分\n6. 学号\n");
    printf("请输入排序关键字的数量(1-6): ");
    scanf("%d", &numCriteria);
    
    if (numCriteria < 1 || numCriteria > 6) {
        printf("无效的关键字数量！\n");
        return;
    }
    
    printf("请依次输入排序关键字(用空格分隔): ");
    for (int i = 0; i < numCriteria; i++) {
        scanf("%d", &criteria[i]);
        if (criteria[i] < 1 || criteria[i] > 6) {
            printf("无效的关键字选择！\n");
            return;
        }
    }
    
    // 冒泡排序，使用多关键字比较
    student t;
    for (int i = 0; i < temp->number - 1; i++) {
        for (int j = 0; j < temp->number - 1 - i; j++) {
            if (compareStudents(&temp->stu[j], &temp->stu[j + 1], criteria, numCriteria) > 0) {
                // 交换学生记录
                t = temp->stu[j];
                temp->stu[j] = temp->stu[j + 1];
                temp->stu[j + 1] = t;
            }
        }
    }
    
    printf("排序完成！\n");
    printf("排序结果将按以下优先级排列：\n");
    for (int i = 0; i < numCriteria; i++) {
        switch (criteria[i]) {
            case 1:
                printf("%d. 总成绩\n", i + 1);
                break;
            case 2:
                printf("%d. 平均成绩\n", i + 1);
                break;
            case 3:
                printf("%d. 实践能力\n", i + 1);
                break;
            case 4:
                printf("%d. 身心素质\n", i + 1);
                break;
            case 5:
                printf("%d. 附加分\n", i + 1);
                break;
            case 6:
                printf("%d. 学号\n", i + 1);
                break;
        }
    }
}

// 写入学生信息
void write(studentDB *temp) {
    FILE *outfile = fopen("./数据.txt", "w");
    if (!outfile) {
        printf("文件打开失败！\n");
        return;
    }
    
    for (int i = 0; i < temp->number; i++) {
        fprintf(outfile, "%s %s %s %s %s %.2f %.2f %.2f\n",
                temp->stu[i].no,
                temp->stu[i].name,
                temp->stu[i].sex,
                temp->stu[i].thought,
                temp->stu[i].major,
                temp->stu[i].practice,
                temp->stu[i].health,
                temp->stu[i].extraPoints);
    }
    fclose(outfile);
    printf("成功保存 %d 条学生记录！\n", temp->number);
}

int main() {
    
    int select;
    studentDB stu;
    stu.number = 0;
    read(&stu);

    while (1) {
        menu();
        scanf("%d", &select);

        switch (select) {
            case 1:
                display(&stu);
                break;
            case 2:
                if (stu.number >= MAX_NUM) {
                    printf("错误：已达到最大学生数量限制！\n");
                } else {
                    insert(&stu);
                }
                break;
            case 3:
                d(&stu);
                break;
            case 4:
                modify(&stu);
                break;
            case 5:
                search(&stu);
                break;
            case 6:
                sort(&stu);
                break;
            case 7:
                calculate_scores(&stu);
                printf("已重新计算所有学生的平均成绩！\n");
                break;
            case 8:
                write(&stu);
                break;
            case 0:
                exit(0);
            default:
                printf("无效选择，请重新输入！\n");
                break;
        }
    }
    return 0;
}
