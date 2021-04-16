#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

int dtmsplit(char *str, const char *delim, char ***array, int *length);
size_t file_list(const char *path, char ***ls);
void readFileAndDelimitUnderscore(char **pets, int *countPets);
void writeLog();
void unzipAndCleanFiles();

int main(int argc, char **argv) {
  pid_t child_unzip;
  int status_unzip;

  child_unzip = fork();

  if (child_unzip == 0) {
    unzipAndCleanFiles();

  } else {
    while ((wait(&status_unzip)) > 0)
      ;

    char **files;
    size_t count;
    int i;

    count = file_list(
        "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal2/files", &files);
    for (i = 0; i < count; i++) {
      // Copies the same files, because the original files will be mutated (to
      // use later for copying files.)
      char filesUntouched[70];
      strcpy(filesUntouched, files[i]);
      // REMOVE 4 character from files (.jpg)
      files[i][strlen(files[i]) - 4] = '\0';

      int c = 0;
      int countTok = 0;
      char **individualPets = NULL;

      c = dtmsplit(files[i], "_", &individualPets, &countTok);

      for (int j = 0; j < countTok; j++) {
        int d = 0;

        int petAtrTok = 0;
        char **petAtr = NULL;

        // store to temp so it does not mutate the individualPets
        char temp[100];
        strcpy(temp, individualPets[j]);

        d = dtmsplit(temp, ";", &petAtr, &petAtrTok);

        //* DEFINITION
        // individualPets[j] = dog;amo;6
        // petAtr[0] = category (cat, turtle)
        // petAtr[1] = name (bambang, joni)
        // petAtr[2] = age (2, 3)

        // create folder name with category (don't care if exists), then cp
        pid_t child_id_mkdir;
        int status_mkdir;

        child_id_mkdir = fork();

        if (child_id_mkdir == 0) {
          // TODO Create directory petshop/cat...
          char petDir[100];
          sprintf(petDir, "petshop/%s", petAtr[0]);

          // using -p, if parent folder not exist, will create it, and quiet if
          // there is error
          char *argv[] = {"mkdir", "-p", petDir, NULL};
          execv("/usr/bin/mkdir", argv);
        } else {
          while ((wait(&status_mkdir)) > 0)
            ;

          pid_t child_id_cp;
          int status_cp;

          child_id_cp = fork();

          if (child_id_cp == 0) {
            // COPY EACH PETS TO PROPER DIRECTORY
            char fromFile[100], toFile[100];
            sprintf(fromFile, "%s", filesUntouched);
            sprintf(toFile, "../petshop/%s/%s.jpg", petAtr[0], petAtr[1]);

            writeLog(petAtr[0], petAtr[1], petAtr[2]);

            chdir(
                "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal2/"
                "files");
            char *argv[] = {"cp", fromFile, toFile, NULL};
            execv("/usr/bin/cp", argv);
          }
        }  // end else mkdir pet category
      }    // end looping each individual pets
    }
  }
}

// Will be terminated
void unzipAndCleanFiles() {
  pid_t child_mkdir;
  int status_mkdir;

  child_mkdir = fork();

  if (child_mkdir == 0) {
    char *argv[] = {"mkdir", "files", NULL};
    execv("/usr/bin/mkdir", argv);
  } else {
    while ((wait(&status_mkdir)) > 0)
      ;
    chdir("/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal2/files");
    char *argv[] = {
        "unzip",    "../pets.zip",         "*", "-x", "apex_cheats/*",
        "musics/*", "unimportant_files/*", NULL};
    execv("/usr/bin/unzip", argv);
  }
}

void writeLog(char category[], char nama[], char umur[]) {
  char templatePrint[200];
  sprintf(templatePrint, "nama: %s\numur: %s tahun\n\n", nama, umur);

  FILE *keteranganFile;

  char keteranganLoc[150];
  sprintf(keteranganLoc, "petshop/%s/keterangan.txt", category);

  keteranganFile = fopen(keteranganLoc, "a");
  fprintf(keteranganFile, "%s", templatePrint);

  fclose(keteranganFile);
}

void readFileAndDelimitUnderscore(char **pets, int *countPets) {
  char **files;
  size_t count;
  int i;

  count = file_list(
      "/home/clarence/soal-shift-sisop-modul-2-A08-2021/soal2/files", &files);
  for (i = 0; i < count; i++) {
    // printf("%s\n", files[i]);
    int c = 0;
    int countTok = 0;
    char **arr = NULL;

    c = dtmsplit(files[i], "_", &arr, &countTok);

    for (int j = 0; j < countTok; j++) {
      printf("%s\n", arr[j]);
    };
  }
}

// Mutates the str, and the length
int dtmsplit(char *str, const char *delim, char ***array, int *length) {
  int i = 0;
  char *token;
  char **res = (char **)malloc(0 * sizeof(char *));

  /* get the first token */
  token = strtok(str, delim);
  while (token != NULL) {
    res = (char **)realloc(res, (i + 1) * sizeof(char *));
    res[i] = token;
    i++;
    token = strtok(NULL, delim);
  }
  *array = res;
  *length = i;
  return 1;
}

size_t file_list(const char *path, char ***ls) {
  size_t count = 0;
  size_t length = 0;
  DIR *dp = NULL;
  struct dirent *ep = NULL;

  dp = opendir(path);
  if (NULL == dp) {
    fprintf(stderr, "no such directory: '%s'", path);
    return 0;
  }

  *ls = NULL;
  ep = readdir(dp);
  while (NULL != ep) {
    count++;
    ep = readdir(dp);
  }

  rewinddir(dp);
  *ls = calloc(count, sizeof(char *));

  count = 0;
  ep = readdir(dp);
  while (NULL != ep) {
    // omit . and .. in list dir
    if (!strcmp(ep->d_name, ".") == 0 && !strcmp(ep->d_name, "..") == 0) {
      (*ls)[count++] = strdup(ep->d_name);
    }
    ep = readdir(dp);
  }

  closedir(dp);
  return count;
}