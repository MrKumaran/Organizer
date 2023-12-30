#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//defining output text color
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//defining all variables as global
//so that it can be accessiable by any functions in this program
int namesize[100];
int max;
int temporary;
int number;
int loopitem = 0;
int condition;
int i,j;
char input[30];
char filename[50];
FILE *file;

//declarations of functions
int conditionfn();    //for checking the condition entered by user
void details();		  //for getting required details from user
void size_compare();  //for finding max space required and assign spacefor each name
void format();		  //for formatting names -> first letter is capital
void alphabet_sort(); //for sort the structure in alphabetical order
void menu();		  //for display menu options and getting user input
void cgpa_sort();	  //for sort the structure in cgpa order
void printer();		  //for printing the details in table form in op terminal
void file_printer();  //for writing table form in seperate user named file
void file_function(); //for opening the file with user named name
void proceed();		  //for calling functions whenever needed

//structure to hold students details max 100(Array of structure)
struct student
{
    char name[100];
    int age;
    int year;
    float cgpa;
    int space;
} s[100];

//structure to hold students details temporary while sorting
struct Temporary
{
    char name[100];
    int age;
    int year;
    float cgpa;
    int space;
} temp;

//for getting required details from user
void details()
{
    //reading input from user
    printf("\n\t\tEnter Student Details\n\n");
    for (i=0; i<number; i++)
    {
        printf("Name : ");
        scanf(" %100[^\n]",s[i].name);
        printf("Age  : ");
        scanf("%d",&s[i].age);
        printf("Year : ");
        scanf("%d",&s[i].year);
        printf("CGPA : ");
        scanf("%f",&s[i].cgpa);
    }
}

//for formatting names -> first letter is capital
void format()
{
    //formatting the name read from user
    //making first capital and others small
    for(j=0; j<number; j++)
    {
        for(i=0; s[j].name[i]!='\0'; i++)
        {
            if(i==0)
            {
                if((s[j].name[i]>='a' && s[j].name[i]<='z'))
                    s[j].name[i]=s[j].name[i]-32;
                continue;
            }
            if(s[j].name[i]==' ')
            {
                ++i;
                if(s[j].name[i]>='a' && s[j].name[i]<='z')
                {
                    s[j].name[i]=s[j].name[i]-32;
                    continue;
                }
            }
            else
            {
                if(s[j].name[i]>='A' && s[j].name[i]<='Z')
                    s[j].name[i]=s[j].name[i]+32;
            }
        }
    }
}

//for finding max space required and assign spacefor each name
void size_compare()
{
    //to find the max value required for space(table form)
    for (i=0; i<number; i++)
    {
        namesize[i] = strlen(s[i].name);
    }
    max = namesize[0];
    for (i=0; i<number; i++)
    {
        if(namesize[i] < namesize[i+1] && namesize[i+1]!=0)
        {
            max = namesize[i+1];
        }
    }
    max += 5;
    for(i=0; i<number; i++)
    {
        s[i].space= max - namesize[i];
    }
    max -=4;
}

//for sort the structure in alphabetical order
void alphabet_sort()
{
    //sort in alphabetical order
    for(i=0; i<number; i++)
    {
        for(j=0; j<i; j++)
        {
            if(strcmp(s[i].name,s[j].name)<0)
            {
                strcpy(temp.name,s[j].name);
                temp.age = s[j].age;
                temp.year = s[j].year;
                temp.cgpa = s[j].cgpa;
                strcpy(s[j].name,s[i].name);
                s[j].age = s[i].age;
                s[j].year = s[i].year;
                s[j].cgpa = s[i].cgpa;
                strcpy(s[i].name,temp.name);
                s[i].age = temp.age;
                s[i].year = temp.year;
                s[i].cgpa = temp.cgpa;
                temp.space=s[i].space;
                s[i].space=s[j].space;
                s[j].space=temp.space;
            }
        }
    }
}

//for checking the condition entered by user
int conditionfn()
{
    //checks the input with options and return int value
    if(strcmp(input,"alphaop")==0)
    {
        return 0;
    }
    else if(strcmp(input,"cgpaop")==0)
    {
        return 1;
    }
    else if(strcmp(input,"alphasave")==0)
    {
        return 2;
    }
    else if(strcmp(input,"cgpasave")==0)
    {
        return 3;
    }
    else if(strcmp(input,"alphaop_save")==0)
    {
        return 4;
    }
    else if(strcmp(input,"cgpaop_save")==0)
    {
        return 5;
    }
    else if(strcmp(input,"alpha_cgpa_save")==0)
    {
        return 6;
    }
    else if(strcmp(input,"alpha_cgpa_op_save")==0)
    {
        return 7;
    }
    else if(strcmp(input,"exit")==0)
    {
        return 8;
    }
    else
    {
        return -1;
    }
}

