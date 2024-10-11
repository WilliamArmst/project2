#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

unsigned int getSize(char* string) {
    unsigned int size = 0;
    while (string[size] != '\0') {
        size++;
    }

    return size + 1;
}

//make directory
void mkdir(char pathName[]){

    unsigned int size = getSize(pathName); // initialize variable for splitPath function
    char* name = (char*)malloc (size * sizeof(char));
    char* dir = (char*)malloc (size * sizeof(char));   
    
    struct NODE* currNode = splitPath(pathName, name, dir); // get current node and delete dir info 
    free(dir);

    struct NODE* newNode = (struct NODE*)malloc (sizeof(struct NODE));
    strcpy(newNode->name, name);
    newNode->fileType = 'D';
    newNode->parentPtr = currNode;    

    if (currNode->childPtr) {
        currNode = currNode->childPtr;

        if (strcmp(currNode->name, name) == 0) {
            free(name);
            free(newNode);
            printf("MKDIR ERROR: directory %s already exists\n",pathName);
            return;
        }

        while (currNode->siblingPtr) {
            currNode = currNode->siblingPtr;
        }

        currNode->siblingPtr = newNode;
    } else {    
        currNode->childPtr = newNode;
    }

    free(name);
    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // get pathName size
    unsigned int size = getSize(pathName);

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
    dirName[i + 1] = '\0';

    if (size != slashPos) { // skip the slash if it's there
        i++;
    }

    int j;
    for (j = 0; i < size; j++) { // continue loop to get base name, everything until the end
        baseName[j] = pathName[i];
        i++;
    }
    baseName[j + 1] = '\0';

    struct NODE* currentDir = cwd; 

    char* path = (char*)malloc (size * sizeof(char));
    
    j = 0;
    for (int i = 0; pathName[i] != '\0'; i++) {
        if (pathName[i] == '/') {
            path[j] = '\0';
           
            currentDir = currentDir->childPtr;
            if (!currentDir) {
                free(path);
                printf("ERROR: directory %s does not exist\n", path); // ToDo: path should be full directory
                return NULL;
            }

            if (currentDir->name == path) {
                continue;
            }
        
            while (currentDir->siblingPtr) {
                currentDir = currentDir->siblingPtr;
                if (currentDir->name == path) {
                    break;
                }
            }

            if (currentDir->name != path) {
                free(path);
                printf("Error: directory %s does not exist\n", path); // ToDo: path should be full directory                
                return NULL;
            }

            j = 0;
        } else {
            path[j] = pathName[i];
            j++;
        }
    }

    free(path);

    // get node to return
    

    return currentDir;
}

