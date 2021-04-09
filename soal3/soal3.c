#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

void getTime(char *string);
void cipher(char *string);

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("Must include argument -z or -x");
    exit(EXIT_FAILURE);
  } else if (!(strcmp(argv[1], "-z") == 0 || strcmp(argv[1], "-x") == 0)) {
    puts("Argument can only be -z or -x");
    exit(EXIT_FAILURE);
  }

  //! BOILER PLATE DAEMON
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
  if ((chdir("/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal3")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  //! /BOILER PLATE DAEMON

  //! KILLER PROGRAM
  FILE *killer;
  killer = fopen("Killer", "w");

  if (strcmp(argv[1], "-z") == 0) {
    // Instant Terminate
    fprintf(killer,
            "#!/bin/bash\n"
            "killList=$(echo $(pidof ./soal3))\n"
            "kill -9 $killList\n"
            "rm Killer");
  } else if (strcmp(argv[1], "-x") == 0) {
    // Stop Program
    fprintf(killer,
            "#!/bin/bash\n"
            "kill %d\n"
            "rm Killer",
            getpid());
  }
  fclose(killer);

  pid_t child_chmod;
  child_chmod = fork();

  if (child_chmod == 0) {
    char *argv[] = {"chmod", "+x", "Killer", NULL};
    execv("/usr/bin/chmod", argv);
  }
  //! KILLER PROGRAM

  while (1) {
    pid_t child_id;
    int status;

    child_id = fork();

    char parentDir[200];
    getTime(parentDir);

    // childnya ngerun, sampe mati di exec rm
    if (child_id == 0) {
      pid_t child_id2;
      int status2;

      child_id2 = fork();

      // Create Folder, then download the images inside
      if (child_id2 == 0) {
        char *argv[] = {"mkdir", "-p", parentDir, NULL};
        execv("/bin/mkdir", argv);
      } else {
        while ((wait(&status2)) > 0)
          ;
        // DOWNLOAD FILES
        char namaFile[300];
        char imgFile[70];
        char linkDownload[100];
        pid_t child_id3;
        int status3;

        // DOWNLOAD FILE
        for (int i = 0; i < 10; i++) {
          getTime(imgFile);
          // folder utama/imgFile
          sprintf(namaFile, "%s/%s.jpg", parentDir, imgFile);

          long int imageSize = time(NULL) % 1000 + 50;
          snprintf(linkDownload, sizeof(linkDownload),
                   "https://picsum.photos/%ld", imageSize);

          child_id3 = fork();

          if (child_id3 == 0) {
            char *argv[] = {"wget", "-q", "-O", namaFile, linkDownload, NULL};
            execv("/usr/bin/wget", argv);
          }

          sleep(5);
        }

        while ((wait(&status3)) > 0)
          ;

        // CREATE status.txt
        char statustxtFileName[100];
        char statusText[] = "Download Success";
        cipher(statusText);

        strcpy(statustxtFileName, parentDir);
        strcat(statustxtFileName, "/status.txt");
        // out: timestamp/status.txt

        FILE *statusFile = fopen(statustxtFileName, "w");
        fputs(statusText, statusFile);
        fclose(statusFile);

        // ZIP FOLDER
        pid_t child_id4;
        int status4;

        child_id4 = fork();

        if (child_id4 == 0) {
          char outputZip[300];
          sprintf(outputZip, "%s.zip", parentDir);

          char *argv[] = {"zip", "-r", outputZip, parentDir, NULL};
          execv("/usr/bin/zip", argv);
        } else {
          while ((wait(&status4)) > 0)
            ;
          // STOP the current fork to run again
          char *argv[] = {"rm", "-r", parentDir, NULL};
          execv("/usr/bin/rm", argv);
        }
      }
    } else {
    }
    //* DAEMON SLEEPING TIME
    sleep(40);
  }
}

// get Timestamp with format [YYYY-mm-dd_HH:ii:ss]
void getTime(char *string) {
  time_t t;
  struct tm *tmp;
  char MY_TIME[50];
  time(&t);

  tmp = localtime(&t);

  // using strftime to display time
  strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%H:%M:%S", tmp);
  // [YYYY-mm-dd_HH:ii:ss]

  strcpy(string, MY_TIME);
  return;
}

// Rewrites the inputted string to ciphered one
void cipher(char *successMsg) {
  char character;
  int key = 5;

  for (int i = 0; successMsg[i] != '\0'; ++i) {
    character = successMsg[i];

    if (character >= 'a' && character <= 'z') {
      character = character + key;

      if (character > 'z') {
        character = character - 'z' + 'a' - 1;
      }

      successMsg[i] = character;
    } else if (character >= 'A' && character <= 'Z') {
      character = character + key;

      if (character > 'Z') {
        character = character - 'Z' + 'A' - 1;
      }

      successMsg[i] = character;
    }
  }
}
