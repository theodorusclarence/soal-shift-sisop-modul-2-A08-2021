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

// Foto https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
// Musik https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
// Film https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view
void musik(char *link);

int main() {
  char fotoLink[] =
      "https://drive.google.com/"
      "uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
  char musikLink[] =
      "https://drive.google.com/"
      "uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
  char filmLink[] =
      "https://drive.google.com/"
      "uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";

  musik(musikLink);
}

void musik(char *link) {
  pid_t child_id;
  int status;

  child_id = fork();

  char folderName[] = "Musyik";

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
        chdir("/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik");
        char *argv[] = {"unzip", "-q", "Download.zip", NULL};
        execv("/usr/bin/unzip", argv);

      } else {
        while ((wait(&status3)) > 0)
          ;
        pid_t child_id4;
        int status4;
        child_id4 = fork();

        if (child_id4 == 0) {
          // TODO Pindahin file
          chdir(
              "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik/"
              "MUSIK");
          char *argv[] = {"cp", "-r", ".", "..", NULL};
          execv("/usr/bin/cp", argv);
        } else {
          while ((wait(&status4)) > 0)
            ;

          chdir(
              "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik/");
          char *argv[] = {"rm", "-r", "MUSIK/", "Download.zip", NULL};
          execv("/usr/bin/rm", argv);
        }
      }
    }
  }
}