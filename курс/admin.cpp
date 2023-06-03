#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "storage.h"
#include "menu.h"
#include <ctype.h>



// функция для проверки наличия администратора в файле
extern int check_admin(int id, char* password) {
    struct Admin admin;

    FILE* file;
    if (fopen_s(&file, "admin.txt", "r") == 0) {
        fread(&admin, sizeof(struct Admin), 1, file);
        fclose(file);

        if (admin.id == id && strcmp(admin.password, password) == 0) {
            
            return 1;
        }
        if (admin.id == id  == 0) {
            save_admin(id, password);
            return 1;
        }
        else return 0;
    }

    
}



// функция для авторизации администратора
int login_admin() {
    int id;
    char password[100];

    printf("Введите ID (только цифры): ");
    scanf_s("%d", &id);

    printf("Введите пароль (только английские буквы): ");
    scanf_s("%s", password, sizeof(password));

    if (!is_alpha(password)) {
        printf("\nНекорректный формат пароля! Пароль должен состоять только из символов.\n");
        print_main_menu();
        return 0;
    }

    // проверка наличия пользователя в файле
    if (check_admin(id, password)) {
        printf("\nВы успешно авторизовались как администратор!\n");
        print_admin_menu();
        return 1;
    }
    else {
        printf("\nВведенный логин или пароль неверны!\n");
        print_main_menu();
        return 0;
    }
}