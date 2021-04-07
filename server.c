#include "header.h"

FILE *chemptr,*appptr,*fineptr;


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
    printf("Welcome to the Login page\n");
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
                    if(ch == ' ' || ch == '\t')
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
            main_menu();
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
        case 2:
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
        // case 2:
        //     modify(main_choice,id,qty);
        //     break;
        // case 3:
        //     printf("Enter the id\n");
        //     scanf("%s",id);
        //     printf("Enter the quantity\n");
        //     scanf("%f",qty);
        //     delete(main_choice,id);
        //     break;
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
    stu->app_id =  malloc(sizeof(char)*40);;
    stu->qty = malloc(sizeof(int));
    stu->student_name = malloc(sizeof(char)*50) ;
    stu->total_cost = (float *)malloc(sizeof(float));
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
        if (!fineptr)
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
           // modify(1,stu->app_id,*stu->qty);
            fclose(fineptr);
        }
        else
        {
            fclose(fineptr);
            printf("Does not exist\n");
        }
    }
}



int showOne(int main_choice,char *id)
{
    char *id_find;
    int i;
    const char x = ',';
    if(main_choice == 1)//Apparatus
    {
        appptr = fopen("apparatus.txt","r");
        if (!appptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1,flag = 1;
        int line_no = 0;
        while(fgets(line,1024,appptr))
        {
            strcpy(line_cpy,line);
            id_find = strtok(line,",");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                flag = 1;
                return 1;
            }
            else
            {
                flag = 0;
            }
            
            //printf("%s\n",id_find);
        }
        if(!flag)
        {
            printf("Not found\n");
            return 0;
        }
        fclose(appptr);
       
    }
    else if(main_choice == 2)//Chemicals
    {
        chemptr = fopen("chemicals.txt","r");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1,flag = 1;
        int line_no = 0;
        while(fgets(line,1024,chemptr))
        {
            strcpy(line_cpy,line);
            id_find = strtok(line,",");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                flag = 1;
                return 1;
            }
            else
            {
                flag = 0;
            }
            
            //printf("%s\n",id_find);
        }
        if(!flag)
        {
            printf("Not found\n");
            return 0;
        }
        fclose(appptr);
    }
    else
    {
        fineptr = fopen("fines.txt","r");
        if (!fineptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1,flag = 1;
        int line_no = 0;
        while(fgets(line,1024,fineptr))
        {
            strcpy(line_cpy,line);
            id_find = strtok(line,",");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                flag = 1;
                return 1;
            }
            else
            {
                flag = 0;
            }
            
            //printf("%s\n",id_find);
        }
        if(!flag)
        {
            printf("Not found\n");
            return 0;
        }
        fclose(appptr);
    }
}


void showAll(int choice)
{
    if(choice == 1)
    {
        appptr = fopen("apparatus.txt","r");
        if (!appptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line,1024,appptr))
        {
            printf("%s",line);
        }
        printf("\n");
    }
    else if(choice == 2)
    {
        chemptr = fopen("chemicals.txt","r");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line,1024,chemptr))
        {
            printf("%s",line);
        }
        printf("\n");
    }
    else
    {
        fineptr = fopen("fines.txt","r");
        if (!fineptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line,1024,fineptr))
        {
            printf("%s",line);
        }
        printf("\n");
    }
}