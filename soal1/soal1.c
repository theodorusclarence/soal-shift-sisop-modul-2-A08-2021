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

void reusable(char *link, char *folderName, char *downloadName);
void runBuildFolder();
void zipAndDestroy();
void getTime(char *string);

int main() {
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
  if ((chdir("/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  //! /BOILER PLATE DAEMON

  while (1) {
    char time[50];
    getTime(time);

    pid_t child_id;
    int status;

    child_id = fork();

    // childnya ngerun, sampe mati di exec rm
    if (child_id == 0) {
      if (strcmp(time, "2021-04-09_16:22:00") == 0) {
        // ! 6 JAM SEBELUM ULTAH STEVANY 😱
        runBuildFolder();
      } else if (strcmp(time, "2021-04-09_22:22:00") == 0) {
        // ! ULTAH STEVANY 🥳
        zipAndDestroy();
      } else {
        // ! do nothing
        char *argv[] = {"echo", NULL};
        execv("/usr/bin/echo", argv);
      }
    }

    sleep(1);
  }
}

void zipAndDestroy() {
  pid_t child_q1;
  int status_q1;

  child_q1 = fork();

  if (child_q1 == 0) {
    char *argv[] = {"zip",   "-r",      "-q",     "Lopyu_Stevany.zip",
                    "Fylm/", "Musyik/", "Pyoto/", NULL};
    execv("/usr/bin/zip", argv);
  } else {
    while ((wait(&status_q1)) > 0)
      ;

    char *argv[] = {"rm", "-r", "Fylm/", "Musyik/", "Pyoto/", NULL};
    execv("/usr/bin/rm", argv);
  }
}

void runBuildFolder() {
  char fotoLink[] =
      "https://drive.google.com/"
      "uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
  char musikLink[] =
      "https://drive.google.com/"
      "uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
  char filmLink[] =
      "https://drive.google.com/"
      "uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";

  pid_t child_q1, child_q2;
  int status_q1, status_q2;

  child_q1 = fork();

  if (child_q1 == 0) {
    reusable(musikLink, "Musyik", "MUSIK/");
  } else {
    child_q2 = fork();

    if (child_q2 == 0) {
      reusable(fotoLink, "Pyoto", "FOTO/");
    } else {
      reusable(filmLink, "Fylm", "FILM/");
    }
  }
}

void reusable(char *link, char *folderName, char *downloadName) {
  pid_t child_id;
  int status;

  // Store base folder
  // "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik"
  char baseFolder[200] =
      "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/";
  strcat(baseFolder, folderName);

  // Store downloaded files
  // "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik/MUSIK/"
  char filesFolder[300];
  sprintf(filesFolder, "%s/%s", baseFolder, downloadName);

  child_id = fork();

  if (child_id == 0) {
    // Create Folder
    char *argv[] = {"mkdir", folderName, NULL};
    execv("/usr/bin/mkdir", argv);

  } else {
    while ((wait(&status)) > 0)
      ;
    pid_t child_id2;
    int status2;
    child_id2 = fork();

    // TODO Download zip
    if (child_id2 == 0) {
      // Musyik/Download.zip
      char downloadLoc[200];
      sprintf(downloadLoc, "%s/Download.zip", folderName);

      // TODO Download
      char *argv[] = {"wget",      "-q", "--no-check-certificate", link, "-O",
                      downloadLoc, NULL};
      execv("/usr/bin/wget", argv);
    } else {
      while ((wait(&status2)) > 0)
        ;
      pid_t child_id3;
      int status3;
      child_id3 = fork();

      if (child_id3 == 0) {
        // TODO Uncompress
        chdir(baseFolder);
        // unzip quietly
        // Unzip to Musyik/MUSIK/*.mp3
        char *argv[] = {"unzip", "-q", "Download.zip", NULL};
        execv("/usr/bin/unzip", argv);

      } else {
        while ((wait(&status3)) > 0)
          ;
        pid_t child_id4;
        int status4;
        child_id4 = fork();

        if (child_id4 == 0) {
          // TODO Move file
          chdir(filesFolder);
          // Move files in MUSIK to back 1 level
          // From Musyik/MUSIK/*.mp3
          // To Musyik/*.mp3
          // Musyik/|remove|MUSIK/*.mp3
          char *argv[] = {"cp", "-r", ".", "..", NULL};
          execv("/usr/bin/cp", argv);
        } else {
          while ((wait(&status4)) > 0)
            ;
          // TODO Remove unused files
          chdir(baseFolder);
          // remove downloaded folder (MUSIK/) and Download file (Download.zip)
          char *argv[] = {"rm", "-r", downloadName, "Download.zip", NULL};
          execv("/usr/bin/rm", argv);
        }
      }
    }
  }
}

void getTime(char *string) {
  time_t t;
  struct tm *tmp;
  char MY_TIME[50];
  time(&t);

  tmp = localtime(&t);

  // using strftime to display time
  strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d_%H:%M:%S", tmp);

  strcpy(string, MY_TIME);
  return;
}