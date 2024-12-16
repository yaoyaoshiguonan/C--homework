#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>  // ����Windowsϵͳ�Ŀ���̨����

#define MAX_NUM 2000

// ѧ����Ϣ�ṹ��
typedef struct {
    char no[30];          // ѧ��
    char name[30];        // ����
    char sex[10];         // �Ա�
    char thought[20];     // ˼�����
    char major[30];       // ѧ��רҵ
    float practice;       // ʵ������
    float health;         // ��������
    float extraPoints;    // ���ӷ�
    float totalScore;     // �ܳɼ�
    float averageScore;   // ƽ���ɼ�
} student;

// ѧ�����ݿ�ṹ��
typedef struct {
    student stu[MAX_NUM];
    int number;
} studentDB;


// �����ܳɼ���ƽ���ɼ�
void calculate_scores(studentDB *temp) {
    for (int i = 0; i < temp->number; i++) {
        temp->stu[i].totalScore = temp->stu[i].practice + temp->stu[i].health + temp->stu[i].extraPoints;
        temp->stu[i].averageScore = temp->stu[i].totalScore / 3;
    }
}

// ��ȡѧ������
void read(studentDB *temp) {
    FILE *infile = fopen("./����.txt", "r");
    if (!infile) {
        printf("�ļ���ʧ�ܣ�\n");
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
            printf("���棺���ݳ���������� %d �����������ݽ������ԣ�\n", MAX_NUM);
            break;
        }
        temp->number++;
    }
    fclose(infile);
    calculate_scores(temp);
    printf("�ɹ���ȡ %d ��ѧ����¼��\n", temp->number);
}

// ��ʾѧ����Ϣ
void display(studentDB *temp) {
    int page_size = 20; // ÿҳ��ʾ20����¼
    int current_page = 0;
    int total_pages = (temp->number + page_size - 1) / page_size;
    char choice;

    while (1) {
        system("cls"); // ����
        printf("\n��ǰ�� %d/%d ҳ\n", current_page + 1, total_pages);
        printf("================================================================================================================\n");
        printf("|%-11s|%-10s|%-6s|%-10s|%-15s|%-10s|%-10s|%-8s|%-8s|%-8s|\n",
               "ѧ��", "����", "�Ա�", "˼�����", "ѧ��רҵ", "ʵ������", "��������", "���ӷ�", "�ܳɼ�", "ƽ���ɼ�");
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
        printf("n-��һҳ, p-��һҳ, q-�˳�\n��ѡ��: ");
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
                printf("��Ч���룡\n");
        }
    }
}

// ɾ��ѧ����Ϣ 
void d(studentDB *temp) {
    char no[30];
    printf("������Ҫɾ����ѧ��ѧ�ţ�");
    scanf("%s", no);

    // ����ѧ����ɾ��
    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            // ��������ɾ��ѧ��
            for (int j = i; j < temp->number - 1; j++) {
                temp->stu[j] = temp->stu[j + 1]; // �������ѧ������ǰ��
            }
            temp->number--; // ����ѧ������
            printf("ѧ����Ϣ��ɾ����\n");
            return; // �ҵ���ɾ�����˳�
        }
    }
    // ���δ�ҵ���ѧ�ŵ�ѧ��
    printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
}

// ��ʾ�˵�
void menu() {
    printf("\n\n\t****************************ѧ���ۺϳɼ�����ϵͳ*********************\n");
    printf("\t*                              1.��ʾѧ����Ϣ                           *\n");
    printf("\t*                              2.����ѧ����Ϣ                           *\n");
    printf("\t*                              3.ɾ��ѧ����Ϣ                           *\n");
    printf("\t*                              4.�޸�ѧ����Ϣ                           *\n");
    printf("\t*                              5.��ѯѧ����Ϣ                           *\n");
    printf("\t*                              6.����ѧ���ɼ�                           *\n");
    printf("\t*                              7.����ѧ��ƽ���ɼ�                       *\n");
    printf("\t*                              8.����ѧ����Ϣ                           *\n");
    printf("\t*                              9.�û�Ȩ�޹�����¼ϵͳ��δʵ�֣�       *\n");
    printf("\t*                              10.�༶����ͳ�ƣ�δʵ�֣�                *\n");
    printf("\t*                              0.�˳�ϵͳ                               *\n");
    printf("\t***********************************************************************\n");
    printf("��ѡ�����: ");
}

