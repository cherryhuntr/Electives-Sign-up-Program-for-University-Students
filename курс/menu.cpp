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

// Функция main()
int main() {
    setlocale(LC_ALL, "Rus");


    // Заполнение массива студентов данными из файла
    FILE* file;
    if (fopen_s(&file, "students.txt", "r+") == 0)
    {
        // Получаем количество записей в файле
        fseek(file, 0L, SEEK_END);
        long file_size = ftell(file);
        num_students = file_size / sizeof(struct Student);
        rewind(file);
        struct Student* student = (struct Student*)malloc(num_students * sizeof(struct Student));
        // Считываем данные из файла в массив структур
        fread(student, sizeof(struct Student), num_students, file);

        fclose(file);

    }
    else {
        printf("Ошибка открытия файла!\n");
        exit(1);
    }



    print_main_menu();

    return 0;
}



void print_main_menu() {
    int choice;
    printf("Как вы хотите войти в программу?\n");
    printf("1. Войти как администратор\n");
    printf("2. Войти как студент\n");
    printf("3. Выйти\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Ошибка: введен некорректный выбор\n");
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
            // Выход из программы
            printf("До свидания!\n");
            exit(0);
        }
    }
}



void print_admin_menu() {
    int choice;
    printf("--------------------------------------------------------МЕНЮ АДМИНИСТРАТОРА----------------------------------------------------------\n");
    printf("1. Режим управления учетными записями\n");
    printf("2. Посмотреть все записи\n");
    printf("3. Поиск студентов\n");
    printf("4. Сортировка студентов по убыванию среднего балла\n");
    printf("5. Назад\n");
    printf("6. Выйти\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 6) {
        printf("\nОшибка: введен некорректный выбор\n");
        print_admin_menu();
    }

    switch (choice) {
    case 1:
        
        int id;
        printf("Введите id студента: ");
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
        
        printf("\nДо свидания!\n");
        exit(0);
    }
}

void print_student_menu(int k) {
    int id = k;
    int choice;
    printf("----------------------------------------------------------МЕНЮ СТУДЕНТА------------------------------------------------------------\n");
    printf("1. Редактировать личный кабинет\n");
    printf("2. Поиск студентов\n");
    printf("3. Сортировка студентов по убыванию среднего балла\n");
    printf("4. Назад\n");
    printf("5. Выйти\n");
    printf("Ваш выбор: ");
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 5) {
        printf("\nОшибка: введен некорректный выбор\n");
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
        printf("\nДо свидания!\n");
        exit(0);
    }
}

void search() {


    printf("1. По фамилии\n");
    printf("2. По адресу\n");
    printf("3. По номеру группы\n");
    printf("4. Назад\n");
    printf("5. Выйти\n");
    printf("Ваш выбор: ");
    int choice;
    scanf_s("%d", &choice);

    if (choice < 1 || choice > 5) {
        printf("\nОшибка: введен некорректный выбор\n");
        search();
    }

    switch (choice) {
    case 1:
        char surname[20];
        printf("Введите фамилию искомого студента: ");
        scanf_s("%s", surname, sizeof(surname));
        searchStudentBySurname(surname);
        break;
    case 2:
        char address[20];
        printf("Введите адрес искомого студента: ");
        scanf_s("%s", address, sizeof(address));
        searchStudentByAddress(address);
        break;
    case 3:
        int group;
        printf("Введите номер группы искомого студента: ");
        scanf_s("%d", &group);
        searchStudentByGroup(group);
        break;
    case 4:
        print_main_menu();
        break;

    case 5:
        printf("\nДо свидания!\n");
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

       
                printf("1. Добавление записи\n");
                printf("2. Удаление записи\n");
                printf("3. Редактирование записи\n");
                printf("4. Назад\n");
                printf("5. Выйти\n");
                printf("Ваш выбор: ");
                int choice;
                scanf_s("%d", &choice);

                if (choice < 1 || choice > 5) {
                    printf("\nОшибка: введен некорректный выбор\n");
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
                    // Выход из программы
                    printf("\nДо свидания!\n");
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

        // Сортировка по среднему баллу
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (students[j].gpa < students[j + 1].gpa) {
                    struct Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        printf("Студенты, отсортированные по среднему баллу:\n");
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-5s | %-10s |\n",
            "ID", "Фамилия", "Имя", "Отчество", "Группа", "Дата рождения", "Факультатив", "Средний балл");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < count; i++) {
            struct Student student = students[i];

            char gpaString[10];
            sprintf_s(gpaString, "%.2f", student.gpa);

            printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%02d     | ",
                student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                student.group_number, student.birthday.day, student.birthday.month, student.birthday.year);

            if (student.subjects.math == 1)
                printf("Математика ");
            if (student.subjects.physics == 1)
                printf("Физика ");
            if (student.subjects.programming == 1)
                printf("Программирование ");
            if (student.subjects.english == 1)
                printf("Английский ");
            if (student.subjects.database == 1)
                printf("Базы данных");

            printf(" | %10s |\n", gpaString);
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        fclose(file);
    }
    else {
        printf("Не удалось открыть файл.\n");
    }
    print_main_menu();
}



