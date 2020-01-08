#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    printf("TEST: Hijo de keneltyr\tPID_test: %d\n", getpid());
    return 0;
}
