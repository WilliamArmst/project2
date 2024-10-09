#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    printf("TO BE IMPLEMENTED\n");

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // get pathName size
    unsigned int size = 0;
    while (pathName[size] != '\0') {
        size++;
    }

    // handle edge cases
    if (size == 0) {
        dirName[0] = '/';
        return root;
    }

    int slashPos = size; // from the end
    
    for (int i = size - 1; i >= 0; i--) {
        if (pathName[i] == '/') { // mark the location of the first slash and break
            slashPos = -(i - size);
            break;
        } 
    }

    int i;
    // hopefully memory management is done in the other parts?
    // dirName = (char*)malloc ((size - slashPos) * sizeof(char));
    // baseName = (char*)malloc (slashPos * sizeof(char));

    dirName[0] = '\0';
    baseName[0] = '\0';

    for (i = 0; i < size - slashPos; i++) { // get the directoy name, everything until the slash if there is one
        dirName[i] = pathName[i]; 
    }

    if (size != slashPos) { // skip the slash if it's there
        i++;
    }

    for (int j = 0; i < size; j++) { // continue loop to get base name, everything until the end
        baseName[j] = pathName[i];
        i++;
    }

    printf("%s\n",dirName);
    printf("%s\n",baseName);

    if (dirName[0] == '\0') {
        return cwd;
    }

    struct NODE* currentDir = cwd;

    return currentDir;
}

