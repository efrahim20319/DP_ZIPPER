#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>

void displayFlags(char *username, char *usernumber, char *usernames, char *usernumbers, int rezip, int logFlags, int openExplorer)
{
    printf("[username: %s]\n[usernumber: %s]\n[usernames: %s]\n[usernumers: %s]\n", username, usernumber, usernames, usernumbers);
    printf("[rezip: ");
    rezip ? printf("True]\n") : printf("False]\n");
    printf("[logFlags: ");
    logFlags ? printf("True]\n") : printf("False]\n");
    printf("[openExplorer: ");
    openExplorer ? printf("True]\n") : printf("False]\n");
}

void readFlags(int numberOfArguments, char *arguments[], char *username,
               char *usernumber, char *usernames, char *usernumbers, int *rezip, int *logFlags, int * openExplorer)
{
    int i = 0;
    for (i = 0; i < numberOfArguments; i++)
    {
        // Needs to be refactored
        if (strcmp("--username", arguments[i]) == 0)
        {
            strcpy(username, arguments[i + 1]);
            continue;
        }
        if (strcmp("--usernumber", arguments[i]) == 0)
        {
            strcpy(usernumber, arguments[i + 1]);
            continue;
        }
        if (strcmp("--usernames", arguments[i]) == 0)
        {
            strcpy(usernames, arguments[i + 1]);
            continue;
        }
        if (strcmp("--usernumbers", arguments[i]) == 0)
        {
            strcpy(usernumbers, arguments[i + 1]);
            continue;
        }
        if (strcmp("--rezip", arguments[i]) == 0 || strcmp("-r", arguments[i]) == 0)
        {
            *rezip = 1;
            continue;
        }
        if (strcmp("--log", arguments[i]) == 0 || strcmp("-l", arguments[i]) == 0)
        {
            *logFlags = 1;
            continue;
        }
        if (strcmp("--explorer", arguments[i]) == 0 || strcmp("-r", arguments[i]) == 0)
        {
            *openExplorer = 1;
            continue;
        }
    }
}

int findFolder(char *folderToFind)
{
    system("find * -maxdepth 0 -type d > .dp-zipper-files");
    FILE *fp = fopen(".dp-zipper-files", "r");
    char folderName[50];
    if (fp != NULL)
    {
        while (fscanf(fp, "%s", folderName) != EOF)
        {
            if (strcmp(folderName, folderToFind) == 0)
            {
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

int main(int argc, char const *argv[])
{
    // flags
    char username[100] = "", usernumber[100] = "", usernames[100] = "", usernumbers[100] = "";
    int hasTheSRCFolder = 0;
    int rezip = 0, *pt_rezip = &rezip;
    int logFlags = 0, *pt_logFlags = &logFlags;
    int openExplerer = 0, * pt_openExplerer = &openExplerer;
    readFlags(argc, argv, username, usernumber, usernames, usernumbers, pt_rezip, pt_logFlags, pt_openExplerer);
    displayFlags(username, usernumber, usernames, usernumbers, rezip, logFlags, openExplerer);
    hasTheSRCFolder = findFolder("src");
    if (rezip && hasTheSRCFolder)
    {
        system("zip -r SAMPLE src AUTHORS.txt");
    }
    if (hasTheSRCFolder)
    {
        FILE *fp = NULL;
        printf("Source folder found\n");
        fp = fopen("AUTHORS.txt", "w");
        fprintf(fp, "a%s;%s", usernumber, username);
        fclose(fp);
        system("zip -r SAMPLE src AUTHORS.txt");
    }
    else
    {
        printf("Couldn't find the source folder!!!");
    }
    if (openExplerer) {
        system("explorer.exe .");
    }
    return 0;
}
