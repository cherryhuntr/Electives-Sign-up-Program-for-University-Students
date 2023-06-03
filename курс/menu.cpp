#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include "storage.h"
#include "menu.h"
#include <ctype.h>


int num_students = 0;

// ������� main()
int main() {
    setlocale(LC_ALL, "Rus");


    // ���������� ������� ��������� ������� �� �����
    FILE* file;
    if (fopen_s(&file, "students.txt", "r+") == 0)
    {
        // �������� ���������� ������� � �����
        fseek(file, 0L, SEEK_END);
        long file_size = ftell(file);
        num_students = file_size / sizeof(struct Student);
        rewind(file);
        struct Student* student = (struct Student*)malloc(num_students * sizeof(struct Student));
        // ��������� ������ �� ����� � ������ ��������
        fread(student, sizeof(struct Student), num_students, file);

        fclose(file);

    }
    else {
        printf("������ �������� �����!\n");
        exit(1);
    }



    print_main_menu();

    return 0;
}



void print_main_menu() {
    int choice;
    printf("��� �� ������ ����� � ���������?\n");
    printf("1. ����� ��� �������������\n");
    printf("2. ����� ��� �������\n");
    printf("3. �����\n");
    printf("��� �����: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("������: ������ ������������ �����\n");
        print_main_menu();
    }
    else {

        switch (choice) {
        case 1:
            login_admin();
            break;
        case 2:
            login_student();
            break;
        case 3:
            // ����� �� ���������
            printf("�� ��������!\n");
            exit(0);
        }
    }
}



void print_admin_menu() {
    int choice;
    printf("--------------------------------------------------------���� ��������������----------------------------------------------------------\n");
    printf("1. ����� ���������� �������� ��������\n");
    printf("2. ���������� ��� ������\n");
    printf("3. ����� ���������\n");
    printf("4. ���������� ��������� �� �������� �������� �����\n");
    printf("5. �����\n");
    printf("6. �����\n");
    printf("��� �����: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 6) {
        printf("\n������: ������ ������������ �����\n");
        print_admin_menu();
    }

    switch (choice) {
    case 1:
        
        int id;
        printf("������� id ��������: ");
        scanf_s("%d", &id);
        print_edit_menu(id);
        
        break;
    case 2:
        print_all_students();
        break;
    case 3:
        search();
        break;
    case 4:
        sortByGPA();
        break;
    case 5:
        print_main_menu();
        break;
    case 6:
        
        printf("\n�� ��������!\n");
        exit(0);
    }
}

void print_student_menu(int k) {
    int id = k;
    int choice;
    printf("----------------------------------------------------------���� ��������------------------------------------------------------------\n");
    printf("1. ������������� ������ �������\n");
    printf("2. ����� ���������\n");
    printf("3. ���������� ��������� �� �������� �������� �����\n");
    printf("4. �����\n");
    printf("5. �����\n");
    printf("��� �����: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 5) {
        printf("\n������: ������ ������������ �����\n");
        print_student_menu(id);
    }

    switch (choice) {
    case 1:
        print_edit_menu(id);
        break;
    case 2:
        search();
        break;
    case 3:
        sortByGPA();
        break;
    case 4:
        print_main_menu();
        break;

    case 5:
        printf("\n�� ��������!\n");
        exit(0);
    }
}

void search() {


    printf("1. �� �������\n");
    printf("2. �� ������\n");
    printf("3. �� ������ ������\n");
    printf("4. �����\n");
    printf("5. �����\n");
    printf("��� �����: ");
    int choice;
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 5) {
        printf("\n������: ������ ������������ �����\n");
        search();
    }

    switch (choice) {
    case 1:
        char surname[20];
        printf("������� ������� �������� ��������: ");
        scanf_s("%s", surname, sizeof(surname));
        searchStudentBySurname(surname);
        break;
    case 2:
        char address[20];
        printf("������� ����� �������� ��������: ");
        scanf_s("%s", address, sizeof(address));
        searchStudentByAddress(address);
        break;
    case 3:
        int group;
        printf("������� ����� ������ �������� ��������: ");
        scanf_s("%d", &group);
        searchStudentByGroup(group);
        break;
    case 4:
        print_main_menu();
        break;

    case 5:
        printf("\n�� ��������!\n");
        exit(0);
    }
}

