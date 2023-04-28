#include <stdio.h>

typedef struct Student {
    char* name;             // 姓名
    double base_salary;     // 基本工资
    double floating_salary; // 浮动工资
    double outcome;         // 支出
} Student;

int main()
{
    Student workers_data[] = {
        {"Tom", 1240.00, 800.00, 75.00},
        {"Lucy", 1360.00, 900.00, 50.00},
        {"Jack", 1560.00, 1000.00, 80.00},
    };
    
    printf("姓名\t基本工资\t浮动工资\t支出\n");
    for (int i = 0; i < 3; i++)
    {
        Student worker_data = workers_data[i];
        printf(
            "%s\t%f\t%f\t%f\n",
            worker_data.name,
            worker_data.base_salary,
            worker_data.floating_salary,
            worker_data.outcome
        );
    }
    
    return 0;
}
