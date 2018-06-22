/* Ain't no party like a Holy Ghost party, because a Holy Ghost party don't stop! */
#define SHELL_RL_BUFSIZE 1024

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

        if (c == 'EOF' || c == '\n') {

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

void shellebrate_loop(void) {

    // A few declarations to start the party!
    char * line; // store the entered line here
    char ** args; // store the list of args here
    int status;

    do {

        printf(">"); // print a little arrow so the user knows where to enter commands
        line = shell_read(); // read the entered line
        args = shell_split(); // split the input into arguments
        status = shell_execute(); // do that thing!

        // Free up a little bit of space.
        free(line);
        free(args);

    } while(status);

}

int main(int argc, char** argv) {

    // Call the loop function to get this party started!
    shellebrate_loop();

    // Leave that party like a boss
    exit(EXIT_SUCCESS);

}
