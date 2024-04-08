#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

void printColorMessage(const char *message, int color) {
    printf("\033[1;%dm%s\033[0m", color, message);
}

int main() {
    char buffer[100];

    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lockResult = flock(fd, LOCK_EX | LOCK_NB);
    if (lockResult == -1) {
        printColorMessage("Unable to lock file immediately. Waiting...\n", 31);  // красный текст
        flock(fd, LOCK_EX);  // устанавливаем блокировку с ожиданием
    } else {
        printColorMessage("File locked immediately.\n", 32);  // зеленый текст
    }

    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    printf("Read from file:\n%s\n", buffer);

    // Задержка выполнения (в секундах)
    sleep(7);

    // Снятие блокировки
    flock(fd, LOCK_UN);

    close(fd);
    return 0;
}
