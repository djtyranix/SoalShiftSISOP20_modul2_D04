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
#include <sys/wait.h>
#include <ctype.h>



int main(int argc, char *argv[]) {
  if(argc != 5){
    printf("ERROR: argumen yang diberikan tidak sesuai\n");
    exit(EXIT_FAILURE);
  }
  else{
    int times[4];
    int i;
    char command[1024];
    for(i = 1; i <= 3; i++){
      if(strlen(argv[i]) > 2){
        printf("ERROR: argumen yang diberikan tidak sesuai\n");
        exit(EXIT_FAILURE);
      }
      else if(strcmp(argv[i], "*") == 0){
        times[i] = -1; //for every (sec/min/hour)
      }
      else{
        int j, alpha = 0;
        for(j = 0 ; j < (strlen(argv[i]) + 1); j++){
          if(isalpha(argv[i][j])){
            alpha = 1;
            break;
          }
        }
        if(alpha == 1){
          printf("ERROR: argumen yang diberikan tidak sesuai\n");
          exit(EXIT_FAILURE);
        }
        else{
        times[i] = atoi(argv[i]);
          if(times[i]<0){
            printf("ERROR: argumen yang diberikan tidak sesuai\n");
            exit(EXIT_FAILURE);
          }
        }
      }
    }
    if (times[1] > 59){
      printf("ERROR: argumen yang diberikan tidak sesuai\n");
      exit(EXIT_FAILURE);
    }
    if (times[2] > 59){
      printf("ERROR: argumen yang diberikan tidak sesuai\n");
      exit(EXIT_FAILURE);
    }
    if (times[3] > 23){
      printf("ERROR: argumen yang diberikan tidak sesuai\n");
      exit(EXIT_FAILURE);
    }
    strcpy(command, argv[4]);

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
      time_t t;
  	  struct tm *tm;
      t = time(NULL);
      tm = localtime(&t);
      //check time
      if((times[1] == -1 || tm->tm_sec == times[1]) && (times[2] == -1 || tm->tm_min == times[2]) && (times[3] == -1 || tm->tm_hour == times[3])){
        pid_t child_id;
        int status;
        child_id = fork();

        if (child_id < 0) {
          exit(EXIT_FAILURE);
        }
        if (child_id == 0){
          char *argvv[] = {"bash", command, NULL};
          execv("/bin/bash", argvv);
        }
        else{
          wait(NULL);
        }
      }
      sleep(1); //interval every second
    }
  }
}
