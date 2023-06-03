#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <wchar.h>
#include <locale.h>
#include "storage.h"
#include "menu.h"
#include <ctype.h>



int check_student(int id, char* password) {
    struct Student student;

    FILE* file;
    if (fopen_s(&file, "students.txt", "r") == 0) {
        fread(&student, sizeof(struct Student), 1, file);
        fclose(file);

        if (student.id == id && strcmp(student.password, password) == 0) {

            return 1;
        }
        if (student.id == id == 0) {
            save_student(id, password);
            return 1;
        }
        else return 0;
    }
    return 0;
}

int login_student() {
    int id;
    char password[100];

    printf("Введите ID (только цифры): ");
    scanf_s("%d", &id);

    printf("Введите пароль (только английские буквы): ");
    scanf_s("%s", password, sizeof(password));

    if (!is_alpha(password)) {
        printf("\nНекорректный формат пароля! Пароль должен состоять только из английских букв.\n");
        print_main_menu();
        return 0;
    }

    if (check_student(id, password) == 1) {
        printf("Вы успешно авторизовались как студент!\n");
        print_student_menu(id);
        return 1;
    }
    else {
        printf("Введенный логин или пароль неверны!\n");
        print_main_menu();
        return 0;
    }
}
