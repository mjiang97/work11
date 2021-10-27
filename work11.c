#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int random_num(int x) {
    int r;
    int err = read(x, &r, sizeof(r));
    if (err < 0) {
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    return r;
}

int main() {
    printf("Generating random numbers:\n");
    int data = open("/dev/random", O_RDONLY);
    int arr[10], err, i;
    for (int i = 0; i < 10; i++) {
        arr[i] = random_num(data);
        printf("\trandom %d: %u\n", i, arr[i]);
    }
    printf("\nWriting numbers to file...\n\n");
    int file = open("out.txt", O_CREAT | O_WRONLY | O_EXCL, 0644);
    if (file == -1) {
        printf("Error: \n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    err = write(file, arr, sizeof(arr));
    if (err < 0){
        printf("Error: \n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    printf("Reading numbers from file...\n\n");
    file = open("out.txt",O_RDONLY);
    if (err < 0) {
        printf("Error: \n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    unsigned int arr2[10];
    err = read(file,arr2,sizeof(arr2));
    if (err < 0) {
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    printf("Verification that written values were the same: \n");
    for (i = 0; i < 10; i++){
        printf("\trandom %d: %u\n",i, arr2[i]);
    }
    return 0;
}