// ����ѧ����Ϣ
void insert(studentDB *temp) {
    char no[30];
    printf("������ѧ����ѧ�ţ�");
    scanf("%s", no);

    // ѧ����Ч�Լ��
    if (strlen(no) != 11) {
        printf("ѧ��ӦΪ11λ�����������룡\n");
        return;
    }

    // ���ѧ���Ƿ��Ѵ���
    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("��ѧ�ŵ�ѧ���Ѵ��ڣ�\n");
            return;
        }
    }

    // ����ѧ����Ϣ
    strcpy(temp->stu[temp->number].no, no);
    printf("������������");
    scanf("%s", temp->stu[temp->number].name);
    printf("�������Ա�");
    scanf("%s", temp->stu[temp->number].sex);
    printf("������˼����£�");
    scanf("%s", temp->stu[temp->number].thought);
    printf("������ѧ��רҵ��");
    scanf("%s", temp->stu[temp->number].major);
    printf("������ʵ�������ɼ���");
    scanf("%f", &temp->stu[temp->number].practice);
    printf("�������������ʳɼ���");
    scanf("%f", &temp->stu[temp->number].health);
    printf("�����븽�ӷ֣�");
    scanf("%f", &temp->stu[temp->number].extraPoints);

    // �����ܳɼ���ƽ���ɼ�
    calculate_scores(temp);

    temp->number++;
    printf("ѧ����Ϣ����ɹ���\n");
}

// �޸�ѧ����Ϣ
void modify(studentDB *temp) {
    char no[30];
    printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
    scanf("%s", no);

    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("��ǰ��Ϣ��%s %s %s %s %s %.2f %.2f %.2f\n", temp->stu[i].no, temp->stu[i].name, temp->stu[i].sex,
                   temp->stu[i].thought, temp->stu[i].major, temp->stu[i].practice, temp->stu[i].health, temp->stu[i].extraPoints);
            printf("������Ҫ�޸ĵ���Ŀ��\n");
            printf("1. ����\n2. �Ա�\n3. ˼�����\n4. ѧ��רҵ\n5. ʵ������\n6. ��������\n7. ���ӷ�\n");
            printf("��ѡ��");
            int choice;
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    printf("�������µ�������");
                    scanf("%s", temp->stu[i].name);
                    break;
                case 2:
                    printf("�������µ��Ա�");
                    scanf("%s", temp->stu[i].sex);
                    break;
                case 3:
                    printf("�������µ�˼����£�");
                    scanf("%s", temp->stu[i].thought);
                    break;
                case 4:
                    printf("�������µ�ѧ��רҵ��");
                    scanf("%s", temp->stu[i].major);
                    break;
                case 5:
                    printf("�������µ�ʵ��������");
                    scanf("%f", &temp->stu[i].practice);
                    break;
                case 6:
                    printf("�������µ��������ʣ�");
                    scanf("%f", &temp->stu[i].health);
                    break;
                case 7:
                    printf("�������µĸ��ӷ֣�");
                    scanf("%f", &temp->stu[i].extraPoints);
                    break;
                default:
                    printf("��Чѡ�\n");
                    return;
            }
            // �����ܳɼ���ƽ���ɼ�
            calculate_scores(temp);
            printf("��Ϣ�޸ĳɹ���\n");
            return;
        }
    }
    printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
}

// ��ѯѧ����Ϣ
void search(studentDB *temp) {
    char no[30];
    printf("������Ҫ��ѯ��ѧ��ѧ�ţ�");
    scanf("%s", no);

    for (int i = 0; i < temp->number; i++) {
        if (strcmp(temp->stu[i].no, no) == 0) {
            printf("ѧ����Ϣ��%s %s %s %s %s %.2f %.2f %.2f %.2f %.2f\n", temp->stu[i].no, temp->stu[i].name, temp->stu[i].sex,
                   temp->stu[i].thought, temp->stu[i].major, temp->stu[i].practice, temp->stu[i].health, temp->stu[i].extraPoints,
                   temp->stu[i].totalScore, temp->stu[i].averageScore);
            return;
        }
    }
    printf("δ�ҵ���ѧ�ŵ�ѧ����\n");
}

