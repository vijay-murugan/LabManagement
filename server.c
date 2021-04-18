#include "header.h"
int counter=0;
int cn=0;
int ctr=0;
int ctr1=0;
void getdetails(char details[])
{
    static struct termios oldt, newt;
    int i = 0;
    int c;
    /*saving the old settings of STDIN_FILENO and copy settings for resetting*/
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    /*setting the approriate bit in the termios struct*/
    newt.c_lflag &= ~(ECHO);          

    /*setting the new bits*/
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*reading the details from the console*/
    
    while ((c=getchar())!= 10 && c != EOF && i < 100){
          details[i++] =(char) c;
    }
    details[i] = '\0';

    /*resetting our old STDIN_FILENO*/ 
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

}




bool check_password_strength(char pa[])
{
    int lengt=(int)strlen(pa);
    int counter_for;
    int uppercase=0,lowercase=0,specialcharacters=0;
    for(counter_for=0;counter_for<lengt;counter_for++)
    {
        if((int)pa[counter_for]>=65 && (int)pa[counter_for]<=90)
        {
            uppercase++;
        }
        else if((int)pa[counter_for]>=97 && (int)pa[counter_for]<=122)
        {
            lowercase++;
        }
        else
        {
            specialcharacters++;
        }
    }
    if(uppercase>=1 && (lowercase>=1 && specialcharacters >=1))
    {
        return true;

    }
    else
    {
        return false;
    }
}







bool uniquename(char *usrnm)
{
    FILE *fp=fopen(".student_login_details.txt","r");
    if(fp==NULL)
    {
        return 1;
    }
    char temp[100];
    char *user_by_user;
    while(fgets(temp,100,fp))
    {
            //printf("%s\n",temp);
            user_by_user = strtok(temp,",");
            
            if(strcmp(usrnm,user_by_user)==0)
            {
                return false;
            }
            //printf("%s is userbyuser\n",user_by_user);
    }
    if(fclose(fp)!=0)
    {
        printf("Error while closing file\n");
    }
    return true;
}

void encrypt_pass(char std_pass[],char enc_pass[])
{
    int len_password=(int)strlen(std_pass);
    int counter_for_loop=0;
    for(counter_for_loop=0;counter_for_loop<len_password;counter_for_loop++)
    {
        char temp=std_pass[counter_for_loop];
        if(counter_for_loop%2==0)
        {
            int no=(int)temp -5 ;
            enc_pass[counter_for_loop]=(char)no;
        }
        else
        {
            
            int no=(int)temp  + 5;
            enc_pass[counter_for_loop]=(char)no;
        }
        
    }
    enc_pass[counter_for_loop]='\0';
}

void login_granted()
{
    int return_val;
    int admin_choice;
    return_val=system("clear");
    printf("                                                                                                                                    Welcome admin\n");
    /*printf("1)Add fine for student\n");
    printf("2)Create an account for student\n");
    printf("3)To exit\n");
    return_val=scanf("%d",&admin_choice);
    if(return_val==EOF)
    {
        printf("Error in input entered sorry\n");
        exit(0);
    }
    if(admin_choice==1)
    {
        printf("Done stuff\n");
        login_granted();
    }
    else if(admin_choice==3)
    {
        system("rm .admin.txt");
        exit(0);
    }
    else if(admin_choice==2)
    {
        create_account_student();
    }*/


    int main_menu_choice = 0;
     for(;;)
     {
         printf("1. Apparatus\n2. Chemicals\n3. Student Fines\n4. Create an account for Student\n5. Exit\n");
         printf("Enter your choice\n");
         return_val=scanf("%d",&main_menu_choice);
         if(return_val==EOF)
         {
             printf("Error in entered input\n");
         }
         switch (main_menu_choice)
         {       
         case 1:
         case 2:
         case 3:
             menu(main_menu_choice);
             break;    
         case 4:
             create_account_student();
             break;
         case 5:
            system("rm .admin.txt");
             exit(0);
         default:
             break;
         }
    }
    
}

