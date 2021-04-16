#include <stdio.h>
#include <stdlib.h>
#include <string.h>




struct apparatus
{
    char *id;
    char *name;
    int *app_qty;
    float *cost;
};

struct chemicals
{
    char *id;
    char *name;
    float *qty;
    float *cost;
};


struct student
{
    char *student_name;
    char *app_id;
    float *total_cost;
    int *qty;
};


int login_function();
void main_menu();
void menu(int);
void add(int);
void modify(int,char * );
void delete(int,char *);
void showAll(int);
int showOne(int,char *);
