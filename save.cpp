#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include "global.h"

using namespace std;

int size;

struct task {
  char name[51];
  char date[12];
  bool completed = false;
};

struct task lista[100];

void readReg(string fileName) {
  FILE *file;
  file = fopen("data.bin", "r");
  struct task readed;
  int i = 0;
  while (fread(&readed, sizeof(struct task), 1, file)) {
    lista[i] = readed;
    i++;
  }
  size = i;
  fclose(file);
}

void viewReg() {
  for (int i = 0; i < 100 ; i++) {
    if (strcmp(lista[i].name, "") == 0) break;
    printf("[%d] \"%s\" - %s - %s\n", i, lista[i].name, lista[i].date, lista[i].completed ? "Done" : "Nope");
  }
}

void addReg() {
  struct task newTask;
  newTask.completed = false;
  char c;
  while ((c = getchar() != '\n' && c != EOF)) {}
  printf("--- Adding task ---\n");
  printf("Name: ");
  cin.getline(newTask.name, 50);

  printf("Date (09-12-2021): ");
  cin.getline(newTask.date, 11);
  if (strcmp(newTask.name, "") == 0 || strcmp(newTask.date, "") == 0) {
    printf("No task added\n");
    return;
  }

  printf("\"%s\" - %s\n", newTask.name, newTask.date);
  lista[size] = newTask;
  size++;
  winconf.changed = 1;
}

void removeReg() {
  struct task deletedTask;
  struct task copyList[100];
  char c;
  int index;
  while((c = getchar()) != '\n' && c != EOF) {}
  printf("--- Removing task ---\n");
  printf("File index: ");
  scanf("%d", &index);
  if (index < 0) {
    printf("Error: Index below 0\n");
    return;
  }
  if (strcmp(lista[index].name, "") == 0) {
    printf("No task in index [%d]\n", index);
    return;
  }
  int r = 0;
  for (int i = 0; i < 100; i++) {
    if (i == index) continue;
    if (strcmp(lista[r].name, "") == 0) break;
    copyList[r] = lista[i];
    r++;
  }
  copy(copyList, copyList+99, lista);
  size--;
  winconf.changed = 1;
}

void editReg() {
  struct task editedTask;
  char c;
  int index;
  char completed[2];
  while((c = getchar()) != '\n' && c != EOF) {}
  printf("--- Editing task ---\n");
  printf("File index: ");
  scanf("%d", &index);
  while((c = getchar()) != '\n' && c != EOF) {}
  if (index < 0) {
    printf("Error: Index below 0\n");
    return;
  }
  if (strcmp(lista[index].name, "") == 0) {
    printf("No task in index [%d]\n", index);
    return;
  }
  printf("Name: ");
  cin.getline(editedTask.name, 50);
  printf("Date: ");
  cin.getline(editedTask.date, 11);
  printf("Completed (1 or 0): ");
  cin.getline(completed, 2);
  if (strcmp(editedTask.name, "") == 0) {
    strcpy(editedTask.name, lista[index].name);
  }
  if (strcmp(editedTask.date, "") == 0) {
    strcpy(editedTask.date, lista[index].date);
  }
  if (strcmp(completed, "") == 0) {
    editedTask.completed = lista[index].completed;
  } else {
    editedTask.completed = stoi(completed);
  }

  lista[index] = editedTask;
  printf("Task modified\n");
  winconf.changed = 1;
}

void saveReg(string fileName) {
  FILE *file;
  file = fopen(fileName.c_str(), "w");
  for (int i = 0; i < 100; i++) {
    if (strcmp(lista[i].name, "") == 0) break;
    fwrite(&lista[i], sizeof(struct task), 1, file);
  }
  fclose(file);
  printf("Archivos guardados\n");
  winconf.changed = 0;
}