void create_account_student()
{
    char student_username[100];
    char student_password[100];
    int return_val;
    //system("clear");
    if(ctr!=0)
    {
        printf("Necessary crieteria for password not matched\n");
    }
    printf("Student login UserID:-");
    return_val=scanf("%s",student_username);
    if(return_val==EOF)
    {
        printf("Error in input entered sorry\n");
        exit(0);
    }
    printf("Please chooose a password with atleast 1 Upper case 1 Lower case and 1 Special charcter\n");
    printf("Student Password:-");
    if(cn==0)
    {
        int temp;
        temp=getchar();
    }
    getdetails(student_password);
    if(check_password_strength(student_password) && uniquename(student_username))
    {
        int return_value;
        FILE *fp=fopen(".student_login_details.txt","a");
        if(fp!=NULL)
        {
            int loop_counter;
            for(loop_counter=0;loop_counter<(int)strlen(student_username);loop_counter++)
            {
                return_value=fputc(student_username[loop_counter],fp);
                if(return_val==EOF)
                {
                    printf("Error in placing character in file\n");
                    exit(0);
                }
            }
            return_val=fputc((int)',',fp);
                if(return_val==EOF)
                {
                    printf("Error in placing character in file\n");
                    exit(0);
                }
            char encry_pass[100];
            encrypt_pass(student_password,encry_pass);
            for(loop_counter=0;loop_counter<(int)strlen(encry_pass);loop_counter++)
            {
                return_val=fputc(encry_pass[loop_counter],fp);
                if(return_val==EOF)
                {
                    printf("Error in placing character in file\n");
                    exit(0);
                }
            }
            return_val=fputc((int)',',fp);
                if(return_val==EOF)
                {
                    printf("Error in placing character in file\n");
                    exit(0);
                }
            return_val=fputc(10,fp);
                if(return_val==EOF)
                {
                    printf("Error in placing character in file\n");
                    exit(0);
                }
            if(fclose(fp)!=0)
            {
                printf("Error in closing file\n");
            }
            login_granted();
        }
        else
        {
            printf("File opening error\n");
        }
    }
    if(uniquename(student_username)==0)
    {
        printf("\nUseraname already exists\n");
        create_account_student();
    }
    else
    {
        ctr++;
        
        create_account_student();
    }

}


void decrypt_and_check(char username[],char password[])
{

    FILE *fp1= fopen(".admin.txt","r");
    if(fp1!=NULL)
    {
        char decoded[100];
        char decopass[100];
        int a;
        a=fgetc(fp1);
        int counter_while=0;
        int no_of_odd=0,no_of_even=0;
        while(a!=(int)'\n')
        {
            if(counter_while%2==0)
            {
                no_of_odd++;
                char temp=(char)a;
                int no=(int)temp - (no_of_odd)*3;
                decoded[counter_while]=(char)no;
            }
            else
            {
                no_of_even++;
                char temp=(char)a;
                int no=(int)temp - (no_of_even)*4;
                decoded[counter_while]=(char)no;
            }
            counter_while++;
            a=fgetc(fp1);
        }
        decoded[counter_while]='\0';
        //printf("Decoded username is %s \n",decoded);
        no_of_odd=0,no_of_even=0;
        int b;
        b=fgetc(fp1);
        counter_while=0;
        while(b!=EOF)
        {
            if(counter_while%2==0)
            {
                no_of_odd++;
                char temp=(char)b;
                int no=(int)temp + (no_of_odd)*3;
                decopass[counter_while]=(char)no;
                //printf("b is %c and decoded is %c\n",b,(char)no);
            }
            else
            {
                no_of_even++;
                char temp=(char)b;
                int no=(int)temp + (no_of_even)*4;
                decopass[counter_while]=(char)no;
                //printf("b is %c and decoded is %c\n",b,(char)no);
            }
            counter_while++;
            b=fgetc(fp1);
        }
        decopass[counter_while]='\0';
        //printf("Decoded password is %s \n",decopass);
        

        if(strcmp(decopass,password)==0 && strcmp(decoded,username)==0)
        {
            login_granted();
        }
        else
        {
            printf("Invalid Login attempt\n");
            counter++;
            admin_login();
        }
    }
    else
    {
        printf("Problem with file sorry\n");
    }

}

