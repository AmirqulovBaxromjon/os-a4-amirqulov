#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 256
#define MAX_ARGS 32

// Satrni bo'shliqlar bo'yicha argumentlarga ajratish
int parse_input(char *line, char **args) {
    int count = 0;
    char *token = strtok(line, " \t\n");

    while (token != NULL && count < MAX_ARGS - 1) {
        args[count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[count] = NULL;
    return count;
}

// Ichki buyruqlarni tekshirish (cd, help, exit)
int check_builtin(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        printf("Shell dasturi yakunlandi.\n");
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            printf("Xato: katalog korsatilmadi. Masalan: cd /home\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd xatosi");
            }
        }
        return 1;
    }

    if (strcmp(args[0], "help") == 0) {
        printf("Sodda Mini Shell dasturi.\n");
        printf("Ichki buyruqlar: cd, help, exit\n");
        printf("Boshqa buyruqlar tizim orqali (fork va execvp) bajariladi.\n");
        return 1;
    }

    return 0;
}

// Tashqi buyruqni fork va execvp orqali ishga tushirish
void execute_command(char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork xatosi yuz bersa
        perror("fork xatosi");
    } else if (pid == 0) {
        // Bola jarayon (child process)
        if (execvp(args[0], args) < 0) {
            perror("Buyruqni bajarishda xato");
            exit(1);
        }
    } else {
        // Ota jarayon (parent process) - bola jarayon tugashini kutadi
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    printf("Mini Shell ishga tushdi. Chiqish uchun 'exit' deb yozing.\n");

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        // Foydalanuvchi kiritgan satrni o'qish
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Argumentlarga ajratish
        int arg_count = parse_input(line, args);
        if (arg_count == 0) {
            continue;
        }

        // Agar ichki buyruq bo'lmasa, tizim buyrug'i sifatida bajariladi
        if (!check_builtin(args)) {
            execute_command(args);
        }
    }

    return 0;
}
