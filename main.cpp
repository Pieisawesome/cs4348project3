// Lana Tran | LXT210009
// CS 4348 Project 3
// Due May 9th, 2025

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <filesystem>
#include <fstream>

void createIndex(char *indexFile){
    std::ofstream file;
    file.open(indexFile);
}

void insertIndex(char *indexFile, char *key, char *value){

}

void searchIndex(char *indexFile, char *key);
void loadIndex(char *indexFile, char *csvFile);
void printIndex(char *indexFile);
void extractIndex(char *indexFile, char *csvFile);

void menu(){
    printf("CREATE:\t create <indexFile>\n");
    printf("INSERT:\t insert <indexFile> <key> <value>\n");
    printf("SEARCH:\t search <indexFile> <key>\n");
    printf("LOAD:\t load <indexFile> <csvFile>\n");
    printf("PRINT:\t print <indexFile>\n");
    printf("EXTRACT: extract <indexFile> <csvFile>\n");
}

// Returns -1 if extension is incorrect
// Returns 0 if extension is .idx
// Returns 1 if extension is .csv
int findExtension(char *fileName){
    char *ext = strrchr(fileName, '.');
    if (ext == NULL){
        return -1;
    }

    if (strcmp(ext, ".idx") == 0){
        return 0;
    }

    else if (strcmp(ext, ".csv") == 0){
        return 1;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    
    if (argc <= 1 || argc > 5){
        printf("Valid Arguments:\n");
        menu();
        return 1;
    }


    // CREATE
    if (strcmp(argv[1], "create") == 0){
        if (argc != 3){
            printf("Invalid Arguments.\n\n");
            return 1;
        }
        
        // Check if the file extension is .idx
        if (findExtension(argv[2]) != 0){
            printf("Invalid file extension. Must be .idx\n\n");
            return 1;
        }

        // Part of <filesystem> library
        // Returns true if the file exists
        if (std::filesystem::exists(argv[2])){
            printf("File already exists.\n\n");
            return 1;
        }

        createIndex(argv[2]);
        return 0;
    }


    // Apart of all other commands
    // Part of <filesystem> library
    // Returns true if the file exists
    if (!std::filesystem::exists(argv[2])){
        printf("File does not exist.\n\n");
        return 1;
    }
    
    // INSERT
    if (strcmp(argv[1], "insert") == 0){
        if (argc != 5){
            printf("Invalid Arguments.\n\n");
            return 1;
        }

        insertIndex(argv[2], argv[3], argv[4]);
        return 0;
    }

    // SEARCH
    if (strcmp(argv[1], "search") == 0){
        if (argc != 4){
            printf("Invalid Arguments.\n\n");
            return 1;
        }

        searchIndex(argv[2], argv[3]);
        return 0;
    }

    // LOAD
    if (strcmp(argv[1], "load") == 0){
        if (argc != 4){
            printf("Invalid Arguments.\n\n");
            return 1;
        }

        loadIndex(argv[2], argv[3]);
        return 0;
    }

    // PRINT
    if (strcmp(argv[1], "print") == 0){
        if (argc != 3){
            printf("Invalid Arguments.\n\n");
            return 1;
        }

        printIndex(argv[2]);
        return 0;
    }

    // EXTRACT
    if (strcmp(argv[1], "extract") == 0){
        if (argc != 4){
            printf("Invalid Arguments.\n\n");
            return 1;
        }

        extractIndex(argv[2], argv[3]);
        return 0;
    }


}