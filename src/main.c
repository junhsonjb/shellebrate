

void shellebrate_loop(void) {

    char * line;
    char ** args;
    int status;

    do {

        printf(">")
        line = shell_read();
        args = shell_split();
        status = shell_execute();

        free(line);
        free(args);

    } while(status);

}

int main(int argc, char** argv) {

    // Call the loop function to get this party started!
    shellebrate_loop();

    return EXIT_SUCCESS

}
