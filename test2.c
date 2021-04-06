#include <stdio.h> 
#include <string.h> 
#include "header.h"
 
FILE *chemptr,*appptr,*fineptr;

    struct apparatus *apps;
    struct chemicals *chem;
    struct student *stu;

void main()
{
    int x = -1;
    x = showOne(3,"name");
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