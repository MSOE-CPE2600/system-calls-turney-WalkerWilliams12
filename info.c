/**
 * @file info.c
 * @brief prints:
 *        The current time of day - in nanoseconds
 *        The system’s network name
 *        The operating system name
 *        The operating system release and version
 *        The system’s hardware type
 *        The number of CPUs on the system
 *        The total amount of physical memory in bytes
 *        The total amount of free memory in bytes
 * 
 * Course: CPE 2600
 * Section: 111
 * Assignment: Lab 9 System calls
 * Name: Walker Williams
 * 
 * Compile: gcc -o info info.c
 *          ./info
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    // Time of the day in nano secones
    struct timespec time;
    if (clock_gettime(CLOCK_REALTIME, &time) == 0)
    {
        struct tm local;
        localtime_r(&time.tv_sec, &local);

        // Calculates total nanoseconds for the day - orginal I had was getting just the samll value just from time.tv_nsec which was just the singular second;
        long long nanoseconds_of_day = ((long long)local.tm_hour * 3600LL + (long long)local.tm_min * 60LL + (long long)local.tm_sec) * 1000000000LL + time.tv_nsec;
        printf("Current time (nanosecond): %lld\n", nanoseconds_of_day);
    }
    else
    {
        printf("clock_gettime() did not get the time.");
    }

    // Name of the computer on the network
    char network_name[256];
    if(gethostname(network_name, sizeof(network_name)) == 0)
    {
        printf("System network name is: %s\n", network_name);
    }
    else
    {
        printf("gethostname() did not get the name.");
    }

    // Information on the computers operating system (Linux subsytem)
    struct utsname computer_info;
    if (uname(&computer_info) == 0)
    {
        if(strlen(computer_info.sysname) > 0)
        {
            printf("Operatng System: %s\n", computer_info.sysname);
        }
        if(strlen(computer_info.release) > 0)
        {
            printf("OS release: %s\n", computer_info.release);     
        }
        if(strlen(computer_info.version) > 0)
        {
            printf("OS version: %s\n", computer_info.version);
        }
        if(strlen(computer_info.machine) > 0)
        {
            printf("Machine format: %s\n", computer_info.machine);
        }
    }
    else
    {
        printf("uname() did not return the correct computer information.");
    }

    // Number of CPU cores in the Core Evo i5
    printf("Number of CPUs: %d\n", get_nprocs());

    // Total system ram (Recorded at 8GB)
    struct sysinfo ram_memory;
    if (sysinfo(&ram_memory) == 0) 
    {
        printf("Total physical memory (bytes): %lu\n", ram_memory.totalram * ram_memory.mem_unit);
        printf("Free memory (bytes): %lu\n", ram_memory.freeram * ram_memory.mem_unit);
    } 
    else 
    {
        printf("sysinfo() did not return the ram memory values");
    }
    
    return 0;
}