#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h> 
#include<ctype.h>
#include<stdbool.h>

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
    char *stu_id;
    char *total_cost;
    
};

void getdetails(char details[]);
bool check_password_strength(char pa[]);
bool uniquename(char *usrnm);
void encrypt_pass(char std_pass[],char enc_pass[]);
void login_granted();
void create_account_student();
void decrypt_and_check(char username[],char password[]);
void login_page();
void admin_login();
int string_matching(char main_word[],char sub_word[]);
int check_student_details(char usr[],char pass[]);
void student_login();







int login_function();
void main_menu();
void menu(int);
void add(int);
void modify(int,char * );
void delete(int,char *);
void showAll(int);
int showOne(int,char *);
