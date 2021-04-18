#include "header.h"

FILE *chemptr, *appptr, *fineptr, *ptr2, *ptr3;
int checking;

int login_function()
{
    int login_choice = 0; //To identify whether the user is a student or an admin
    char *username;
    char *password;
    const int size = 20;  //DO not modify constant objects
    username = malloc(sizeof(char)*size);
    password = malloc(sizeof(char)*size);
    printf("Welcome to the Login page\n");
    while(1)
    {
        printf("1. Students\n2. Admin\nEnter your choice\n");
        checking = scanf("%d", &login_choice);
        switch (login_choice)
        {
        case 1:
            break;
        case 2:
            main_menu();
            break;
            
        default:
            printf("Incorrect option,  please try again!");
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
        checking = scanf("%d", &main_menu_choice);
        if(main_menu_choice > 5 || main_menu_choice < 1)
            main_menu();
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
    char *id = malloc(sizeof(char)*50);
    for(;;)
    {
        printf("1.Add\n2.Modify\n3.Delete\n4.Show One\n5.Show All\nEnter your choice\n");
        checking = scanf("%d", &menu_choice);
        if(menu_choice > 6 || menu_choice < 1)
            menu(main_choice);
        switch (menu_choice)
        {
        case 1:
            add(main_choice);
            break;
        case 2:
            printf("Enter the id\n");
            checking = scanf("%s", id);
            if(checking > 50)
                main_menu();
            modify(main_choice, id);
            break;
        case 3:
            printf("Enter the id\n");
            checking = scanf("%s", id);
            if(checking > 50)
                main_menu();
            delete(main_choice, id);
            break;
        case 4:
            printf("Enter the id\n");
            checking = scanf("%s", id);
            if(checking > 50)
                main_menu();
            checking = showOne(main_choice,id);
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
    stu->stu_id =  malloc(sizeof(char)*40);
    stu->student_name = malloc(sizeof(char)*50) ;
    stu->total_cost = (char *)malloc(sizeof(char)*50);
    char str_cost_one[20],str_cost_total[50],str_chem_qty[50],temp;
   // char name_app[50];
    //int exists = 0;
     float total_cost;
    // float chem_qty;
    
    if(main_choice == 1)
    {
        printf("Enter id\n");
        checking = scanf("%s", apps->id);
        checking = showOne(main_choice,apps->id);
        if(checking != 0)
        {
            printf("Enter name of the apparatus\n");
            checking = scanf("%s", apps->name);
            if(checking > 50)
            {
                printf("Invalid Name\n");
                exit(0);
            }
            printf("Enter the quantity\n");
            checking = scanf("%d", apps->app_qty);
            printf("Enter the cost per unit\n");
            checking = scanf("%f", apps->cost);
            gcvt(*apps->cost, 7, str_cost_one);
            total_cost = *apps->cost * *apps->app_qty;  
            gcvt(total_cost, 7, str_cost_total);
        
            appptr = fopen("apparatus.txt", "a+");
            if (!appptr)
            {
            // Error in file opening
                printf("Can't open file\n");
                return ;
            }
            fprintf(appptr,"\n");
            fprintf(appptr, "%s,%s,%d,%s,%s", apps->id, apps->name, *apps->app_qty, str_cost_one, str_cost_total);
            if(fclose(appptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }           
        }
        else
        {
            printf("Entry already exists\nTaking you to modify\n");
            modify(main_choice,apps->id);

        }
    }
    else if (main_choice == 2)
    {
        
        printf("Enter id\n");
        checking = scanf("%s", chem->id);
        if(!showOne(main_choice,chem->id))
        {
            printf("Enter name of the chemicals\n");
            checking = scanf("%s", chem->name);
            printf("Enter the quantity\n");
            checking = scanf("%f", chem->qty);
            gcvt(*chem->qty, 6, str_chem_qty);
            printf("Enter the cost per unit\n");
            checking = scanf("%f", chem->cost);
            gcvt(*chem->cost, 7, str_cost_one);
            total_cost = *chem->cost * *chem->qty;
            gcvt(total_cost, 7, str_cost_total);
            chemptr = fopen("chemicals.txt", "a+");
            if (!chemptr)
            {
            // Error in file opening
            printf("Can't open file\n");
            return ;
            }
            fprintf(chemptr,"\n");
            fprintf(chemptr, "%s,%s %s,%s,%s", chem->id, chem->name, str_chem_qty, str_cost_one, str_cost_total);
            if(fclose(chemptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }      
            
        }
        else
        {
            printf("Entry already exists\nTaking you to modify\n");
            modify(main_choice,chem->id);
        }
    }
    else
    {
        printf("Enter the id of the apparatus\n");
        checking = scanf("%s", stu->stu_id);
        
        
        if(!showOne(main_choice,stu->stu_id))
        {
            printf("Enter name of student\n");
            checking = scanf("%s", stu->student_name);
            fineptr = fopen("fines.txt", "a+");
            if (!fineptr)
            {
                // Error in file opening
                printf("Can't open file\n");
                return ;
            }
       
            printf("Enter the cost\n");
            checking = scanf("%s", stu->total_cost);
            fprintf(fineptr,"\n");
            fprintf(fineptr, "%s,%s,%s", stu->stu_id, stu->student_name, stu->total_cost);
           if(fclose(fineptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }      
        }
        else
        {
            printf("Entry already exists\nTaking you to modify\n");
            modify(main_choice, stu->stu_id);
            
        }
    }
}

int showOne(int main_choice,char *id)
{
    char *id_find;
    int line_no = 0;
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
                //line_no = ftell(appptr);
                line_no++;
                if(fclose(appptr) != 0) 
                {
                    printf("File not closed\n");
                    exit(0);
                }      
                
                return line_no;
            }
            else
            {
                flag = 0;
                line_no++;
            }

        }
        if(!flag)
        {
            printf("Entry Not found\n");
            if(fclose(appptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }      
            return 0;
        }
        
       
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
 
        while(fgets(line,1024,chemptr))
        {
            strcpy(line_cpy,line);
            id_find = strtok(line,",");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                line_no++;
                flag = 1;
                if(fclose(chemptr) != 0) 
                {
                    printf("File not closed\n");
                    exit(0);
                }      
                return line_no;
            }
            else
            {
                line_no++;
                flag = 0;
            }
            
            //printf("%s\n",id_find);
        }
        if(!flag)
        {
            printf("Entry Not found\n");
            if(fclose(chemptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }      
            return 0;
        }
        
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
        while(fgets(line,1024,fineptr))
        {
            strcpy(line_cpy,line);
            id_find = strtok(line,",");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                line_no++;
                flag = 1;
                if(fclose(fineptr) != 0) 
                {
                    printf("File not closed\n");
                    exit(0);
                }      
                return line_no;
            }
            else
            {
                line_no++;
                flag = 0;
            }
            
            //printf("%s\n",id_find);
        }
        if(!flag)
        {
            printf("Entry Not found\n");
            if(fclose(fineptr) != 0) 
            {
                printf("File not closed\n");
                exit(0);
            }      
            return 0;
        }
       
    }
}


void delete(int main_choice,char *id)
{
    int x = -1;
    int lines = 0,i;
    char line[1024];
    
    if(main_choice == 1)//Apparatus
    {
        ptr2 = fopen("apparatus.txt","r");
        ptr3 = fopen("apparatus2.txt","a+");
        if (!ptr2)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }

        if (!ptr3)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }
        
        x = showOne(main_choice,id);
       
        if(x != 0 )
        {
           
            // for(i = 0;i < x-1;i++)
            // {
            //     fgets(line,1024,ptr2);//fseek(appptr,)
            // }
                
            // rewind(ptr2);
            for(i = 0;i < x-1;i++)
            {
                fgets(line,1024,ptr2);
                fputs(line,ptr3);
            }

            fgets(line,1024,ptr2);
            // char a[100];
            // for(int i1=0;)
           // fgets(line,1024,ptr2);
            for(i = 1, x = 1; !feof(ptr2) ;i++)
                {
                    
                    fgets(line,1024,ptr2);
                    fputs(line,ptr3);
                    
                }
            rewind(ptr2);
            rewind(ptr3);
            fclose(ptr2);
            fclose(ptr3);
            system("rm apparatus.txt");
            system("mv apparatus2.txt apparatus.txt");
            
        }
     }
    else if(main_choice == 2)//CHEMICALS
    {
        ptr2 = fopen("chemicals.txt","r");
        ptr3 = fopen("chemicals2.txt","a+");
        if (!ptr2)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }

        if (!ptr3)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }

        x = showOne(main_choice,id);
    
        if(x != 0)
        {
           
            for(i = 0;i < x-1;i++)
            {
                fgets(line,1024,ptr2);//fseek(appptr,)
            }
                
            rewind(ptr2);
            for(i = 0;i < x-1;i++)
            {
                    fgets(line,1024,ptr2);
                    fputs(line,ptr3);
            }

            fgets(line,1024,ptr2);
            for(i = 1, x = 1; !feof(ptr2) ;i++)
                {
                    
                    fgets(line,1024,ptr2);
                    fputs(line,ptr3); 
                    
                }
            rewind(ptr2);
            rewind(ptr3);
            fclose(ptr2);
            fclose(ptr3);
            system("rm chemicals.txt");
            system("mv chemicals2.txt chemicals.txt");
            
        }
    }
    else
    {
        ptr2 = fopen("fines.txt","r");
        ptr3 = fopen("fines2.txt","a+");

        if (!ptr2)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }

        if (!ptr3)
        {
            // Error in file opening
            printf("Can't open file\n");
            return ;
        }

        x = showOne(main_choice,id);

        if(x != 0)//it exists
        {
            
                for(i = 0;i < x-1;i++)
                {
                    fgets(line,1024,ptr2);
                }
                fgets(line,1024,ptr2);


                rewind(ptr2);
                for(i = 0;i < x-1;i++)
                    {
                        fgets(line,1024,ptr2);//fseek(appptr,)
                        fputs(line,ptr3);
                    }

                fgets(line,1024,ptr2);
                for(i = 1, x = 1; !feof(ptr2) ;i++)
                    {
                        
                        fgets(line,1024,ptr2);
                        fputs(line,ptr3);
                    }
                rewind(ptr2);
                rewind(ptr3);
                fclose(ptr2);
                fclose(ptr3);
                system("rm fines.txt");
                system("mv fines2.txt fines.txt");
            
        }
    }
}


void showAll(int choice)
{
    if(choice == 1)
    {
        appptr = fopen("apparatus.txt", "r");
        if (!appptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line, 1024, appptr))
        {
            printf("%s", line);
        }
        printf("\n");
    }
    else if(choice == 2)
    {
        chemptr = fopen("chemicals.txt", "r");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line, 1024, chemptr))
        {
            printf("%s", line);
        }
        printf("\n");
    }
    else
    {
        fineptr = fopen("fines.txt", "r");
        if (!fineptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return ;
        }
        char line[1024];
        while(fgets(line, 1024, fineptr))
        {
            printf("%s", line);
        }
        printf("\n");
    }
}


void modify(int ch,char *id)
{
    if(showOne(ch,id))
    {
        delete(ch,id);
        add(ch);
    }

}

