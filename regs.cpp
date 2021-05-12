#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

struct task {
  char name[51];
  char date[12];
  bool completed = false;
};

void aReg(std::string fileName, char name[50], char date[8]) {
  FILE *file;
  file = fopen(fileName.c_str(), "a");
  struct task newTask;
  newTask.completed = false;
  int stringLength = strlen(name);
  for (int i = 0; i < stringLength; i++) {
    newTask.name[i] = name[stringLength-1-i];
  }
  newTask.name[stringLength] = '\0';

  stringLength = strlen(date);
  for (int i = 0; i < stringLength; i++) {
    newTask.date[i] = date[stringLength-1-i];
  }
  newTask.date[stringLength] = '\0';
  fwrite(&newTask, sizeof(struct task), 1, file);

  fclose(file); 
}

/*
 *void addReg(std::string fileName) {
 *  FILE *file;
 *  struct task newTask;
 *  newTask.completed = false;
 *  file = fopen(fileName.c_str(), "a");
 *
 *  int c;
 *  while((c = getchar()) != '\n' && c != EOF) {}
 *
 *  printf("--- Adding task ---\n");
 *  printf("Name: ");
 *  cin.getline(newTask.name, 50);
 *  //fgets(newTask.name, 50, stdin);
 *    //strtok(newTask.name,"\n");
 *  printf("Date (09-12-2021): ");
 *  cin.getline(newTask.date, 11);
 *  //fgets(newTask.date, 11, stdin);
 *    //strtok(newTask.date,"\n");
 *  printf("\"%s\" - %s\n", newTask.name, newTask.date);
 *
 *  fwrite(&newTask, sizeof(struct task), 1, file);
 *
 *  fclose(file);
 *}
 */

void removeReg(std::string fileName) {
  FILE *file, *tmp;
  file = fopen(fileName.c_str(), "r");
  int c, index;
  while((c = getchar()) != '\n' && c != EOF) {}

  printf("--- Removing task ---\n");
  printf("File index: ");
  scanf("%d", &index);

  tmp = fopen("temp", "w");

  struct task readed;
  int i = -1;
  /*
  while (feof(file) == 0) {
    fread(&readed, sizeof(struct task), 1, file);
    if (i != index) {
      fwrite(&readed, sizeof(struct task), 1, tmp);
      printf("[%d] \"%s\" - %s\n", i, readed.name, readed.date);
    }
    i++;
  }*/
  while (!feof(file)) {
    fread(&readed, sizeof(struct task), 1, file);
    if (!feof(file)) {
      i++;
      /* skip the line at given line number */
      if (i != index) {
        fwrite(&readed, sizeof(struct task), 1, tmp);
      }
    }
  }

  fclose(file);
  fclose(tmp);
  remove(fileName.c_str());
  rename("temp", fileName.c_str());
}

/*
 *void readReg(std::string fileName) {
 *  FILE *file;
 *  file = fopen(fileName.c_str(), "r");
 *  struct task readed;
 *  int i = 0;
 *  while(fread(&readed, sizeof(struct task), 1, file)) {
 *    printf("[%d] \"%s\" - %s\n", i, readed.name, readed.date);
 *    i++;
 *  }
 *  fclose(file);
 *}
 */
