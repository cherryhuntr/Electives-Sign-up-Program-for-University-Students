#pragma once

#ifndef MENU_H
#define MENU_H

#include "storage.h"

void print_main_menu();
void print_admin_menu();
void print_student_menu(int k);
void print_edit_menu(int k);
void print_search_menu(void);
int is_alpha(char* str);
void addStudentApplication(int k);
void deleteStudentRecord(int k);
void editStudentRecord(int k);
void sortByGPA();
void searchStudentBySurname(const char* surname);
void searchStudentByAddress(const char* surname);
void searchStudentByGroup(int group);
void search();


#endif
