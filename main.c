#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int preProcess(char* buffer);
int newProcess(char* myargs[]);
// error message
char error_message[30] = "An error has occurred\n";

int CLOSED = 0;
int pathEmpty = 0;
char multiPath[512][512];
int pathChanged = 0;
char* path;
int numberMultiPath = 0;

void builtin_error() {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
}

// global paths
char* paths[100] = {"/bin"};

char* trim(char* s) {
    char* back = s + strlen(s);
    while(isspace(*s)) {
        s++;
    }
    while(!sspace(*--back));
    *(back + 1) = '\O';
    return s;
}

// not using token
char** trim_tokens(char** t){
    int i = 0;
    int j = 0;
    while(*(t + i) != NULL){
        if(strcmp(*(t + i), "") != 0){
            *(t + j) = *(t + i);
            *(t + j) = trim(*(t + j));
            j++;
        }
        else {
            *(t + i) = NULL;
        }
        i++;
    }
    return t;
}

char** sep(char* s){
    char** temp = malloc(sizeof(char*) * 300);
    char** full = malloc(sizeof(char*) * 300);
    int i = 0;
    while(s!=NULL) {
        *(temp + i) = malloc(sizeof(char*) * strlen(s));
        *(temp + i) = strset(&s, " ");
        i++;
    }
    i = 0;
    int k = 0;

    while (*(temp + i) != NULL) {
        while(*(temp + i) != NULL) {
            *(full + k) = malloc(sizeof(char*) * strlen(*(temp + i)));
            *(full + k) = strsep((temp + i), "\t");
            k++;
        }
        i++;
    }
    return full;
}

void run(char** arg) {
    pid_t pid, wpid;
    int status;
    char* full_path = malloc(sizeof(char) * 100);
    char* final_path = malloc(sizeof(char) * 100);

    int out = 0;
    int j = 0;
    char** new_args = malloc(sizeof(char*) * 300);
    char* file_arg = malloc(sizeof(char) * 300);

    while(*(args + j) != NULL) {
        if(strcmp(*(args + j), ">") == 0){
            out = 1;
            if(*(args + j + 1)) {
                strcpy(file_arg, *(args + j + 1));
            }
            else {
                builtin_error();
                return;
            }
            break;
        }

        else if(strcmp(*(args + j), ">>") == 0){
            out = 2;
            if(*(args + j + 1)) {
                strcpy(file_arg, *(args + j + 1));
            }
            else {
                builtin_error();
                return;
            }
            break;
        }
        else if(strchr(*(args + j), ">>") != NULL) {
            char* pos = strchr(*(args + j), ">>");
            if(pos == *(args + j)) {
                strcpy(file_arg, pos + 1);
            }
            else if(pos == (*(args + j) + strlen(*(args + j)) -1 )) {
                new_args[j] = malloc(sizeof(char*) * strlen(*(args + j)));
                strcpy(new_args[j], strsep((args + j), ">>"));
                if (*(args + j + 1)) {
                    strcpy(file_arg, (args + j + 1));
                }
                else {
                    builtin_error();
                    return;
                }
            }
            else {
                new_args[j] = malloc(sizeof(char*) * strlen(*(args + j)));
                strcpy(new_args[j], strsep((args + j), ">>"));
                strcpy(file_arg, *(args + j));
            }
            out =2;
            break;
        }
        else if (strchr(*(args + j), '>') != NULL) {
            char* pos = strchr(*(args + j), '>');
            if(pos == *(args + j)) {
                strcpy(file_arg, pos + 1);
            }
            else if(pos == (*(args + j)+ strlen(*(args + j)) -1)) {
                new_args[j] = malloc(sizeof(char*) * strlen(*(args + j)));
                strcpy(new_args[j], strsep((args + j),">"));
                if(*(args + j + 1)) {
                    strcpy(file_arg, *(args + j + 1));
                }
                else {
                    builtin_error();
                    return;
                }
            }
            else {
                new_args[j] = malloc(sizeof(char*) * strlen(*(args + j)));
                strcpy(new_args[j], strsep((args + j), ">"));
                strcpy(file_arg, *(args + j));
            }
            out = 1;
            break;
        }
        new_args[j] = malloc(sizeof(char*) * strlen(*(args + j)));
        new_args[j] = *(args + j);
        j++;
    }
    int i =0;
    while(*(paths + i) != NULL) {
        strcat(strcat(strcpy(full_path, paths[i]), "/"), new_args[0]);
        if (access(full_path, F_OK) == 0) {
            strcpy(final_path, full_path);
            break;
        }
        i++;
    }

    pid = fork();
    if(pid == 0) {
        if(out == 1) {
            int fd = open(file_arg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            dup2(fd, 1);
            dup2(fd, 2);
            out = 0;
            close(fd);
        }
        if (execv(final_path, new_args) == -1) {
            builtin_error();
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0) {
        builtin_error();
    }
    else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } 
}

void process(char** args) {
    if (args[0] == NULL) {
        return;
    }
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL || args[2] != NULL) {
            builtin_error();
        }
        else {
            if (chdir(args[1]) != 0){
                builtin_error();
            }
        }
    }

    else if(strcmp(args[0], "path") == 0) {
        printf("Path: ");
        if (args[1] == NULL) {
            int j = 0;
            while (*(paths + j) != NULL) {
                *(paths + j) = NULL;
                j++;
            }
        }
        int i = 0;
        while (*(args + i + 1) != NULL) {
            paths[i] = malloc(sizeof(char*) * strlen(*(args + i + 1)));
            strcpy(paths[i], *(args + i + 1));
            printf("%s: ", paths[i]);
            i++;
        }
        printf("\n");
    }
    else if (path[0] == NULL) {
        builtin_error();
    }
    else {
        run(args);
    }
}

