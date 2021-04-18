#include "header.h"

int main()
{
    system("gcc imp.c");
    system("./a.out");
    printf("                                    Welcome to Chemistry Lab Mangment system\n              ");
    printf("\n\n");
    struct apparatus *apps;
    struct chemicals *chem;
    struct student *stu;
    apps = malloc(sizeof(struct apparatus));
    apps->name = malloc(sizeof(char)*40);
    apps->id = malloc(sizeof(char)*50);
    apps->app_qty = malloc(sizeof(int));
    apps->cost = (float *)malloc(sizeof(float));
    chem = malloc(sizeof(struct chemicals));
    chem->cost = (float *)malloc(sizeof(float));
    chem->name = malloc(sizeof(char)*40);
    chem->id = malloc(sizeof(char)*50);
    chem->qty = malloc(sizeof(int));
    stu = malloc(sizeof(struct student));
    stu->stu_id =  malloc(sizeof(char)*40);;
    stu->student_name = malloc(sizeof(char)*50) ;
    stu->total_cost = (char *)malloc(sizeof(char) * 50);
    login_page();
    
    return 0;
}