void searchStudentBySurname(const char* surname)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("Результаты поиска по фамилии '%s':\n", surname);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-10s |\n",
            "ID", "Фамилия", "Имя", "Отчество", "Группа", "Дата рождения", "Адрес", "Факультатив");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (strcmp(student.full_name.surname, surname) == 0) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("Математика ");
                if (student.subjects.physics == 1)
                    printf("Физика ");
                if (student.subjects.programming == 1)
                    printf("Программирование ");
                if (student.subjects.english == 1)
                    printf("Английский ");
                if (student.subjects.database == 1)
                    printf("Базы данных");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("Студент с фамилией '%s' не найден.\n", surname);
        }

        fclose(file);
    }
    else {
        printf("Не удалось открыть файл.\n");
    }
    search();
}

void searchStudentByAddress(const char* surname)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("Результаты поиска по адресу '%s':\n", surname);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-5s |\n",
            "ID", "Фамилия", "Имя", "Отчество", "Группа", "Дата рождения", "Адрес", "Факультатив");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (strcmp(student.address, surname) == 0) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("Математика ");
                if (student.subjects.physics == 1)
                    printf("Физика ");
                if (student.subjects.programming == 1)
                    printf("Программирование ");
                if (student.subjects.english == 1)
                    printf("Английский ");
                if (student.subjects.database == 1)
                    printf("Базы данных");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("Студент по адресу '%s' не найден.\n", surname);
        }

        fclose(file);
    }
    else {
        printf("Не удалось открыть файл.\n");
    }
    search();
}

void searchStudentByGroup(int groupNumber)
{
    FILE* file;
    struct Student student;

    if (fopen_s(&file, "records.txt", "r") == 0) {
        int found = 0;

        printf("Результаты поиска по номеру группы '%d':\n", groupNumber);
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-15s | %-15s | %-15s | %-6s | %-10s | %-12s | %-5s |\n",
            "ID", "Фамилия", "Имя", "Отчество", "Группа", "Дата рождения", "Адрес", "Факультатив");
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            if (student.group_number == groupNumber) {
                found = 1;
                printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%04d     | %-12s | ",
                    student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                    student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

                if (student.subjects.math == 1)
                    printf("Математика ");
                if (student.subjects.physics == 1)
                    printf("Физика ");
                if (student.subjects.programming == 1)
                    printf("Программирование ");
                if (student.subjects.english == 1)
                    printf("Английский ");
                if (student.subjects.database == 1)
                    printf("Базы данных");

                printf(" |\n");
            }
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        if (!found) {
            printf("Студенты в группе '%d' не найдены.\n", groupNumber);
        }

        fclose(file);
    }
    else {
        printf("Не удалось открыть файл.\n");
    }
    search();
}




