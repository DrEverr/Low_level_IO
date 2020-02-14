#define _CRT_SECURE_NO_WARNINGS	//allowing close read open and write work

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#define FILE_NAME	"arr.dat"		//file to read and write
#define STDOUT_FILENO	_fileno(stdout)	//console
#define N		10

int main(void) {
	//creating some variables
	int arr[N];
	int i, choice, fd;
	srand(time(NULL));

	//Menu
	printf("Write : 1\nRead : 2\nExit : 0\n:");
	scanf("%d", &choice);

	while (choice) {
		switch (choice)
		{
		case 1: //write to file
			for (i = 0; i < N; i++) { //randomize table
				arr[i] = rand() % 10 + 1;
				printf("%d ", arr[i]);
			}
			printf("\n");
			fd = _open(FILE_NAME, _O_WRONLY | _O_TRUNC | _O_CREAT, _S_IREAD | _S_IWRITE); //opening with write open and clear file perrmisions and on file perrmisions are granted perrmissions to modify and read :D
			if (fd > 0) { // if file open failed fd = 0
				int n = _write(fd, arr, sizeof(arr)); //writing data to file
				printf("%d bytes written\n:", n); //how much data writen to file
				_close(fd); //closing file
			}
			else {
				printf("In file %s an error has occurred: %s\n:", FILE_NAME, strerror(errno)); //clear error message
			}
			break;
		case 2: 	//read from file
			fd = _open(FILE_NAME, O_RDONLY); //opening with read only perrmisions
			int n = _read(fd, arr, sizeof(arr)); //reading data from file
			if (fd > 0) {
				printf("%d bytes read\n", n);
				_close(fd); //closing file
				for (i = 0; i < N; i++) //showing data in console
					printf("%d ", arr[i]);
				printf("\n:");
			}
			else {
				printf("In file %s an error has occurred: %s\n:", FILE_NAME, strerror(errno)); //clear error message
			}
			break;
		default:
			break;
		}
		for (i = 0; i < N; i++)
			arr[i] = 0;
		scanf("%d", &choice);
	}
	_unlink(FILE_NAME); //unlinging definitions
	getchar();
	return 0;
}
