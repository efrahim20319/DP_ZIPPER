#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
     //flags
    char * username, * usernumer , * usernames, * usernumers;
    username = usernumer = usernames = usernumers = NULL;
    int i = 0;
    for ( i = 0; i < argc; i++)
    {
        //Need to be refactored
        if (strcmp("--username", argv[i]) == 0) {
            username = argv[i+1];
            continue;
        }
        if (strcmp("--usernumber", argv[i]) == 0) {
            usernumer = argv[i+1];
            continue;
        }
        if (strcmp("--usernames", argv[i]) == 0) {
            usernames = argv[i+1];
            continue;
        }
        if (strcmp("--usernumbers", argv[i]) == 0) {
            usernumers = argv[i+1];
            continue;
        }
    }
    printf("[username: %s]\n[usernumber: %s]\n[usernames: %s]\n[usernumers: %s]\n", username, usernumer, usernames, usernumers);
    system("find * -maxdepth 0 -type d > .dp-zipper-files");
    FILE * fp = fopen(".dp-zipper-files", "r");
    char fileName[100];
    if (fp != NULL) { 
         while (fscanf(fp, "%s", fileName) != EOF) {
            if (strcmp(fileName, "src")  == 0) {
                printf("Find It");
            }
        }
    }
    fclose(fp);
    return 0;
}