void print_edit_menu(int k) {   
    struct Student student;
    int id = k;
    FILE* file;
    if (fopen_s(&file, "records.txt", "r") == 0) {
        fread(&student, sizeof(struct Student), 1, file);
        fclose(file);

       
                printf("1. ���������� ������\n");
                printf("2. �������� ������\n");
                printf("3. �������������� ������\n");
                printf("4. �����\n");
                printf("5. �����\n");
                printf("��� �����: ");
                int choice;
                scanf_s("%d", &choice);

                if (choice < 1 || choice > 5) {
                    printf("\n������: ������ ������������ �����\n");
                    print_edit_menu(id);
                }

                switch (choice) {
                case 1:
                    addStudentApplication(id);
                    break;
                case 2:
                    deleteStudentRecord(id);
                    break;
                case 3:
                    editStudentRecord(id);
                    break;

                case 4:
                    print_main_menu();
                    break;
                case 5:
                    // ����� �� ���������
                    printf("\n�� ��������!\n");
                    exit(0);
                }
      
      
    }
 
   
}



void sortByGPA()
{
    FILE* file;
    struct Student students[100];
    int count = 0;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        struct Student student;

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            students[count] = student;
            count++;
        }

        // ���������� �� �������� �����
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (students[j].gpa < students[j + 1].gpa) {
                    struct Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        printf("��������, ��������������� �� �������� �����:\n");
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-5s | %-10s |\n",
            "ID", "�������", "���", "��������", "������", "���� ��������", "�����������", "������� ����");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < count; i++) {
            struct Student student = students[i];

            char gpaString[10];
            sprintf_s(gpaString, "%.2f", student.gpa);

            printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%02d     | ",
                student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                student.group_number, student.birthday.day, student.birthday.month, student.birthday.year);

            if (student.subjects.math == 1)
                printf("���������� ");
            if (student.subjects.physics == 1)
                printf("������ ");
            if (student.subjects.programming == 1)
                printf("���������������� ");
            if (student.subjects.english == 1)
                printf("���������� ");
            if (student.subjects.database == 1)
                printf("���� ������");

            printf(" | %10s |\n", gpaString);
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        fclose(file);
    }
    else {
        printf("�� ������� ������� ����.\n");
    }
    print_main_menu();
}



void searchStudentBySurname(const char* surname)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("���������� ������ �� ������� '%s':\n", surname);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-10s |\n",
            "ID", "�������", "���", "��������", "������", "���� ��������", "�����", "�����������");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (strcmp(student.full_name.surname, surname) == 0) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("���������� ");
                if (student.subjects.physics == 1)
                    printf("������ ");
                if (student.subjects.programming == 1)
                    printf("���������������� ");
                if (student.subjects.english == 1)
                    printf("���������� ");
                if (student.subjects.database == 1)
                    printf("���� ������");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("������� � �������� '%s' �� ������.\n", surname);
        }

        fclose(file);
    }
    else {
        printf("�� ������� ������� ����.\n");
    }
    search();
}

void searchStudentByAddress(const char* surname)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("���������� ������ �� ������ '%s':\n", surname);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-5s |\n",
            "ID", "�������", "���", "��������", "������", "���� ��������", "�����", "�����������");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (strcmp(student.address, surname) == 0) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("���������� ");
                if (student.subjects.physics == 1)
                    printf("������ ");
                if (student.subjects.programming == 1)
                    printf("���������������� ");
                if (student.subjects.english == 1)
                    printf("���������� ");
                if (student.subjects.database == 1)
                    printf("���� ������");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("������� �� ������ '%s' �� ������.\n", surname);
        }

        fclose(file);
    }
    else {
        printf("�� ������� ������� ����.\n");
    }
    search();
}

