#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int check(struct tm tm, char* aux, char* cmd){
  char space[4][4];
  memset(space[0],'\0',sizeof(space[0]));
  memset(space[1],'\0',sizeof(space[0]));
  memset(space[2],'\0',sizeof(space[0]));

  int counter = 0;
  int digit = 0;
  int iter = 0 ;
  while(aux[iter] != '\0' && counter < 3)
  {
    if(aux[iter]==' '){
      counter++;
      digit = 0;
    }
    else {
      space[counter][digit] = aux[iter];
      digit++;
    }
    iter++;
  }
  strcpy(cmd,aux+iter);

  char menit[3]; char jam[3]; char detik[3];

  sprintf(menit, "%d", tm.tm_min);
  sprintf(jam, "%d", tm.tm_hour);
  sprintf(detik, "%d", tm.tm_sec);
  printf("%s-%s-%s\n", space[0], space[1], space[2]);
  printf("%s, %s, %s\n", detik, menit, jam);

  int flag = 1;

  if(strcmp(detik, space[0]) != 0 && strcmp(space[0], "*") != 0) return 0;
  if(strcmp(menit, space[1]) != 0 && strcmp(space[1], "*") != 0) return 0;
  if(strcmp(jam, space[2]) != 0 && strcmp(space[2], "*") != 0) return 0;

  return flag;
}


int main(int argc, char *argv[]) {
  //if(argc != 3){
    //perror("ERROR: argumen yang diberikan tidak sesuai");
    //return -1;
  //}
  char input[1000];
  sprintf(input, "%s %s %s %s", argv[1], argv[2], argv[3], argv[4]);

  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/yaniarpe/modul2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // cek waktu sekarang
    time_t t=time(NULL);
	  struct tm tm = *localtime(&t);

    int menit = tm.tm_min;
    int jam = tm.tm_hour;
    int detik = tm.tm_sec;
    char command[1000];
    if(check(tm,input,command)){
      char *argv[] = {"bash", command, NULL};
      //execv("bin/bash", argv);
    }
    sleep(1);
  }
  exit(EXIT_SUCCESS);
}
