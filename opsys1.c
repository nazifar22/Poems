//Nazifa Nazrul Rodoshi - w8czne

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define DATA_FILE "poems.txt"

int getPoemCount() {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) return 0;

    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        count++;
    }

    fclose(file);
    return count;
}

void addPoem() {
    char title[256], content[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];
    printf("Enter poem title: ");
    scanf(" %[^\n]", title);
    getchar(); 
    printf("Enter poem content (use ';' as a newline): ");
    scanf(" %[^\n]", content);
    getchar(); 

    for (char *p = content; *p; ++p) {
        if (*p == ';') *p = '\n';
    }

    FILE *file = fopen(DATA_FILE, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int id = getPoemCount() + 1;
    fprintf(file, "{ \"id\": %d, \"title\": \"%s\", \"content\": \"%s\" }\n", id, title, content);

    fclose(file);
    printf("Poem added successfully.\n");
}

void listPoems() {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void deletePoem(int id) {
    FILE *file = fopen(DATA_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"id\": ") && atoi(strstr(line, "\"id\": ") + 6) == id) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    if (found) {
        printf("Poem with ID %d deleted successfully.\n", id);
    } else {
        printf("Poem with ID %d not found.\n", id);
    }
}

void modifyPoem(int id) {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"id\": ") && atoi(strstr(line, "\"id\": ") + 6) == id) {
            found = 1;
            char newTitle[256], newContent[MAX_LINE_LENGTH], modifiedLine[MAX_LINE_LENGTH];
            printf("Enter new poem title: ");
            scanf(" %[^\n]", newTitle);
            getchar();
            printf("Enter new poem content (use ';' as a newline): ");
            scanf(" %[^\n]", newContent);
            getchar();

            for (char *p = newContent; *p; ++p) {
                if (*p == ';') *p = '\n';
            }

            snprintf(modifiedLine, sizeof(modifiedLine), "{ \"id\": %d, \"title\": \"%s\", \"content\": \"%s\" }\n", id, newTitle, newContent);
            fputs(modifiedLine, tempFile);
            continue;
        }

        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(DATA_FILE);
        rename("temp.txt", DATA_FILE);
        printf("Poem with ID %d modified successfully.\n", id);
    } else {
        remove("temp.txt");
        printf("Poem with ID %d not found.\n", id);
    }
}


int main() {
    int choice, id;
    do {
        printf("\nPoem Database\n");
        printf("1. Add Poem\n");
        printf("2. List Poems\n");
        printf("3. Delete Poem\n");
        printf("4. Modify Poem\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPoem();
                break;
            case 2:
                listPoems();
                break;
            case 3:
                printf("Enter Poem ID to delete: ");
                scanf("%d", &id);
                deletePoem(id);
                break;
            case 4:
                printf("Enter Poem ID to modify: ");
                scanf("%d", &id);
                modifyPoem(id);
                break;
            case 5:
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}