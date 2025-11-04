/**
 * @file pmod.c
 * @brief Modifies its own priority and sleeps for a specified duration
 * 
 * Course: CPE 2600
 * Section: 111
 * Assignment: Lab 9 System calls
 * Name: Walker Williams
 * 
 * Compile: gcc -o pmod pmod.c
 *          ./pmod
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Gets current priority
    int priority = nice(0);
    printf("Current priority: %d\n", priority);
    
    // Reduces priority by 10 (increase nice value) 
    int new_priority = nice(10);
    if (new_priority == -1) 
    {
        printf("nice() did not work correctly.\n");
    } 
    else 
    {
        printf("New priority: %d\n", new_priority);
    }
    
    // Sleeps for 1,837,272,638 nanoseconds
    struct timespec sleep;
    sleep.tv_sec = 1;  // 1 second
    sleep.tv_nsec = 837272638;  // 83727268 nanoseconds
    
    printf("Sleeping for 1,837,272,638 nanoseconds...\n");
    if (nanosleep(&sleep, NULL) == -1) 
    {
        printf("Sleep did not wait 1,837,272,638 nanoseconds\n");
    }
    
    // Goodbye message
    printf("Goodbye! Program completed successfully.\n");
    return 0;
}