//for display menu options and getting user input
void menu()
{
    //displays the options available to user and gets the input from user and call conditionfn function
    while(loopitem==0)
    {
        printf(ANSI_COLOR_CYAN "\t\nEnter What to do with this Information\n\n");
        printf(ANSI_COLOR_YELLOW "AlphaOP            = print the organized form in alphabet of name in op terminal\nCGPAOP             = print the organized form in cgpa order in op terminal\nAlphasave          = saves the organized form of Alphabets of Name in user named file\nCGPAsave           = save the organized form in cgpa order in user named file\nAlphaop_save       = op plus save\nCGPAop_save        = op plus save\nAlpha_cgpa_save    = Both alphasave and Cgpa_save\nAlpha_cgpa_op_save = Both Alphaop_save and Cgpaop_save\nExit               = Exits the program!\n\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_BLUE "Your input:" ANSI_COLOR_GREEN);
        scanf("%s",&input);
        printf(ANSI_COLOR_RESET);
        strcpy(input,strlwr(input));
        condition = conditionfn(input);
        if(condition >=0)
        {
            proceed();
            break;
        }
        else
        {
            printf(ANSI_COLOR_RED "Enter valid Input!\a\a\n" ANSI_COLOR_RESET);
        }
    }
}

//for printing the details in table form in op terminal
void printer()
{
    //used to display in op terminal
    printf("Name");
    for(i=0; i<=max; i++)
    {
        printf(" ");
    }
    printf("| Age");
    for(i=0; i<max-2; i++)
    {
        printf(" ");
    }
    printf("| Year");
    for(i=0; i<max-4; i++)
    {
        printf(" ");
    }
    printf("| CGPA\n");
    for(i=0; i<number; i++)
    {
        printf("%s",s[i].name);
        for(j=0; j<=s[i].space; j++)
        {
            printf(" ");
        }
        printf("|");
        printf(" %d",s[i].age);
        for(j=0; j<max-1; j++)
        {
            printf(" ");
        }
        printf("|");
        printf(" %d",s[i].year);
        for(j=0; j<max-1; j++)
        {
            printf(" ");
        }
        printf("|");
        printf(" %.1f\n",s[i].cgpa);
    }
}

//for writing table form in seperate user named file
void file_printer()
{
    //used to store in file in table form
    fprintf(file,"Name");
    for(i=0; i<=max; i++)
    {
        fprintf(file," ");
    }
    fprintf(file,"| Age");
    for(i=0; i<max-2; i++)
    {
        fprintf(file," ");
    }
    fprintf(file,"| Year");
    for(i=0; i<max-4; i++)
    {
        fprintf(file," ");
    }
    fprintf(file,"| CGPA\n");
    for(i=0; i<number; i++)
    {
        fprintf(file,"%s",s[i].name);
        for(j=0; j<=s[i].space; j++)
        {
            fprintf(file," ");
        }
        fprintf(file,"|");
        fprintf(file," %d",s[i].age);
        for(j=0; j<max-1; j++)
        {
            fprintf(file," ");
        }
        fprintf(file,"|");
        fprintf(file," %d",s[i].year);
        for(j=0; j<max-1; j++)
        {
            fprintf(file," ");
        }
        fprintf(file,"|");
        fprintf(file," %.1f\n",s[i].cgpa);
    }
}

//for sort the structure in cgpa order
void cgpa_sort()
{
    //compare cgpa and sort the structure based on cgpa
    for(i=0; i<number; i++)
    {
        for(j=0; j<i; j++)
        {
            if(s[i].cgpa>s[j].cgpa)
            {
                strcpy(temp.name,s[j].name);
                temp.age = s[j].age;
                temp.year = s[j].year;
                temp.cgpa = s[j].cgpa;
                strcpy(s[j].name,s[i].name);
                s[j].age = s[i].age;
                s[j].year = s[i].year;
                s[j].cgpa = s[i].cgpa;
                strcpy(s[i].name,temp.name);
                s[i].age = temp.age;
                s[i].year = temp.year;
                s[i].cgpa = temp.cgpa;
                temp.space=s[i].space;
                s[i].space=s[j].space;
                s[j].space=temp.space;
            }
        }
    }
}

//for opening the file with user named name
void file_function()
{
    //opens a file to store data
    printf("\n");
    printf("File name: ");
    scanf("%s",&filename);
    file = fopen(filename,"w");
    if(file==NULL)
    {
        printf("file Open error");
    }
    else
    {
        file_printer();
    }
    printf("\n\n\n");
    printf("Information saved in file : %s\n\n",filename);
    system("pause");
    fclose(file);
}

//for calling functions whenever needed
void proceed()
{
    //based on the condition value return from conditionfn(function) calls the corresponding function
    if(condition == 0)
    {
        printer();
        printf("\n");
        system("pause");
        menu();
    }
    else if(condition == 1)
    {
        cgpa_sort();
        printer();
        printf("\n");
        alphabet_sort();
        system("pause");
        menu();
    }
    else if(condition == 2)
    {
        file_function();
        printf("\n");
        system("pause");
        menu();
    }
    else if(condition == 3)
    {
        cgpa_sort();
        file_function();
        printf("\n");
        alphabet_sort();
        system("pause");
        menu();
    }
    else if(condition == 4)
    {
        printer();
        file_function();
        printf("\n");
        system("pause");
        menu();
    }
    else if(condition == 5)
    {
        cgpa_sort();
        printer();
        file_function();
        printf("\n");
        alphabet_sort();
        system("pause");
        menu();
    }
    else if(condition == 6)
    {
        printf("\n\tAlphabet Order\n\n");
        file_function();
        printf("\n\tCGPA Order\n\n");
        cgpa_sort();
        file_function();
        printf("\n");
        alphabet_sort();
        system("pause");
        menu();
    }
    else if(condition == 7)
    {
        printf("\n\tAlphabet Order\n\n");
        printer();
        file_function();
        printf("\n\tCGPA Order\n\n");
        cgpa_sort();
        printer();
        file_function();
        printf("\n");
        alphabet_sort();
        system("pause");
        menu();
    }
    else
    {
        printf(ANSI_COLOR_MAGENTA "\n\nProgram exiting...Tata bye bye!\n\n" ANSI_COLOR_RESET);
        system("pause");
    }
}

//std main function
int main()
{
    printf(ANSI_COLOR_MAGENTA "Enter number of Students(Max 100): " ANSI_COLOR_RESET);
    scanf("%d",&number);
    details();
    format();
    size_compare();
    alphabet_sort();
    printf("\n\n");
    menu();
    //proceed();
    return 0;
}