#include "header.h"

FILE *chemptr, *appptr, *fineptr, *ptr2, *ptr3;


void main()
{
    delete(1,"21");
}

int showOne(int main_choice, char *id)
{
    char *id_find;
    int i;
    const char x = ',';
    if(main_choice == 1)//Apparatus
    {
        appptr = fopen("apparatus.txt", "r");
        if (!appptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1, flag = 1;
        int line_no = 0;
        while(fgets(line, 1024, appptr))
        {
            strcpy(line_cpy, line);
            id_find = strtok(line, ", ");
            cmp = strcmp(id_find,id);
            if(cmp == 0)
            {
                printf("ID,Name,Quantity,Cost per unit,Total Cost\n");
                printf("%s\n",line_cpy);
                flag = 1;
                fclose(appptr);
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
            fclose(appptr);
            return 0;
        }
        
       
    }
    else if(main_choice == 2)//Chemicals
    {
        chemptr = fopen("chemicals.txt", "r");
        if (!chemptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1, flag = 1;
        int line_no = 0;
        while(fgets(line, 1024, chemptr))
        {
            strcpy(line_cpy, line);
            id_find = strtok(line, ", ");
            cmp = strcmp(id_find, id);
            if(cmp == 0)
            {
                printf("ID, Name, Quantity, Cost per unit, Total Cost\n");
                printf("%s\n", line_cpy);
                flag = 1;
                return 1;
            }
            else
            {
                flag = 0;
            }
            
            //printf("%s\n", id_find);
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
        fineptr = fopen("fines.txt", "r");
        if (!fineptr)
        {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
        }
        //char ch = fgetc(appptr);
        char line[1024];
        char line_cpy[1024];//To make a copy cause line gets modified when strtok is done
        int cmp = -1, flag = 1;
        int line_no = 0;
        while(fgets(line, 1024, fineptr))
        {
            strcpy(line_cpy, line);
            id_find = strtok(line, ", ");
            cmp = strcmp(id_find, id);
            if(cmp == 0)
            {
                printf("ID, Name, Quantity, Cost per unit, Total Cost\n");
                printf("%s\n", line_cpy);
                flag = 1;
                return 1;
            }
            else
            {
                flag = 0;
            }
            
            //printf("%s\n", id_find);
        }
        if(!flag)
        {
            printf("Not found\n");
            return 0;
        }
        fclose(appptr);
    }
}


void delete(int main_choice, char *id)
{
    int x = -1;
    int lines = 0,i;
    char line[1024];
    if(main_choice == 1)//Apparatus
    {
        ptr2 = fopen("apparatus.txt", "r");
        ptr3 = fopen("apparatus2.txt", "a+");

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

        x = showOne(main_choice, id);
        printf("%d\n",x);
        if(x != 0)//it exists
        {
            if(x == 1)
            {

            }
            for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr,)
            }
            fgets(line,1024,ptr2);
            printf("%s\n",line);
            fputs("\n",  ptr2);
        }

        rewind(ptr2);
        for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr, )
                fputs(line, ptr3);
            }

        fgets(line, 1024, ptr2);

        for(i = 1, x = 1; !feof(ptr2) ;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr, )
                fputs(line, ptr3);
            }

        fclose(ptr2);
        fclose(ptr3);
        system("rm apparatus.txt");
        system("mv apparatus2.txt apparatus.txt");
       
    }
    else if(main_choice == 2)//CHEMICALS
    {
        ptr2 = fopen("chemicals.txt", "r");
        ptr3 = fopen("chemicals2.txt", "a+");

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

        x = showOne(main_choice, id);
        
        if(x != 0)//it exists
        {
            for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr,)
            }
            fgets(line, 1024, ptr2);
            printf("%s", line);
            fputs("\n",  ptr2);
            // fseek(appptr, x*sizeof(struct apparatus), SEEK_SET);
            // fgets(line, 1024, appptr);
        }

        rewind(ptr2);
        for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr, )
                fputs(line, ptr3);
            }

        fgets(line, 1024, ptr2);

        for(i = x = 1; !feof(ptr2) ;i++)
            {
                fgets(line, 1024, ptr2);//fseek(appptr, )
                fputs(line, ptr3);
            }

        fclose(ptr2);
        fclose(ptr3);
        system("rm chemicals.txt");
        system("mv chemicals2.txt chemicals.txt");
    }
    else
    {
        ptr2 = fopen("fines.txt", "r");
        ptr3 = fopen("fines2.txt", "a+");

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

        x = showOne(main_choice, id);

        if(x != 0)//it exists
        {
            for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);
            }
            fgets(line, 1024, ptr2);
            printf("%s", line);
            fputs("\n",  ptr2);
        }

        rewind(ptr2);
        for(i = 0;i < x-1;i++)
            {
                fgets(line, 1024, ptr2);
                fputs(line, ptr3);
            }

        fgets(line, 1024, ptr2);

        for(i = x = 1; !feof(ptr2) ;i++)
            {
                fgets(line, 1024, ptr2);
                fputs(line, ptr3);
            }

        fclose(ptr2);
        fclose(ptr3);
        system("rm fines.txt");
        system("mv fines2.txt fines.txt");
       
    }
}