void addStudentApplication(int k)
{
    setlocale(LC_ALL, "Rus");
    struct Student student;
    int id = k;

    printf("Введите фамилию: ");
    scanf_s("%s", student.full_name.surname, sizeof(student.full_name.surname));

    printf("Введите имя: ");
    scanf_s("%s", student.full_name.name, sizeof(student.full_name.name));

    printf("Введите отчество: ");
    scanf_s("%s", student.full_name.patronymic, sizeof(student.full_name.patronymic));

    printf("Введите номер группы: ");
    scanf_s("%d", &student.group_number, sizeof(student.group_number));

    student.id = id;

    printf("Введите дату рождения (день месяц год): ");
    scanf_s("%d %d %d", &student.birthday.day, &student.birthday.month, &student.birthday.year);

    printf("Введите адрес: ");
    scanf_s("%s", student.address, sizeof(student.address));

    printf("Введите средний балл успеваемости: ");
    scanf_s("%f", &student.gpa, sizeof(student.gpa));

    printf("Выберите факультативное занятие:\n");
    printf("1. Математика\n");
    printf("2. Физика\n");
    printf("3. Программирование\n");
    printf("4. Английский\n");
    printf("5. Базы данных\n");
    printf("Ваш выбор: ");
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
        printf("Некорректный выбор.\n");
        return;
    }

    printf("Введите дату записи на занятие (день месяц год): ");
    scanf_s("%2d %2d %4d", &student.record.day, &student.record.month, &student.record.year);

    FILE* file;
    if (fopen_s(&file, "records.txt", "ab") == 0) {
        fwrite(&student, sizeof(struct Student), 1, file);
        fclose(file);

        printf("Заявление успешно добавлено.\n");
        print_edit_menu(id);
    }
    else {
        printf("Не удалось открыть файл.\n");
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
            "ID", "Фамилия", "Имя", "Отчество", "Группа", "Дата рождения", "Адрес", "Факультатив");

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(struct Student), 1, file) != 0) {
            printf("| %-6d | %-15s | %-15s | %-15s | %-6d | %02d.%02d.%02d     | %-12s | ",
                student.id, student.full_name.surname, student.full_name.name, student.full_name.patronymic,
                student.group_number, student.birthday.day, student.birthday.month, student.birthday.year, student.address);

            if (student.subjects.math == 1)
                printf("Математика ");
            if (student.subjects.physics == 1)
                printf("Физика ");
            if (student.subjects.programming == 1)
                printf("Программирование ");
            if (student.subjects.english == 1)
                printf("Английский ");
            if (student.subjects.database == 1)
                printf("Базы данных");

            printf(" |\n");
        }

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        fclose(file);
        print_admin_menu();

    }
    else {
        printf("Не удалось открыть файл.\n");
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
            printf("Запись успешно удалена.\n");
            print_edit_menu(id);
        }
        else {
            printf("Не удалось создать временный файл.\n");
        }
    }
    else {
        printf("Не удалось открыть файл.\n");
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
                printf("Выберите поле для редактирования:\n");
                printf("1. Фамилия\n");
                printf("2. Имя\n");
                printf("3. Отчество\n");
                printf("4. Номер группы\n");
                printf("5. Дата рождения\n");
                printf("6. Адрес\n");
                printf("7. Средний балл успеваемости\n");
                printf("8. Факультативное занятие\n");
                printf("9. Дата записи на занятие\n");
                printf("Ваш выбор: ");
                int choice;
                scanf_s("%d", &choice);

                switch (choice) {
                case 1:
                    printf("Введите новую фамилию: ");
                    scanf_s("%s", student.full_name.surname, sizeof(student.full_name.surname));
                    break;
                case 2:
                    printf("Введите новое имя: ");
                    scanf_s("%s", student.full_name.name, sizeof(student.full_name.name));
                    break;
                case 3:
                    printf("Введите новое отчество: ");
                    scanf_s("%s", student.full_name.patronymic, sizeof(student.full_name.patronymic));
                    break;
                case 4:
                    printf("Введите новый номер группы: ");
                    scanf_s("%d", &student.group_number);
                    break;
                case 5:
                    printf("Введите новую дату рождения (день месяц год): ");
                    scanf_s("%d %d %d", &student.birthday.day, &student.birthday.month, &student.birthday.year);
                    break;
                case 6:
                    printf("Введите новый адрес: ");
                    scanf_s("%s", student.address, sizeof(student.address));
                    break;
                case 7:
                    printf("Введите новый средний балл успеваемости: ");
                    scanf_s("%f", &student.gpa);
                    break;
                case 8:
                    printf("Выберите новое факультативное занятие:\n");
                    printf("1. Математика\n");
                    printf("2. Физика\n");
                    printf("3. Программирование\n");
                    printf("4. Английский\n");
                    printf("5. Базы данных\n");
                    printf("Ваш выбор: ");
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
                        printf("Некорректный выбор.\n");
                        break;
                    }
                    break;
                case 9:
                    printf("Введите новую дату записи на занятие (день месяц год): ");
                    scanf_s("%2d %2d %4d", &student.record.day, &student.record.month, &student.record.year);
                    break;
                default:
                    printf("Некорректный выбор.\n");
                    break;
                }
                
                fseek(file, sizeof(student), SEEK_CUR);
                fwrite(&student, sizeof(student), 1, file);
                printf("Запись успешно отредактирована.\n");
                break;
            }
        }

        fclose(file);

        if (!found) {
            printf("Запись с указанным ID не найдена.\n");
        }

       
    }
    else {
        printf("Не удалось открыть файл.\n");
    } 
    print_edit_menu(id);
}




