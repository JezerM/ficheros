#include <cstdio>
#include <cstring>
#include <string>
#include "global.h"

using namespace std;

struct winc winconf;

void addReg();
void removeReg();
void readReg(string fileName);
void viewReg();
void saveReg(string fileName);
void editReg();

void checkFile(string name, FILE *buff) {
  buff = fopen(name.c_str(), "r");
  if (!buff) {
    buff = fopen(name.c_str(), "w");
    printf("File created\n");
  }
  fclose(buff);
}

int main() {
  FILE *file;

  string fileName = "data.bin";
  checkFile(fileName, file);
  readReg(fileName);
  
  bool running = true;
  printf("[1] - Add\n");
  printf("[2] - Remove\n");
  printf("[3] - Read\n");
  printf("[4] - Edit\n");
  printf("[5] - Save\n");
  printf("[6] - Exit\n");

  int onceExit = 0;

  while (running) {
    int opt;
    printf("Choose: ");
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        addReg();
        break;
      case 2:
        removeReg();
        break;
      case 3:
        viewReg();
        break;
      case 4:
        editReg();
        break;
      case 5:
        saveReg(fileName);
        break;
      case 6:
        if (winconf.changed == 1 && onceExit == 0) {
          printf("Data not saved yet.\n");
          printf("Exit again to not save your data\n");
          onceExit = 1;
        } else
        if (winconf.changed == 0 || onceExit == 1) {
          exit(0);
        }
        break;
      default:
        break;
    }
  }
  
  return 0;
}