// ����ȽϺ��������ڱȽ�����ѧ����¼
int compareStudents(student *a, student *b, int criteria[], int numCriteria) {
    for (int i = 0; i < numCriteria; i++) {
        float diff = 0;
        switch (criteria[i]) {
            case 1: // �ܳɼ�
                diff = b->totalScore - a->totalScore;
                break;
            case 2: // ƽ���ɼ�
                diff = b->averageScore - a->averageScore;
                break;
            case 3: // ʵ������
                diff = b->practice - a->practice;
                break;
            case 4: // ��������
                diff = b->health - a->health;
                break;
            case 5: // ���ӷ�
                diff = b->extraPoints - a->extraPoints;
                break;
            case 6: // ѧ��
                diff = strcmp(a->no, b->no);
                break;
        }
        if (diff != 0) {
            return (diff > 0) ? 1 : -1;
        }
    }
    return 0;
}

// ����ѧ���ɼ�
void sort(studentDB *temp) {
    int criteria[6]; // �洢����ؼ���
    int numCriteria = 0; // �ؼ�������
    
    printf("\n��ؼ�������\n");
    printf("����ؼ���ѡ�\n");
    printf("1. �ܳɼ�\n2. ƽ���ɼ�\n3. ʵ������\n4. ��������\n5. ���ӷ�\n6. ѧ��\n");
    printf("����������ؼ��ֵ�����(1-6): ");
    scanf("%d", &numCriteria);
    
    if (numCriteria < 1 || numCriteria > 6) {
        printf("��Ч�Ĺؼ���������\n");
        return;
    }
    
    printf("��������������ؼ���(�ÿո�ָ�): ");
    for (int i = 0; i < numCriteria; i++) {
        scanf("%d", &criteria[i]);
        if (criteria[i] < 1 || criteria[i] > 6) {
            printf("��Ч�Ĺؼ���ѡ��\n");
            return;
        }
    }
    
    // ð������ʹ�ö�ؼ��ֱȽ�
    student t;
    for (int i = 0; i < temp->number - 1; i++) {
        for (int j = 0; j < temp->number - 1 - i; j++) {
            if (compareStudents(&temp->stu[j], &temp->stu[j + 1], criteria, numCriteria) > 0) {
                // ����ѧ����¼
                t = temp->stu[j];
                temp->stu[j] = temp->stu[j + 1];
                temp->stu[j + 1] = t;
            }
        }
    }
    
    printf("������ɣ�\n");
    printf("�����������������ȼ����У�\n");
    for (int i = 0; i < numCriteria; i++) {
        switch (criteria[i]) {
            case 1:
                printf("%d. �ܳɼ�\n", i + 1);
                break;
            case 2:
                printf("%d. ƽ���ɼ�\n", i + 1);
                break;
            case 3:
                printf("%d. ʵ������\n", i + 1);
                break;
            case 4:
                printf("%d. ��������\n", i + 1);
                break;
            case 5:
                printf("%d. ���ӷ�\n", i + 1);
                break;
            case 6:
                printf("%d. ѧ��\n", i + 1);
                break;
        }
    }
}

// д��ѧ����Ϣ
void write(studentDB *temp) {
    FILE *outfile = fopen("./����.txt", "w");
    if (!outfile) {
        printf("�ļ���ʧ�ܣ�\n");
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
    printf("�ɹ����� %d ��ѧ����¼��\n", temp->number);
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
                    printf("�����Ѵﵽ���ѧ���������ƣ�\n");
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
                printf("�����¼�������ѧ����ƽ���ɼ���\n");
                break;
            case 8:
                write(&stu);
                break;
            case 0:
                exit(0);
            default:
                printf("��Чѡ�����������룡\n");
                break;
        }
    }
    return 0;
}
