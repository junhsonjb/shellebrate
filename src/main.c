/* Ain't no party like a Holy Ghost party, because a Holy Ghost party don't stop! */

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
    return EXIT_SUCCESS

}