void searchStudentByGroup(int groupNumber)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("���������� ������ �� ������ ������ '%d':\n", groupNumber);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-5s |\n",
            "ID", "�������", "���", "��������", "������", "���� ��������", "�����", "�����������");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (student.group_number == groupNumber) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("���������� ");
                if (student.subjects.physics == 1)
                    printf("������ ");
                if (student.subjects.programming == 1)
                    printf("���������������� ");
                if (student.subjects.english == 1)
                    printf("���������� ");
                if (student.subjects.database == 1)
                    printf("���� ������");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("�������� � ������ '%d' �� �������.\n", groupNumber);
        }

        fclose(file);
    }
    else {
        printf("�� ������� ������� ����.\n");
    }
    search();
}




void addStudentApplication(int k)
{
    setlocale(LC_ALL, "Rus");
    struct Student student;
    int id = k;

    printf("������� �������: ");
    scanf_s("%s", student.full_name.surname, sizeof(student.full_name.surname));

    printf("������� ���: ");
    scanf_s("%s", student.full_name.name, sizeof(student.full_name.name));

    printf("������� ��������: ");
    scanf_s("%s", student.full_name.patronymic, sizeof(student.full_name.patronymic));

    printf("������� ����� ������: ");
    scanf_s("%d", &student.group_number, sizeof(student.group_number));

    student.id = id;

    printf("������� ���� �������� (���� ����� ���): ");
    scanf_s("%d %d %d", &student.birthday.day, &student.birthday.month, &student.birthday.year);

    printf("������� �����: ");
    scanf_s("%s", student.address, sizeof(student.address));

    printf("������� ������� ���� ������������: ");
    scanf_s("%f", &student.gpa, sizeof(student.gpa));

    printf("�������� �������������� �������:\n");
    printf("1. ����������\n");
    printf("2. ������\n");
    printf("3. ����������������\n");
    printf("4. ����������\n");
    printf("5. ���� ������\n");
    printf("��� �����: ");
    int choice;
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
        student.subjects.math = 1;
        break;
    case 2:
        student.subjects.physics = 1;
        break;
    case 3:
        student.subjects.programming = 1;
        break;
    case 4:
        student.subjects.english = 1;
        break;
    case 5:
        student.subjects.database = 1;
        break;
    default:
        printf("������������ �����.\n");
        return;
    }

    printf("������� ���� ������ �� ������� (���� ����� ���): ");
    scanf_s("%2d %2d %4d", &student.record.day, &student.record.month, &student.record.year);

    FILE* file;
    if (fopen_s(&file, "records.txt", "ab") == 0) {
        fwrite(&student, sizeof(struct Student), 1, file);
        fclose(file);

        printf("��������� ������� ���������.\n");
        print_edit_menu(id);
    }
    else {
        printf("�� ������� ������� ����.\n");
    }

    return;
}

void print_all_students()
{
    setlocale(LC_ALL, "Rus");

    FILE* file;
    if (fopen_s(&file, "records.txt", "rb") == 0) {
        struct Student student;

        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-5s |\n",
            "ID", "�������", "���", "��������", "������", "���� ��������", "�����", "�����������");

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%02d     | %-12s | ",
                student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

            if (student.subjects.math == 1)
                printf("���������� ");
            if (student.subjects.physics == 1)
                printf("������ ");
            if (student.subjects.programming == 1)
                printf("���������������� ");
            if (student.subjects.english == 1)
                printf("���������� ");
            if (student.subjects.database == 1)
                printf("���� ������");

            printf(" |\n");
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        fclose(file);
        print_admin_menu();

    }
    else {
        printf("�� ������� ������� ����.\n");
    }
}


