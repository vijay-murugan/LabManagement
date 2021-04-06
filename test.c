#include <stdio.h> 
#include <string.h> 
#include "header.h"
 
FILE *chemptr,*appptr,*fineptr;

 struct apparatus *apps;
    struct chemicals *chem;
    struct student *stu;


void main() 
{ 
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
 stu->app_id =  malloc(sizeof(char)*40);;
 stu->qty = malloc(sizeof(int));
 stu->student_name = malloc(sizeof(char)*50) ;
 stu->total_cost = (float *)malloc(sizeof(float));
 add(2);
} 

void add(int main_choice)
{
    char str_cost_one[20],str_cost_total[50],str_chem_qty[50],temp;
    char name_app[50];
    int exists = 0;
    float cost_per_unit,total_cost;
    float chem_qty;
    if(main_choice == 1)
    {
        printf("Enter name of the apparatus\n");
        scanf("%[^\n]s",apps->name);//WE need to input spaces too!!
        printf("Enter id\n");
        temp = getchar();
        scanf("%[^\n]s",apps->id);
        printf("Enter the quantity\n");
        scanf("%d",apps->app_qty);
        printf("Enter the cost per unit\n");
        scanf("%f",apps->cost);
        gcvt(*apps->cost,7,str_cost_one);
        total_cost = *apps->cost * *apps->app_qty;  
        gcvt(total_cost,7,str_cost_total);
        appptr = fopen("apparatus.txt","a+");
        if (!appptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        fprintf(appptr,"%s,%s,%d,%s,%s\n",apps->id,apps->name,*apps->app_qty,str_cost_one,str_cost_total);
        fclose(appptr);
    }
    else if (main_choice == 2)
    {
        printf("Enter name of the chemicals\n");
        scanf("%s[^\n]",chem->name);
        printf("Enter id\n");
        temp = getchar();
        scanf("%s[^\n]",chem->id);
        printf("Enter the quantity\n");
        scanf("%f",chem->qty);
        gcvt(*chem->qty,6,str_chem_qty);
        printf("Enter the cost per unit\n");
        scanf("%f",chem->cost);
        gcvt(*chem->cost,7,str_cost_one);
        total_cost = *chem->cost * *chem->qty;
        gcvt(total_cost,7,str_cost_total);
        chemptr = fopen("chemicals.txt","a+");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        fprintf(chemptr,"%s,%s,%s,%s,%s\n",chem->id,chem->name,str_chem_qty,str_cost_one,str_cost_total);
        fclose(chemptr);
    }
    else
    {
        printf("Enter name of student\n");
        scanf("%s",stu->student_name);
        printf("Enter the id of the apparatus\n");
        scanf("%s",stu->app_id);
        fineptr = fopen("fines.txt","a+");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        exists = showOne(1,stu->app_id);//search if the apparatus id is valid
        if(exists)
        {
            printf("Enter the quantity damaged\n");
            scanf("%d",stu->qty);
            printf("Enter the cost per unit\n");
            scanf("%f",cost_per_unit);
            *stu->total_cost = cost_per_unit * *stu->qty+50;
            gcvt(total_cost,7,str_cost_total);
            fprintf(fineptr,"%s,%s,%d,%s\n",stu->student_name,stu->app_id,stu->qty,total_cost);
            modify(1,stu->app_id,*stu->qty);
            fclose(fineptr);
        }
        else
        {
            printf("Does not exist\n");
        }
    }
}
