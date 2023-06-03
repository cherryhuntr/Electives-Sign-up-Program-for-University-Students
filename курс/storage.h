#pragma once

#ifndef HEADER_H
#define HEADER_H

#include "menu.h"

// Прототипы структур
struct Admin;
struct Student;
struct Date;
struct Subject;
struct Fio;

// Структура, описывающая информацию об администраторе
 struct Admin {
    int id;
    char password[20]; // пароль администратора
};

struct Fio {
    char surname[70];
    char name[70];
    char patronymic[70];
};



// Структура, описывающая факультативные предметы, на которые можно записаться
struct Subject {
    int math;
    int physics;
    int programming;
    int english;
    int database;

};

// Структура, описывающая дату рождения
struct Date {
    int day;
    int month;
    int year;
};
// Структура, описывающая информацию о студенте
struct Student {
    int id;
    char address[70];
    char password[20];
    int group_number;
    float gpa;
    struct Fio full_name;
    struct Date birthday;
    struct Date record;
    struct Subject subjects;
};


void save_admin(int id, char* password);
void save_student(int id, char* password);
int login_admin();
void print_all_students();
int login_student();
int check_admin(int id, char* password);
int check_student(int id, char* password);





#endif // HEADER_H