void deleteStudentRecord(int k) {
  
    int id = k;

    FILE* file;
    if (fopen_s(&file, "records.txt", "rb") == 0) {
        FILE* tempFile;
        if (fopen_s(&tempFile, "temp.txt", "wb") == 0) {
            struct Student student;

            while (fread(&student, sizeof(struct Student), 1, file) != 0) {
                if (student.id != k) {
                    fwrite(&student, sizeof(struct Student), 1, tempFile);
                }
            }
            fclose(tempFile);
            fclose(file);
            remove("records.txt");
            rename("temp.txt", "records.txt");
            printf("������ ������� �������.\n");
            print_edit_menu(id);
        }
        else {
            printf("�� ������� ������� ��������� ����.\n");
        }
    }
    else {
        printf("�� ������� ������� ����.\n");
    }
    print_admin_menu();
}

void editStudentRecord(int k)
{
    FILE* file;
    struct Student student;
    int id = k;
    int found = 0;

    if (fopen_s(&file, "records.txt", "r+") == 0) {
        while (fread(&student, sizeof(struct Student), 1, file)) {
            if (student.id == id) {
                found = 1;
                printf("�������� ���� ��� ��������������:\n");
                printf("1. �������\n");
                printf("2. ���\n");
                printf("3. ��������\n");
                printf("4. ����� ������\n");
                printf("5. ���� ��������\n");
                printf("6. �����\n");
                printf("7. ������� ���� ������������\n");
                printf("8. �������������� �������\n");
                printf("9. ���� ������ �� �������\n");
                printf("��� �����: ");
                int choice;
                scanf_s("%d", &choice);

                switch (choice) {
                case 1:
                    printf("������� ����� �������: ");
                    scanf_s("%s", student.full_name.surname, sizeof(student.full_name.surname));
                    break;
                case 2:
                    printf("������� ����� ���: ");
                    scanf_s("%s", student.full_name.name, sizeof(student.full_name.name));
                    break;
                case 3:
                    printf("������� ����� ��������: ");
                    scanf_s("%s", student.full_name.patronymic, sizeof(student.full_name.patronymic));
                    break;
                case 4:
                    printf("������� ����� ����� ������: ");
                    scanf_s("%d", &student.group_number);
                    break;
                case 5:
                    printf("������� ����� ���� �������� (���� ����� ���): ");
                    scanf_s("%d %d %d", &student.birthday.day, &student.birthday.month, &student.birthday.year);
                    break;
                case 6:
                    printf("������� ����� �����: ");
                    scanf_s("%s", student.address, sizeof(student.address));
                    break;
                case 7:
                    printf("������� ����� ������� ���� ������������: ");
                    scanf_s("%f", &student.gpa);
                    break;
                case 8:
                    printf("�������� ����� �������������� �������:\n");
                    printf("1. ����������\n");
                    printf("2. ������\n");
                    printf("3. ����������������\n");
                    printf("4. ����������\n");
                    printf("5. ���� ������\n");
                    printf("��� �����: ");
                    int subjectChoice;
                    scanf_s("%d", &subjectChoice);
                    switch (subjectChoice) {
                    case 1:
                        student.subjects.math = 1;
                        break;
                    case 2:
                        student.subjects.physics = 1;
                        break;
                    case 3:
                        student.subjects.programming = 1;
                        break;
                    case 4:
                        student.subjects.english = 1;
                        break;
                    case 5:
                        student.subjects.database = 1;
                        break;
                    default:
                        printf("������������ �����.\n");
                        break;
                    }
                    break;
                case 9:
                    printf("������� ����� ���� ������ �� ������� (���� ����� ���): ");
                    scanf_s("%2d %2d %4d", &student.record.day, &student.record.month, &student.record.year);
                    break;
                default:
                    printf("������������ �����.\n");
                    break;
                }
                
                fseek(file, sizeof(student), SEEK_CUR);
                fwrite(&student, sizeof(student), 1, file);
                printf("������ ������� ���������������.\n");
                break;
            }
        }

        fclose(file);

        if (!found) {
            printf("������ � ��������� ID �� �������.\n");
        }

       
    }
    else {
        printf("�� ������� ������� ����.\n");
    } 
    print_edit_menu(id);
}




