#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------- STRUCTURE DEFINITION -----------------------------
struct Student {
    char name[50];
    char Class[10];
    int roll_no;
    float physics, computer_science, maths, nepali, english;
    float total, average, percentage;
    char grade[5];
    char result[10];
};

// ----------------------------- FUNCTION PROTOTYPES -----------------------------
void adminMode();
void teacherMode();
void studentMode();
void login();
void deleteRecord();

// ----------------------------- MAIN FUNCTION -----------------------------
    int main() {
        login();
        return 0;
    }

// ----------------------------- LOGIN FUNCTION -----------------------------
void login() {
    char username[20], password[20];
    int choice;

    printf("===== WELCOME TO MARKSHEET MANAGEMENT SYSTEM =====\n");
    printf("Login as:\n1. Admin\n2. Teacher\n3. Student\nEnter choice: ");
    scanf("%d", &choice);

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (choice == 1 && strcmp(username, "admin1") == 0 && strcmp(password, "pass789") == 0) {
        adminMode();
    } else if (choice == 2 && strcmp(username, "teacher1") == 0 && strcmp(password, "pass456") == 0) {
        teacherMode();
    } else if (choice == 3 && strcmp(username, "student1") == 0 && strcmp(password, "pass123") == 0) {
        studentMode();
    } else {
        printf("Invalid credentials.\n");
    }
}

// ----------------------------- ADMIN MODE FUNCTION -----------------------------
void adminMode() {
    FILE *file = fopen("ledger.dat", "rb");
    if (file == NULL) {
        printf("No ledger found.\n");
        return;
    }

    struct Student s;
    printf("\n==================== CLASS LEDGER ====================\n");
    printf("Name                 Class    Roll     Physics  CS    Maths  Nepali English Total  Percent Grade\n");
    printf("-----------------------------------------------------------------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, file)) {
        printf("%-20s %-8s %-8d %-7.1f %-5.1f %-6.1f %-6.1f %-7.1f %-7.1f %-7.1f %-5s\n",
            s.name, s.Class, s.roll_no, s.physics, s.computer_science, s.maths, s.nepali,
            s.english, s.total, s.percentage, s.grade);
    }

    fclose(file);

    int del;
    printf("\nDo you want to delete a record? (1=Yes, 0=No): ");
    scanf("%d", &del);
    if (del == 1) {
        deleteRecord();
    }
}

