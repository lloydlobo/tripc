#include <stdarg.h>
#include <stdio.h>

typedef int err_t;

enum err_ {
        ERR_OK = 0,    // no error
        ERR_FAIL = -1, // fail on error
};

const char *err_str(err_t e) {
        switch ((enum err_)e) {
        case ERR_OK:
                return "no-error";
        case ERR_FAIL:
                return "fail-on-error";
        }
        return "unknown error";
}

typedef enum {
        LOG_SUCCESS,
        LOG_INFO,
        LOG_ERROR,
        LOG_WARNING,
} LogLevel;

void set_text_color(LogLevel level) {
        switch (level) {
        case LOG_SUCCESS:
                printf("\033[1;32m"); // Bold green for success
                break;
        case LOG_INFO:
                printf("\033[1;34m"); // Bold blue for info
                break;
        case LOG_ERROR:
                printf("\033[1;31m"); // Bold red for error
                break;
        case LOG_WARNING:
                printf("\033[1;33m"); // Bold yellow for warning
                break;
        default:
                break;
        }
}

void reset_text_format() { printf("\033[0m"); }

// Function to handle different log levels
void log_message(const char *file, int line, LogLevel level, err_t err,
                 const char *format, ...) {
        set_text_color(level);
        printf("%s:%d: ", file, line);

        switch (level) {
        case LOG_SUCCESS:
                printf("success[%d]: ", err);
                break;
        case LOG_INFO:
                printf("info: ");
                break;
        case LOG_ERROR:
                printf("error[%d]: ", err);
                break;
        case LOG_WARNING:
                printf("warning[%d]: ", err);
                break;
        default:
                break;
        }

        reset_text_format();

        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);

        printf(" [");

        set_text_color(level);
        printf("\033[1m%s\033[0m", err_str(err));
        reset_text_format();

        printf("]\n");
}

#define LOG(level, err, format, ...)                                           \
        log_message(__FILE__, __LINE__, level, err, format)

// ..
// ....
// ......
// ....
// ..

// typedef int err_t;
// enum err_ {
//         ERR_OK = 0,    // no error
//         ERR_FAIL = -1, // fail on error
// };
// const char *err_str(err_t e) {
//         switch ((enum err_)e) {
//         case ERR_OK:
//                 return "no-error";
//         case ERR_FAIL:
//                 return "fail-on-error";
//         }
//         return "unknown error";
// }
//
// typedef enum {
//         LOG_SUCCESS,
//         LOG_INFO,
//         LOG_ERROR,
//         LOG_WARNING,
// } LogLevel;
// void set_text_color(LogLevel level) {
//         switch (level) {
//         case LOG_SUCCESS:
//                 printf("\033[1;32m"); // Bold green for success
//                 break;
//         case LOG_INFO:
//                 printf("\033[1;34m"); // Bold blue for info
//                 break;
//         case LOG_ERROR:
//                 printf("\033[1;31m"); // Bold red for error
//                 break;
//         case LOG_WARNING:
//                 printf("\033[1;33m"); // Bold yellow for warning
//                 break;
//         default:
//                 break;
//         }
// }
// void reset_text_format() { printf("\033[0m"); }
//
// // Function to handle different log levels
// void log_message(LogLevel level, err_t err, const char *format, ...) {
//         set_text_color(level);
//         printf("%s:%d:%d: ", __FILE__, __LINE__);
//
//         switch (level) {
//         case LOG_SUCCESS:
//                 printf("success[%d]: ",err);
//                 break;
//         case LOG_INFO:
//                 printf("info: ");
//                 break;
//         case LOG_ERROR:
//                 printf("error[%d]: ",err);
//                 break;
//         case LOG_WARNING:
//                 printf("warning[%d]: ",err);
//                 break;
//         default:
//                 break;
//         }
//
//         reset_text_format();
//         va_list args;
//         va_start(args, format);
//         vprintf(format, args);
//         va_end(args);
//
//         reset_text_format();
//
//         printf(" [");
//         set_text_color(level);
//         printf("\033[1m%s\033[0m", err_str(err));
//         reset_text_format();
//         printf("]\n");
// }
//
// #define LOG(level, err, format, ...) \
//         log_message(level, err, format, ##__VA_ARGS__)

// ..
// ....
// ......
// ....
// ..

// In C, if you want to make text bold when printing to the console, you
// typically need to use platform-specific escape codes for controlling text
// formatting. Since you didn't specify the platform you're working on, I'll
// provide an example for ANSI escape codes, which are commonly used in
// Unix-like systems (including Linux and macOS) to control text formatting.
//
// ANSI escape codes:
// - `\033[1;34m` sets the text color to bold blue.
// - `\033[1;32m` sets the text color to bold green.
// - `\033[0m` resets the text formatting to the default.
//
// TODO: determine current OS / platform with #ifdef..
// #define LOG(level, err, format, ...) do {
// \
// 	printf("\033[1;10m");
// \
// 	printf("%s:%d: ", __FILE__, __LINE__);
// \
// 	set_text_color(level); \
// 	printf("%s: ", level == LOG_INFO ? "info" : "error");
// \
// 	reset_text_format();
// \
// 	printf(format, ##__VA_ARGS__);
// \
// 	reset_text_format();
// \
// 	printf(" [");
// \
// 	set_text_color(level);
// \
// 	printf("%s", err_str(err));
// \
// 	reset_text_format();
// \
// 	printf("]");
// \
// 	printf("\n");
// \ } while (0)
//
// typedef enum {
// 	LOG_SUCCESS,
// 	LOG_INFO,
// 	LOG_ERROR,
// 	LOG_WARNING,
// } LogLevel;
//
// void set_text_color(LogLevel level){
// 	switch(level){
// 		case LOG_SUCCESS:
// 			printf("\033[1;32m"); // Bold green for success
// 		break;
// 		case LOG_INFO:
// 			printf("\033[1;34m"); // Bold blue for info
// 		break;
// 		case LOG_ERROR:
// 			printf("\033[1;31m"); // Bold red for error
// 		break;
// 		case LOG_WARNING:
// 			printf("\033[1;33m"); // Bold yellow for error
// 		break;
// 		default:
// 		break;
// 	}
// }
//
// void reset_text_format(){
// 	printf("\033[0m");
// }
//
// typedef int err_t;
//
// enum err_ {
// 	ERR_OK = 0, // no error
// 	ERR_FAIL = -1, // fail on error
// };
//
// const char *err_str(err_t e) {
// 	switch ((enum err_)e) {
// 		case ERR_OK:	return "no-error";
// 		case ERR_FAIL:	return "fail-on-error";
// 	}
// 	return "unknown error";
//
// }
