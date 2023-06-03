#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <conio.h>
#include <locale.h>
#include "storage.h"
#include "menu.h"
#include <ctype.h>



extern void save_student(int id, char* password) {
    FILE* file;
    if (fopen_s(&file, "students.txt", "w") == 0) {
        struct Student student;
        student.id = id;
        strcpy_s(student.password, password);
        fwrite(&student, sizeof(struct Student), 1, file);
        fclose(file);
        printf("\nНовый ID и пароль студента сохранены в файле.\n");
    }
    else {
        printf("\nОшибка: не удалось открыть файл для записи.\n");
    }
}

extern void save_admin(int id, char* password) {
    FILE* file;
    if (fopen_s(&file, "admin.txt", "w") == 0) {
        struct Admin admin;
        admin.id = id;
        strcpy_s(admin.password, password);
        fwrite(&admin, sizeof(struct Admin), 1, file);
        fclose(file);
        printf("\nНовый ID и пароль администратора сохранены в файле.\n");
    }
    else {
        printf("\nОшибка: не удалось открыть файл для записи.\n");
    }
}

int is_alpha(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}