// Login page 
void login_page()
{
    int login_choice;
    char confirm_login_choice[2];
    printf("Would You like to Login as an\n1)Admin or\n2)student\n");
    if(scanf("%d",&login_choice)>0)
    {
        if(login_choice==1)
        {
            admin_lo:
            printf("Logging in as admin Press Y to continue or press N to switch to student login\n");//gives multiple lines if long string enetred
            if(scanf(" %s",confirm_login_choice)>0)
            {
                if(strlen(confirm_login_choice)==1)
                {
                    if(strcmp(confirm_login_choice,"Y")==0)
                    {
                        admin_login();
                    }
                    else if(strcmp(confirm_login_choice,"N")==0)
                    {
                        student_login();
                    }
                    else
                    {
                        printf("Invalid Login Choice Entered\n");
                        goto admin_lo;
                    }
                }
                else
                {
                    printf("Invalid choice get lost without this the stack would get smashed\n");
                    exit(0);
                }
                
            }
        }
        else if(login_choice==2)
        {
            student_lo:
            printf("Logging in as Student Press Y to continue or press N to switch to admin login\n");
            if(scanf("%s",confirm_login_choice)>0)
            {
                if(strlen(confirm_login_choice)==1)
                {
                    if(strcmp(confirm_login_choice,"Y")==0)
                    {
                        student_login();
                        
                    }
                    else if(strcmp(confirm_login_choice,"N")==0)
                    {
                        admin_login();
                    }
                    else
                    {
                        printf("Invalid Login Choice Entered\n");
                        goto student_lo;
                    }
                }
                else
                {
                    printf("Invalid choice get lost without this the stack would get smashed\n");
                    exit(0);
                }
            }

        }
    }
}
// done with login page now go to different login

//admin login page
void admin_login()
{
    int dump;
    int return_value;
    char *admin_username=malloc(sizeof(char)*20);
    char *admin_password=malloc(sizeof(char)*20);
    printf("Admin username: \n");
    return_value=scanf("%s",admin_username);
    if(return_value==EOF)
    {
        printf("Error in entered input\n");
    }
    printf("Admin Password:\n");
    if(counter==0)
    {
        dump=getchar();
    }
    if(admin_username!=NULL)
    {
        getdetails(admin_password);
        decrypt_and_check(admin_username,admin_password);
    }
    free(admin_username);
    free(admin_password);
}

int string_matching(char main_word[],char sub_word[])
{
    int main_length=(int)strlen(main_word);
    int sub_length=(int)strlen(sub_word);
    int i,j,correct=0;
    for(i=0;i<=main_length-sub_length;i++)
    {
        if(correct!=1)
        {
            for(j=0;j<sub_length;j++)
            {
                if(main_word[i+j] != sub_word[j] )
                {   correct=0;
                    break;
                }
                correct=1;
            }
        }
        if(correct==1)
        {
            printf("Password matches\n");
            return 1;
        }
    }
    if(correct==0)
    {
        printf("NO match in pass\n");
        return 0;
    }
    return 0;
}

int check_student_details(char usr[],char pass[])
{
    FILE *fp=fopen(".student_login_details.txt","r");
    if(fp!=NULL)
    {
        
    char temp[100];
    char *user_by_user;
    while(fgets(temp,100,fp))
    {
            //printf("%s\n",temp);
            char temp1[100];
            strcpy(temp1,temp);
            user_by_user = strtok(temp,",");
            
            if(strcmp(usr,user_by_user)==0)
            {
                char *en=malloc(sizeof(char)*100);
                encrypt_pass(pass,en);
                printf("Temp  is %s\n",temp1);
                if(string_matching(temp1,en)==1)
                {
                    //printf("Password matches\n");
                    free(en);
                    return 1;
                }
                free(en);
            }
            
            
    }
    
        if(fclose(fp)!=0)
        {
            printf("Error in closing file\n");
        }
    }
    return 0;

}

void student_login()
{
    int return_val;
    return_val=system("clear");
    char student_username[100];
    char student_password[100];
    printf("Student ID- ");
    return_val=scanf("%s",student_username);
    if(return_val==EOF)
    {
        printf("Invalid input\n");
    }
    printf("Student Pasword:- ");
    if(ctr1==0)
    {
        int temp;
        temp=getchar();
    }
    getdetails(student_password);
    if(check_student_details(student_username,student_password)==1)
    {
        return_val=system("clear");
        printf("                                                                                                                                Welcome %s\n",student_username);
        showOne(3,student_username);
    }

}

FILE *chemptr, *appptr, *fineptr, *ptr2, *ptr3;
int checking;



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
        printf("1.Add\n2.Modify\n3.Delete\n4.Show One\n5.Show All\n6.Go back to previous menu\nEnter your choice\n");
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
        case 6:
            login_granted();
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
        if(checking == 0)
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
        printf("Enter the id of the student\n");
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

