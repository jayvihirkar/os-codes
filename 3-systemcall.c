/* Program to demonstrate system calls for file operations
   System calls used:
   1. open()   - to create/open a file
   2. write()  - to write data into the file
   3. read()   - to read data from the file
   4. close()  - to close the file
*/

#include <stdio.h>
#include <fcntl.h>      // For open()
#include <unistd.h>     // For read(), write(), close()
#include <string.h>     // For strlen()

int main()
{
    int fd;
    char write_data[] = "Hello, this is a demo of file system calls.";
    char read_data[100];

    /* Open (or create) the file */
    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);

    if (fd < 0)
    {
        printf("Error in opening file.\n");
        return 1;
    }

    printf("File opened successfully.\n");

    /* Write data to the file */
    write(fd, write_data, strlen(write_data));
    printf("Data written to file.\n");

    /* Move file pointer to the beginning */
    lseek(fd, 0, SEEK_SET);

    /* Read data from the file */
    read(fd, read_data, sizeof(read_data));

    printf("Data read from file:\n%s\n", read_data);

    /* Close the file */
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}