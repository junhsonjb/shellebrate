/* Ain't no party like a Holy Ghost party, because a Holy Ghost party don't stop! */

// Some preprocessor definitions and includes
#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* Declarations of built-in shell command functions */
int shell_cd(char ** args);
int shell_help(char ** args);
int shell_exit(char ** args);

/* Declarations of the rest of the functions */
int shell_num_builtins();
int shell_execute(char ** args);
char * shell_read();
char ** shell_split(char * line);
int shell_launch(char ** args);
void shellebrate_loop(void);

/* ========= STUFF FOR BUILT IN COMMANDS ========= */

/* List of built-in commands */
char * builtins_string[] = {
    "shell_cd",
    "shell_help",
    "shell_exit"
};

/* List of build-in command function pointers */
int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

/* Get the number of buil in commands */
int shell_num_builtins() {
    return sizeof(builtins_string) / sizeof(char *);
}

/* Actual Definitions of built-in functions */

// cd function
int shell_cd(char ** args) {

    if (args[1] == NULL) {
        fprintf(stderr, "shellebrate: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }

    return 1;

}

// help function
int shell_help(char ** args) {

    printf("Welcom to Shellebrate! A shell by Junhson Jean-Baptiste.\n");
    printf("Type in a program name and it's necessary arguments.\n");
    printf("Here are the built in commands: \n");
    for (int i = 0; i < shell_num_builtins(); i++) {

        printf("  %s\n", builtins_string[i]);

    }
    

    return 1;

}

// exit function
int shell_exit(char ** args) {
    return 0;
}

/* ========= END OF STUFF FOR BUILT IN COMMANDS ========= */

/* ========= THE GOOD STUFF ========= */

/* Our main function */
int main(int argc, char** argv) {

    // Call the loop function to get this party started!
    shellebrate_loop();

    // Leave that party like a boss
    return EXIT_SUCCESS;

}

void shellebrate_loop(void) {

    // A few declarations to start the party!
    char * line; // store the entered line here
    char ** args; // store the list of args here
    int status;

    do {

        printf(">"); // print a little arrow so the user knows where to enter commands
        line = shell_read(); // read the entered line
        args = shell_split(line); // split the input into arguments
        status = shell_execute(args); // do that thing!

        // Free up a little bit of space.
        free(line);
        free(args);

    } while(status);

}

char * shell_read() {

    int bufsize = SHELL_RL_BUFSIZE;
    int position = 0;
    char * buffer  = (char *) malloc(bufsize * sizeof(char));
    int c;

    // If for some reason buffer comes out NULL print an error and exit with failure
    if (!buffer) {
        fprintf(stderr, "Shellebration: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {

        c = getchar();

        if (c == EOF || c == '\n') {

            buffer[position] = '\0';
            return buffer;

        } else {

            buffer[position] = c;

        }

        position++;

        if (position >= bufsize) {

            bufsize += SHELL_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer) {
                fprintf(stderr, "Shellebration: allocation error\n");
                exit(EXIT_FAILURE);
            }

        }

    }

}

char ** shell_split(char * line) {

    int bufsize = SHELL_TOK_BUFSIZE;
    int position = 0;
    char ** tokens = (char **) malloc(bufsize * sizeof(char *));
    char * token;

    if (!tokens) {
        fprintf(stderr, "Shellebration: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);

    while (token != NULL) {

        tokens[position] = token;
        position++;

        if (position >= bufsize) {

            bufsize += SHELL_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens) {
                fprintf(stderr, "Shellebration: allocation error\n");
                exit(EXIT_FAILURE);
            }

        }

        token = strtok(NULL, SHELL_TOK_DELIM);

    }

    // Null terminate the list of char *s (strings)
    tokens[position] = NULL;
    return tokens;

}

int shell_execute(char ** args) {

    // Handle empty commands
    if (args[1] == NULL) {
        return 1;
    }

    // Check if the command is one of the builtin in ones and handle it if so
    for (int i = 0; i < shell_num_builtins(); i++) {

        if ( strcmp(args[0], builtins_string[i]) == 0 ) {
            return (* builtin_func[i]) (args);
        }

    }

    // Otherwise return the program command (not built in) that was called
    return shell_launch(args);

}

int shell_launch(char ** args) {

    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {

        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }

        exit(EXIT_FAILURE);

    } else if (pid < 0) {

        perror("lsh");

    } else {

        do {

            wpid = waitpid(pid, &status, WUNTRACED);

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    }

    return 1;

}

/* ========= LE FIN ========= */
