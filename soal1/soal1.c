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
  chdir("/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal1/tes/MUSIK");
  char *argv[] = {"cp", "-r", ".", "..", NULL};
  execv("/usr/bin/cp", argv);
}