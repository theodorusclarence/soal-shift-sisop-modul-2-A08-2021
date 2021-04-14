#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void getTime(char *string);
void cipher(char *string);

int main() {
    // char temp[30];
    // getTime(temp);
    // printf("%s", temp);

    // char temp[30] = "Download Success";
    // cipher(temp);
    // printf("%s", temp);
    long int imageSize = time(NULL) % 1000 + 50;

    char namaFile[50];
    char linkDownload[100];
    pid_t child_id3;
    int status3, i;

    for (i = 0; i < 2; i++) {
        getTime(namaFile);
        long int imageSize = time(NULL) % 1000 + 50;
        snprintf(linkDownload, sizeof(linkDownload),
                 "https://picsum.photos/%ld", imageSize);

        child_id3 = fork();
        if (child_id3 == 0) {
            // char *argv[] = {"wget", "-O", namaFile, linkDownload, NULL};
            // execv("/usr/bin/wget", argv);

            char *argv[] = {"touch", "hello", NULL};
            execv("/bin/touch", argv);
        }
        printf("%s, %s \n", linkDownload, namaFile);
        sleep(5);
    }

    return 0;
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
void cipher(char *message) {
    char ch;
    int key = 5;

    for (int i = 0; message[i] != '\0'; ++i) {
        ch = message[i];

        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;

            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }

            message[i] = ch;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = ch + key;

            if (ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }

            message[i] = ch;
        }
    }
}