// ----------------------------- TEACHER MODE FUNCTION -----------------------------
void teacherMode() {
    FILE *file = fopen("ledger.dat", "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int n , i;
    printf("Enter number of students to add: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        struct Student s;

        printf("\n--- Entering data for student %d ---\n", i + 1);
        printf("Enter student name: ");
        scanf(" %[^\n]", s.name);

        printf("Enter class: ");
        scanf("%s", s.Class);

        printf("Enter roll number: ");
        scanf("%d", &s.roll_no);


        printf("Enter marks for Physics: ");
        scanf("%f", &s.physics);

        printf("Enter marks for Computer Science: ");
        scanf("%f", &s.computer_science);

        printf("Enter marks for Maths: ");
        scanf("%f", &s.maths);

        printf("Enter marks for Nepali: ");
        scanf("%f", &s.nepali);

        printf("Enter marks for English: ");
        scanf("%f", &s.english);

        s.total = s.physics + s.computer_science + s.maths + s.nepali + s.english;
        s.average = s.total / 5.0;
        s.percentage = s.average;

        if (s.percentage >= 90) strcpy(s.grade, "A+");
        else if (s.percentage >= 80)
            strcpy(s.grade, "A");

        else if (s.percentage >= 70)
            strcpy(s.grade, "B+");

        else if (s.percentage >= 60)
            strcpy(s.grade, "B");

        else if (s.percentage >= 50)
            strcpy(s.grade, "C+");

        else if (s.percentage >= 40)
            strcpy(s.grade, "C");

        else strcpy(s.grade, "F");

        strcpy(s.result, (s.percentage >= 40) ? "Pass" : "Fail");

        fwrite(&s, sizeof(struct Student), 1, file);

        printf("\n\n\t\t\tRUDRAMATI PATHSHALA\n");
        printf("\t\t\t   MARKSHEET\n");
        printf("------------------------------------------------------------\n");
        printf(" Name      : %s\n", s.name);
        printf(" Class     : %s\n", s.Class);
        printf(" Roll No.  : %d\n", s.roll_no);
        printf("------------------------------------------------------------\n");
        printf(" Subject\t\t\t\tMarks\n");
        printf("------------------------------------------------------------\n");
        printf(" Physics\t\t\t\t%.2f\n", s.physics);
        printf(" Computer Science\t\t\t%.2f\n", s.computer_science);
        printf(" Maths\t\t\t\t\t%.2f\n", s.maths);
        printf(" Nepali\t\t\t\t\t%.2f\n", s.nepali);
        printf(" English\t\t\t\t%.2f\n", s.english);
        printf("------------------------------------------------------------\n");
        printf(" Total\t\t\t\t\t%.2f\n", s.total);
        printf(" Average\t\t\t\t%.2f\n", s.average);
        printf(" Percentage\t\t\t\t%.2f%%\n", s.percentage);
        printf(" Grade\t\t\t\t\t%s\n", s.grade);
    }

    fclose(file);
}




// ----------------------------- STUDENT MODE -----------------------------
void studentMode() {
    FILE *file = fopen("ledger.dat", "rb");
    if (file == NULL) {
        printf("No ledger found.\n");
        return;
    }

    struct Student s;
    char name[50], Class[10];
    int roll, found = 0;

    printf("Enter student name: ");
    scanf(" %[^\n]", name);
    printf("Enter class: ");
    scanf("%s", Class);
    printf("Enter roll number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (strcmp(s.name, name) == 0 && strcmp(s.Class, Class) == 0 && s.roll_no == roll) {
            found = 1;
            printf("\n\n\t\t\tRUDRAMATI PATHSHALA\n");
            printf("\t\t\t   MARKSHEET\n");
            printf("------------------------------------------------------------\n");
            printf(" Name      : %s\n", s.name);
            printf(" Class     : %s\n", s.Class);
            printf(" Roll No.  : %d\n", s.roll_no);
            printf("------------------------------------------------------------\n");
            printf(" Subject\t\t\t\tMarks\n");
            printf("------------------------------------------------------------\n");
            printf(" Physics\t\t\t\t%.2f\n", s.physics);
            printf(" Computer Science\t\t\t%.2f\n", s.computer_science);
            printf(" Maths\t\t\t\t\t%.2f\n", s.maths);
            printf(" Nepali\t\t\t\t\t%.2f\n", s.nepali);
            printf(" English\t\t\t\t%.2f\n", s.english);
            printf("------------------------------------------------------------\n");
            printf(" Total\t\t\t\t\t%.2f\n", s.total);
            printf(" Average\t\t\t\t%.2f\n", s.average);
            printf(" Percentage\t\t\t\t%.2f%%\n", s.percentage);
            printf(" Grade\t\t\t\t\t%s\n", s.grade);
            break;
        }
    }

    if (!found)
        printf("Student record not found.\n");

    fclose(file);
}

// ----------------------------- DELETE RECORD -----------------------------
void deleteRecord() {
    FILE *file = fopen("ledger.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (file == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char name[50];
    int roll, deleted = 0;
    struct Student s;

    printf("Enter name of student to delete: ");
    scanf(" %[^\n]", name);
    printf("Enter roll number: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, file)) {
        if (!(strcmp(s.name, name) == 0 && s.roll_no == roll)) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            deleted = 1;
        }
    }


    //----------------file close------------

    fclose(file);
    fclose(temp);

    remove("ledger.dat");
    rename("temp.dat", "ledger.dat");

    if (deleted)
        printf("Record deleted successfully.\n");
    else
        printf("Record not found.\n");
}

