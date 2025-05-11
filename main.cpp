// Lana Tran | LXT210009
// CS 4348 Project 3
// Due May 9th, 2025

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdint>

// Functions -------------------------------------------------

// Returns 1 if file is created successfully
//         0 in error
bool createIndex(int argc, char *argv[]){

    // Checks 
    if (argc != 3){
        printf("Invalid Arguments.\n\n"); // Technically these are side affects and I should put them as error messages instead
        return 0;
    }
    if (findExtension(argv[2]) != 0){
        printf("Invalid file extension. Must be .idx\n\n");
        return 0;
    }
    if (std::filesystem::exists(argv[2])){
        printf("File already exists.\n\n");
        return 0;
    }

    // Create the file
    std::ofstream file(argv[2], std::ios::binary); // Opens in binary mode
    if (!file){
        printf("Error creating file.\n\n");
        return 0;
    }

    /* 
    Header
       • 8-bytes: The magic number “4348PRJ3” (as a sequence of ASCII values).
       • 8-bytes: The id of the block containing the root node. This field is zero if the tree is empty.
       • 8-bytes: The id of the next block to be added to the file. This is the next location for a new node.
       • The remaining bytes are unused.
    */
    uint8_t header[512] = {0}; // 512 bytes
    memcpy(header, "AAAAAAAA", 8); // Magic number??? How it is generated? Is it just "4348PRJ3"?
    writeToHelper(header, 8, 0);
    writeToHelper(header, 16, 1);

    // Write the header to the file
    file.write((char *)header, sizeof(header));
    file.close();
    return 1;
   
}

// Returns 1 if successful
//         0 if error
// Inserts key & value pair into index file
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

// Returns big endian
uint64_t toBigEndian(uint64_t value){
    uint64_t temp = 0;
    uint8_t *p = (uint8_t *)&value;
    uint8_t *q = (uint8_t *)&temp;
    for (int i = 0; i < 8; i++){
        q[i] = p[7 - i];
    }
    return temp;
}

// Helper function
// Writes to header at offset
void writeToHelper(uint8_t *header, int offset, uint64_t value){
    uint64_t bigEndianValue = toBigEndian(value);
    memcpy(header + offset, &bigEndianValue, sizeof(bigEndianValue));
}

int main(int argc, char *argv[]) {
    
    if (argc <= 1 || argc > 5){
        printf("Valid Arguments:\n");
        menu();
        return 1;
    }


    // CREATE
    if (strcmp(argv[1], "create") == 0){
        return (createIndex(argc, argv))?0:1;   // This is just a reverse of the return value 
    }                                           // Wanted the function to return 1 if successful
                                                // But main returns 0 if successful
    

    // Part of all other commands, so I just put the check here
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