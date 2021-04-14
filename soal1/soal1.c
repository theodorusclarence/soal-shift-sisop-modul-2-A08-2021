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

int main() {
  char folderName[] = "Musyik";
  char downloadName[] = "MUSIK/";
  char baseFolder[200] =
      "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/";
  strcat(baseFolder, folderName);

  // Store downloaded files
  // "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/Musyik"
  char filesFolder[300];
  sprintf(filesFolder, "%s/%s", baseFolder, downloadName);
  puts(filesFolder);
}