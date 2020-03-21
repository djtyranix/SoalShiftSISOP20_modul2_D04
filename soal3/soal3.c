#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

void moving (const char* path){
  pid_t child_id, child_id2, child;
  int status;
  DIR *dir;
  struct dirent *a;
  char src[1024];
  char src2[1024];
  char file[1024];
  char file2[1024];

  if(!(dir = opendir(path))){
    return;
  }

  while ((a = readdir(dir)) != NULL){
    if (strcmp(a->d_name, ".") == 0 || strcmp(a->d_name, "..") == 0){
      continue;
    }
    child_id = fork();
    if (child_id < 0) {
      exit(EXIT_FAILURE);
    }
    if (child_id == 0) {
      // this is child
      if(a->d_type == DT_DIR){
        sprintf(src,"%s%s%s", "/home/yaniarpe/modul2/jpg/", a->d_name, "/");
        sprintf(src2,"%s%s%s", "/home/yaniarpe/modul2/indomie/", a->d_name, "/");
        sprintf(file,"%s%s", src2, "coba1.txt");
        sprintf(file2,"%s%s", src2, "coba2.txt");
        child_id2 = fork();
        if (child_id2 < 0) {
          exit(EXIT_FAILURE);
        }
        if (child_id2 == 0){
          char *argv4[] = {"mv", src, "/home/yaniarpe/modul2/indomie/", NULL};
          execv("/bin/mv", argv4);
        }
        else{
          wait(NULL);
          child = fork();
          if (child < 0) {
            exit(EXIT_FAILURE);
          }
          if (child == 0) {
            char *argv5[] = {"touch", file, NULL};
            execv("/usr/bin/touch", argv5);
          }
          else{
            while((wait(&status))>0){
              sleep(3);
              char *argv5[] = {"touch", file2, NULL};
              execv("/usr/bin/touch", argv5);
            }
          }
        }
      }
      else{
        sprintf(src,"%s%s", "/home/yaniarpe/modul2/jpg/", a->d_name);
        char *argv6[] = {"mv", src, "/home/yaniarpe/modul2/sedaap/", NULL};
        execv("/bin/mv", argv6);
      }
    }
  }
  closedir(dir);
}

int main() {
  pid_t child1, child2, child3, child4;
  int status;

  child1 = fork();

  if (child1 < 0) {
    exit(EXIT_FAILURE);
  }
  if (child1 == 0) {
    // this is child
    child2 = fork();
    if (child2 < 0) {
      exit(EXIT_FAILURE);
    }
    if (child2 == 0){
      // this is child
      char *argv1[] = {"mkdir", "-p", "/home/yaniarpe/modul2/indomie/", NULL};
      execv("/bin/mkdir", argv1);
    }
    else{
      while((wait(&status))>0){
        sleep(5);
        char *argv2[] = {"mkdir", "-p", "/home/yaniarpe/modul2/sedaap/", NULL};
        execv("/bin/mkdir", argv2);
      }
    }
  }
  else{
    wait(NULL);
    child3 = fork();
    if (child3 < 0) {
      exit(EXIT_FAILURE);
    }
    if (child3 == 0){
      // this is child
      child4 = fork();
      if (child4 < 0) {
        exit(EXIT_FAILURE);
      }
      if (child4 == 0){
        // this is child
        char *argv3[] = {"unzip", "/home/yaniarpe/modul2/jpg.zip", "-d", "/home/yaniarpe/modul2/", NULL};
        execv("/usr/bin/unzip", argv3);
      }
      else{
        wait(NULL);
        moving ("/home/yaniarpe/modul2/jpg/");
      }
    }
    else{
      wait(NULL);
    }
  }
}
