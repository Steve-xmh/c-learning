#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int id;
    char name[10];
    int chinese_score;
    int math_score;
    int english_score;
} Student;

int main()
{
    Student students[10] = {0};
    int max_scores_list[10] = {-1};
    int current_maxinum_score = 0;

    memset(max_scores_list, -1, 10);

    for (int i = 0; i < 10; i++)
    {
        Student *student = &students[i];
        printf("请输入第 %d 个学生的编号：\n", i);
        scanf("%d", &student->id);
        printf("请输入第 %d 个学生学生名称：\n", i);
        scanf("%10s", student->name);
        printf("请输入第 %d 个学生的语文成绩：\n", i);
        scanf("%d", &student->chinese_score);
        printf("请输入第 %d 个学生的数学成绩：\n", i);
        scanf("%d", &student->math_score);
        printf("请输入第 %d 个学生的英语成绩：\n", i);
        scanf("%d", &student->english_score);
        int total_score = student->chinese_score + student->math_score + student->english_score;
        if (total_score > current_maxinum_score)
        {
            memset(max_scores_list, -1, 10);
            max_scores_list[0] = i;
        }
        else if (total_score == current_maxinum_score)
        {
            // 因为存在同分数的情况，所以要并列第一
            for (int j = 0; j < 10; j++)
            {
                if (max_scores_list[j] == -1)
                {
                    max_scores_list[j] = i;
                    break;
                }
            }
        }
    }

    printf("最高分的同学有：\n");

    for (int i = 0; i < 10; i++)
    {
        if (max_scores_list[i] == -1)
        {
            break;
        }
        else
        {
            Student *student = &students[max_scores_list[i]];
            printf("%s 总分 %d\n", student->name, student->chinese_score + student->math_score + student->english_score);
        }
    }

    return 0;
}
