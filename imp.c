#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int return_val;
int main()
{
    FILE *fp=fopen(".admin.txt","a");
    char username[20]="admin";
    char password[20]="admin";
    int len_username=(int) strlen(username);
    int len_password=(int)strlen(password);
    int counter=0;
    int no_of_odd,no_of_even;
    for(counter=0;counter<len_username;counter++)
    {
        char temp=username[counter];
        if(counter%2==0)
        {
            no_of_odd++;
            int no=(int)temp + (no_of_odd)*3;
            int chck_error=fputc(no,fp);
        }
        else
        {
            no_of_even++;
            int no=(int)temp + (no_of_even)*4;
            int chck_error=fputc(no,fp);
        }
        
    }
    fputc(10,fp);
    no_of_even=0;
    no_of_odd=0;
    for(counter=0;counter<len_password;counter++)
    {
        char temp=password[counter];
        if(counter%2==0)
        {
            no_of_odd++;
            int no=(int)temp - (no_of_odd)*3;
            fputc((char)no,fp);
        }
        else
        {
            no_of_even++;
            int no=(int)temp - (no_of_even)*4;
            fputc((char)no,fp);
        }
        
    }
    if(fclose(fp))
    {
        printf("File not closed\n");
    }
    FILE *fp1= fopen(".admin.txt","r");
    if(fp1!=NULL)
    {
        char decoded[100];
        char decopass[100];
        char a=fgetc(fp1);
        int counter=0;
        int no_of_odd=0,no_of_even=0;
        while(a!='\n')
        {
            if(counter%2==0)
            {
                no_of_odd++;
                char temp=a;
                int no=(int)temp - (no_of_odd)*3;
                decoded[counter]=(char)no;
            }
            else
            {
                no_of_even++;
                char temp=a;
                int no=(int)temp - (no_of_even)*4;
                decoded[counter]=(char)no;
            }
            counter++;
            a=fgetc(fp1);
        }
        //printf("Decoded username is %s \n",decoded);
        no_of_odd=0,no_of_even=0;
        char b=fgetc(fp1);
        counter=0;
        while((int)b!=EOF)
        {
            if(counter%2==0)
            {
                no_of_odd++;
                char temp=b;
                int no=(int)temp + (no_of_odd)*3;
                decopass[counter]=(char)no;
                //printf("b is %c and decoded is %c\n",b,(char)no);
            }
            else
            {
                no_of_even++;
                char temp=b;
                int no=(int)temp + (no_of_even)*4;
                decopass[counter]=(char)no;
                //printf("b is %c and decoded is %c\n",b,(char)no);
            }
            counter++;
            b=fgetc(fp1);
        }
        //printf("Decoded password is %s \n",decopass);
    }
    fclose(fp1);
    
}
