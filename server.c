#include "header.h"

FILE *chemptr,*appptr,*fineptr;

struct apparatus apps;
struct chemicals chem;
struct student stu;

int login_function()
{
    int login_choice = 0; //To identify whether the user is a student or an admin
    char *username;
    char *password;
    const int size = 20;  //DO not modify constant objects
    username = malloc(sizeof(char)*size);
    password = malloc(sizeof(char)*size);
    char ch;//input character by character
    int i;//loop variable
    int flag = 0;
    printf("Welcome to the Login page");
    while(1)
    {
        printf("1. Students\n2. Admin\nEnter your choice\n");
        scanf("%d",&login_choice);
        switch (login_choice)
        {
        case 1:
            
            printf("Enter username\n");
            scanf("%s",username);
            //fscanf(stdin,username);//By the use of scanf for inputting strings we are taking care of              and avoiding spaces
            do
            {
                printf("Enter Password");//Masking password
                for(i=0;i<20;i++)
                {
                    ch = getchar();
                    if(ch == " " || ch == "\t")
                    {
                        printf("\nNo spaces allowed please retry\n");
                        flag = 1;
                        break;
                    }
                    password[i] = ch;
                    ch = '*' ;
                    printf("%c",ch);
                }
                password[i] = '\0';
            }while(flag);
            for(i = 0; i < 20;i++)
                printf("%c",password[i]);
            break;
        case 2:
            
            printf("Enter username\n");
            scanf("%s",username);//By the use of scanf for inputting strings, we are taking care of 
            printf("Enter Password\n");
            scanf("%[^\t]s",password);//Everything except tab is accepted
            

            break;
        default:
            printf("Incorrect option, please try again!");
            break;
        }
    }

}


void main_menu()
{
    int main_menu_choice = 0;
    for(;;)
    {
        printf("1. Apparatus\n2. Chemicals\n3. Student Fines\n4. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&main_menu_choice);
        switch (main_menu_choice)
        {       
        case 1:
            menu(main_menu_choice);
            break;
        case 2:
            menu(main_menu_choice);
            break;
        case 3:
            menu(main_menu_choice);
            break;    
        case 4:
            exit(0);
        default:
            break;
        }
    }
}

void menu(int main_choice)
{
    int menu_choice;
    float qty;
    char *id;
    for(;;)
    {
        printf("1.Add\n2.Modify\n3.Delete\n4.Show One\n5.Show All\nEnter your choice\n");
        scanf("%d",&menu_choice);
        switch (menu_choice)
        {
        case 1:
            add(main_choice);
            break;
        case 2:
            modify(main_choice,id,qty);
            break;
        case 3:
            printf("Enter the id\n");
            scanf("%s",id);
            printf("Enter the quantity\n");
            scanf("%f",qty);
            delete(main_choice,id);
            break;
        case 4:
            printf("Enter the id\n");
            scanf("%s",id);
            showOne(main_choice,id);
            break;
        case 5:
            showAll(main_choice);
            break;
        default:
            printf("Try again \n");
            break;
        }
    }

}


void add(int main_choice)
{
    char *name_app;
    int exists = 0;
    int qty_damaged = 0;
    float cost_per_unit,total_cost;
    float chem_qty;
    if(main_choice == 1)
    {
        printf("Enter name of the apparatus\n");
        scanf("%s\n",apps.name);
        printf("Enter id\n");
        scanf("%s\n",apps.id);
        printf("Enter the quantity");
        scanf("%d\n",apps.app_qty);
        printf("Enter the cost per unit");
        scanf("%f\n",apps.cost);
        total_cost = apps.cost * apps.app_qty;
        appptr = fopen("apparatus.txt","ra");
        fprintf(appptr,apps.name);
        fprintf(appptr,apps.id);
        fprintf(appptr,apps.app_qty);
        fprintf(appptr,ftoa(apps.cost));
        fprintf(appptr,ftoa(total_cost));
        fclose(appptr);
    }
    else if (main_choice == 2)
    {
        printf("Enter name of the chemicals\n");
        scanf("%s\n",chem.name);
        printf("Enter id\n");
        scanf("%s\n",chem.id);
        printf("Enter the quantity");
        scanf("%f\n",chem.qty);
        printf("Enter the cost per unit");
        scanf("%f\n",chem.cost);
        total_cost = chem.cost * chem.qty;
        chemptr = fopen("chemicals.txt","ra");
        fprintf(chemptr,chem.name);
        fprintf(chemptr,chem.id);
        fprintf(chemptr,ftoa(chem.qty));
        fprintf(chemptr,ftoa(chem.cost));
        fprintf(chemptr,ftoa(total_cost));
        fclose(chemptr);
    }
    else
    {
        printf("Enter name of student\n");
        scanf("%s",stu.student_name);
        printf("Enter the id of the apparatus\n");
        scanf("%s",stu.app_id);
        fineptr = fopen("fines.txt","ra");
        exists = showOne(main_choice,stu.app_id);
        if(exists)
        {
            printf("Enter the quantity damaged\n");
            scanf("%d",stu.qty);
            printf("Enter the cost per unit\n");
            scanf("%f",cost_per_unit);
            stu.total_cost = cost_per_unit * qty_damaged+50;
            fprintf(fineptr,stu.student_name);
            fprintf(fineptr,stu.app_id);
            fprintf(fineptr,stu.qty);
            fprintf(fineptr,ftoa(stu.total_cost));
            modify(main_choice,stu.app_id,stu.qty);
            fclose(fineptr);
        }
        else
        {
            printf("Does not exist\n");
        }
    }
}


int showOne(int main_choice,char *id)
{
    int i;
    if(main_choice == 1)//Apparatus
    {
        appptr = fopen("apparatus.txt","ra");
        
        fclose(appptr);
    }
}