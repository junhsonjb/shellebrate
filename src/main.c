/* Ain't no party like a Holy Ghost party, because a Holy Ghost party don't stop! */
#define SHELL_RL_BUFSIZE 1024
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int lsh_launch(char ** args) {

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

int main(int argc, char** argv) {

    // Call the loop function to get this party started!
    shellebrate_loop();

    // Leave that party like a boss
    return EXIT_SUCCESS;

}
