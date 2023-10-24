// ..
// ....
// ...... tripc/src/main.c
// ....
// ..

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../lib/err.h"

// ANSI escape codes for text color
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_RESET "\033[0m"

// Clear screen and position cursor at (0, 0)
#define ASCII_CLEAR_SCREEN "\033[H\033[J"

#define GRID_SIZE 2
#define WINDOW_HEIGHT (4 * GRID_SIZE)
#define WINDOW_WIDTH (4 * GRID_SIZE)
#define FPS 8 // iterations of FPS * 10 is sweep spot. 8 * 10
#define FPS_DELAY (1000000 / FPS) // Delay for the desired frame rate

static struct {
        bool verbose;
        char *output_file;
        char **words;
        size_t words_count;
} cli;

err_t parse_args(int argc, char *argv[]) {
        if (cli.verbose)
                LOG(LOG_INFO, ERR_OK, "argc %i", argc);
        for (size_t i = 1; i < argc; i += 1) {
                if (strcmp(argv[i], "--verbose") == 0 ||
                    strcmp(argv[i], "-v") == 0) {
                        cli.verbose = true;
                } else if (strcmp(argv[i], "--output") == 0 ||
                           strcmp(argv[i], "-o") == 0) {
                        if (i + 1 < argc) {
                                cli.output_file = argv[i + 1];
                                i += 1; // Consume the next argument.
                        } else {
                                LOG(LOG_ERROR, ERR_FAIL,
                                    "Missing arguments for --output option.");
                                return ERR_FAIL;
                        }
                } else {
                        char *opt = argv[i];
                        if (strlen(opt) != 3) {
                                LOG(LOG_ERROR, ERR_FAIL,
                                    "opt[%d] is not of 3 chars %s", i, opt);
                                return ERR_FAIL;
                        }
                        if (cli.words_count < 2) {
                                cli.words[cli.words_count] = strdup(opt);
                                cli.words_count += 1;
                        } else {
                                LOG(LOG_ERROR, ERR_FAIL,
                                    "Too many 3-letter words provided.");
                                return ERR_FAIL;
                        }
                }
        }
        return ERR_OK;
};

// ..
// ....
// ......
// ....
// ..

void renderFrame(size_t frame) {
        printf(ASCII_CLEAR_SCREEN);

        char *wrd1 = cli.words[0];
        char *wrd2 = cli.words[1];
        char *w1 = (wrd1 != NULL && strlen(wrd1) == 3) ? wrd1 : "hey";
        char *w2 = (wrd2 != NULL && strlen(wrd2) == 3) ? wrd2 : "you";

        for (size_t y = 1; y <= WINDOW_HEIGHT; y++) {
                printf("\n");
                for (size_t x = 1; x <= WINDOW_WIDTH; x++) {
                        size_t value = (size_t)((x * y + frame) % 2);
                        if (value == 0)
                                printf(COLOR_MAGENTA "%s" COLOR_RESET, w1);
                        else if (value == 1)
                                printf(COLOR_BLUE "%s" COLOR_RESET, w2);
                }
        }
        fflush(stdout);
        usleep(FPS_DELAY);
}

int main(int argc, char *argv[]) {
        time_t start = clock();

        cli.verbose = 0;
        cli.output_file = NULL;
        cli.words_count = 0;

        cli.words = calloc(sizeof(char *), argc);
        if (cli.words == NULL) {
                LOG(LOG_ERROR, ERR_FAIL, "Failed to allocate memory for words");
                return ERR_FAIL; // or return 1
        }

        err_t err_parse = parse_args(argc, argv);
        if (err_parse != ERR_OK) {
                LOG(LOG_ERROR, err_parse, "Failed to parse input arguments");
                return err_parse; // or return 1
        }

        if (cli.verbose)
                printf("$ sine\n");
        if (cli.words_count > 0)
                assert(cli.words_count <= argc);

        int iterations = FPS * 10;
        for (size_t frame = 0; frame < iterations; frame++)
                renderFrame(frame);

        if (cli.verbose && cli.output_file) {
                printf("Output file is set to %s.\n", cli.output_file);
                // TODO: implement opening the output file and writing to it
        }

        for (size_t i = 0; i < cli.words_count; i += 1)
                if (cli.words[i] != NULL)
                        free(cli.words[i]);
        if (cli.words != NULL)
                free(cli.words);

        time_t end = clock();
        if (cli.verbose) {
                double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
                printf("\n\n");
                printf("Stats for workspace 1 (\"Debug\"):\n");
                printf("iterations:           %14i.\n", iterations);
                printf("FPS:                  %14i.\n", FPS);
                printf("Frames Per Second:    %14d.\n", 1000000 / FPS);
                printf("Total time: %16.6f seconds.\n", elapsed);
                printf("\n");
        }

        return ERR_OK;
}

// ..
// ....
// ......
// ....
// ..