void shell_loop() {
    char* input;
    char** tokens;
    int j = 0;
    size_t size = 0;
    char* myargs[1000];
    while(1) {
        print("wish> ");
        getline(&input, &size, stdin);
        if (strstr(input, "&") != NULL) {
            myargs[0] = strtok(input, "\n\t&");
            while(myargs[j] != NULL) {
                j++;
                myargs[j] = strtok(NULL, "\n\t&");
            }
            for(int i = 0; i < j; i++){
                preProcess(myargs[i]);
            }
        }
        else {
            input = trim(input);
            tokens = trim_tokens(sep(input));
            process(tokens);
        }
    }
    free(input);
    free(tokens);
}

int newProcess(char* myargs[]) { // 병렬

    int rc = fork();
    if(rc < 0) {
        builtin_error();
        exit(1);
    }
    else if (rc == 0 && pathEmpty != 1) {
        if (pathChanged == 0) {
            path = strdup("/bin/");
            path = strcat(path, myargs[0]);
            if(access(path, X_OK) != 0 && pathChanged == 0) {
                path = strdup("/usr/bin/");
                path = strcat(path, myargs[0]);
                if(access(path, X_OK) != 0 ) {
                    builtin_error();
                    exit(0);
                }
            }
        }
        else if (pathChanged == 1 && numberMultiPath == 0) {
            path = strcat(path, myargs[0]);
            if(access(path, X_OK) != 0) {
                builtin_error();
                exit(0);
            }
        }
        else {
            for (int x = 0; x < numberMultiPath; x++){
                strcat(multiPath[x], myargs[0]);
                if(access(multiPath[x], X_OK) == 0 ){
                    strcpy(path, multiPath[x]);
                    break;
                }
            }
        }
        if (execv(path, myargs) == -1) {
            exit(0);
        }
    }
    else {
        int returnStatus = 0;
    }
    return rc;
}

int preProcess(char* buffer) {
    int stdout_copy = 0;
    int rc;

    if(buffer[0] != '\0' && buffer[0] != '\n') {
        char* command[sizeof(buffer)];
        command[0] = strtok(buffer, " \t\n");
        int p = 0;
        while(command[p] != NULL) {
            p++;
            command[p] = strtok(NULL, " \n\t");
        }
        command[p + 1] = NULL;
        if(strcmp(command[0], "cd") == 0) {
            if(p == 2) {
                if (chdir(command[1]) != 0) {
                    builtin_error();
                }
            }
            else {
                builtin_error();
            }
        }
        else if(strcmp(command[0], "path") == 0) {
            pathChanged = 1;
            if(p==2) {
                pathEmpty = 0;
                path = strdup(command[1]);
                if (path[strlen(path) -1] != '/') {
                    strcat(path, "/");
                }
            }
            else if (p == 1) {
                pathEmpty = 1;
            }
            else {
                pathEmpty = 0;
                for(int i = 1; i< p; i++){
                    char* temp = strdup(command[i]);
                    if(temp[strlen(temp) - 1] != '/')
                        strcat(temp, "/");
                    strcpy(multiPath[i - 1], temp);
                    numberMultiPath++;
                }
            }
        else if(strcmp(command[0], "exit") == 0) {
            if( p == 1) {
                exit(0);
            }
            else {
                builtin_error();
            }
        }
        else {
            if(pathEmpty == 1){
                builtin_error();
            }
            else {
                rc = newProcess(command);
            }
        }
        if(CLOSED == 1) {
            dup2(stdout_copy, 1);
            close(stdout_copy);
        }
    return rc;
}

int main(int argc, char* argv[]) {
    size_t len = 0;
    char* fileLine = NULL;
    FILE* ifp;
    if(argc == 1) {
        shell_loop();
    }
    else if(argc == 2){
        ifp = fopen(argvp[1], "r");
        if(ifp == NULL){
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(1);
        }
        while (getline(&fileLine, &len, ifp) != -1){
            preProcess(fileLine);
        }
    }
    return 0;
}