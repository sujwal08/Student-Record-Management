#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    int age;
    int rollno;
    float cgpa;
} Student;

void createRecord();
void listRecord();
void addRecord();
void deleteRecord();
void clearInputBuffer();
int rollNumberExists(int rollno);

int main()
{
    int choice;

    do
    {
        printf("1. Create record\n2. List records\n3. Add another record\n4. Delete record\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
        case 1:
            createRecord();
            break;
        case 2:
            listRecord();
            break;
        case 3:
            addRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void createRecord()
{
    FILE *fp;
    Student s;
    int ch = 1;

    fp = fopen("temp.txt", "w");
    if (fp == NULL)
    {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    printf("Enter student details:\n");
    while (ch == 1)
    {
        printf("Name: ");
        scanf("%s", s.name);
        do
        {
            printf("Age: ");
            scanf("%d", &s.age);
            if (s.age < 0 || s.age > 100)
            {
                printf("Invalid age.\n");
            }

        } while (s.age < 0);

        do
        {
            printf("Roll Number: ");
            scanf("%d", &s.rollno);
            if (rollNumberExists(s.rollno))
            {
                printf("Roll number already exists. Please enter a unique roll number.\n");
            }
        } while (rollNumberExists(s.rollno));

        do
        {
            printf("CGPA: ");
            scanf("%f", &s.cgpa);
            if (s.cgpa < 0 || s.cgpa > 4)
            {
                printf("Invalid CGPA. CGPA should be between 0 and 4. \n");
            }
        } while (s.cgpa < 0 || s.cgpa > 4);

        fprintf(fp, "%s %d %d %.2f\n", s.name, s.age, s.rollno, s.cgpa);

        printf("Press 1 to add another record or 0 to exit: ");
        if (scanf("%d", &ch) != 1)
        {
            printf("Invalid input. Exiting record creation.\n");
            clearInputBuffer();
            break;
        }
    }

    fclose(fp);
}

void listRecord()
{
    FILE *fp;
    Student s;

    fp = fopen("temp.txt", "r");
    if (fp == NULL)
    {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    printf("Name\tAge\tRoll Number\tCGPA\n");
    printf("-----------------------------------------\n");
    while (fscanf(fp, "%s %d %d %f", s.name, &s.age, &s.rollno, &s.cgpa) != EOF)
    {
        printf("%s\t%d\t%d\t%.2f\n", s.name, s.age, s.rollno, s.cgpa);
    }

    fclose(fp);
}

void addRecord()
{
    FILE *fp;
    Student s;
    int ch = 1;

    fp = fopen("temp.txt", "a");
    if (fp == NULL)
    {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    printf("Enter student details:\n");
    while (ch == 1)
    {
        printf("Name: ");
        scanf("%s", s.name);
        printf("Age: ");
        scanf("%d", &s.age);

        do
        {
            printf("Roll Number: ");
            scanf("%d", &s.rollno);
            if (rollNumberExists(s.rollno))
            {
                printf("Roll number already exists. Please enter a unique roll number.\n");
            }
        } while (rollNumberExists(s.rollno));

        printf("CGPA: ");
        scanf("%f", &s.cgpa);

        fprintf(fp, "%s %d %d %.2f\n", s.name, s.age, s.rollno, s.cgpa);

        printf("Press 1 to add another record or 0 to exit: ");
        if (scanf("%d", &ch) != 1)
        {
            printf("Invalid input. Exiting record addition.\n");
            clearInputBuffer();
            break;
        }
    }

    fclose(fp);
}

void deleteRecord()
{
    FILE *fp, *tempFile;
    Student s;
    int rollno, found = 0;

    printf("Enter the roll number of the student to delete:\n ");
    scanf("%d", &rollno);

    fp = fopen("temp.txt", "r");
    if (fp == NULL)
    {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s %d %d %f", s.name, &s.age, &s.rollno, &s.cgpa) != EOF)
    {
        if (s.rollno == rollno)
        {
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%s %d %d %.2f\n", s.name, s.age, s.rollno, s.cgpa);
        }
    }

    fclose(fp);
    fclose(tempFile);

    if (found)
    {
        remove("temp.txt");
        rename("temp.txt", "temp.txt");
        printf("Record deleted successfully.\n");
    }
    else
    {
        printf("Student with roll number %d not found.\n", rollno);
    }
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int rollNumberExists(int rollno)
{
    FILE *fp;
    Student s;
    int exists = 0;

    fp = fopen("temp.txt", "r");
    if (fp == NULL)
    {
        return 0; // File does not exist, so roll number cannnot exist either
    }
    while (fscanf(fp, "%s %d %d %f", s.name, &s.age, &s.rollno, &s.cgpa) != EOF)
    {
        if (s.rollno == rollno)
        {
            exists = 1;
            break;
        }
    }
    fclose(fp);
    return exists;
}
