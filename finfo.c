/**
 * @file finfo.c
 * @brief displays the file information about a given file provided via the command line
 * 
 * Course: CPE 2600
 * Section: 111
 * Assignment: Lab 9 System calls
 * Name: Walker Williams
 * 
 * Compile: gcc -o finfo finfo.c
 *          ./finfo
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Checks argument argc
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    struct stat file_stats;
    
    // Gets file information using stat
    if (stat(filename, &file_stats) == -1) 
    {
        printf("stat() did not run correctly.\n");
        return 1;
    }
    
    // Prints file type in human-readable format - looked up how to do
    printf("File type: ");
    if (S_ISREG(file_stats.st_mode)) 
    {
        printf("Regular file\n");
    } 
    else if (S_ISDIR(file_stats.st_mode)) 
    {
        printf("Directory\n");
    } 
    else if (S_ISCHR(file_stats.st_mode)) 
    {
        printf("Character device\n");
    } 
    else if (S_ISBLK(file_stats.st_mode)) 
    {
        printf("Block device\n");
    } 
    else if (S_ISFIFO(file_stats.st_mode)) 
    {
        printf("FIFO/pipe\n");
    } 
    else if (S_ISLNK(file_stats.st_mode)) 
    {
        printf("Symbolic link\n");
    } 
    else if (S_ISSOCK(file_stats.st_mode)) 
    {
        printf("Socket\n");
    } else {
        printf("Unknown\n");
    }
    
    // Prints file permissions in human-readable format - looked up all permission modes and found directory catagorey
    printf("Permissions: ");
    printf((S_ISDIR(file_stats.st_mode)) ? "d" : "-");
    printf((file_stats.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stats.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stats.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stats.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stats.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stats.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stats.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stats.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stats.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    
    // Prints file owner (user ID)
    printf("Owner ID: %d\n", file_stats.st_uid);
    
    // Prints file size in bytes
    printf("Size (bytes): %ld\n", file_stats.st_size);
    
    // Prints last modification time in readable format
    char time[80];
    struct tm* time_info = localtime(&file_stats.st_mtime);
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last modification: %s\n", time);
    
    return 0;
}