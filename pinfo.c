/**
 * @file pinfo.c
 * @brief Shows process information including priority and scheduling method for a given PID
 * 
 * Course: CPE 2600
 * Section: 111
 * Assignment: Lab 9 System calls
 * Name: Walker Williams
 * 
 * Compile: gcc -o pinfo pinfo.c
 *          ./pinfo
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    if (argc == 1) 
    {
        pid = getpid();
        printf("Checking current process PID: %d\n", pid);
    } 
    else if (argc == 2) 
    {
        // PID from argumnet argv
        pid = atoi(argv[1]);
        
        // Checks if process exists by sending signal 0
        if (kill(pid, 0) == -1) 
        {
            if (errno == ESRCH) 
            {
                fprintf(stderr, "Process with PID %d does not exist\n", pid);
            } 
            else 
            {
                printf("Process was not checked.\n");
            }
            return 1;
        }
        printf("Checking process with PID: %d\n", pid);
    } 
    else 
    {
        fprintf(stderr, "Usage: %s [PID]\n", argv[0]);
        return 1;
    }

    // Gets process priority
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) 
    {
        printf("getpriority() did not run correctly\n");
    } 
    else 
    {
        printf("Process priority: %d\n", priority);
    }

    // Gets scheduling policy
    int schedule_policy = sched_getscheduler(pid);
    if (schedule_policy == -1) 
    {
        printf("sched_getscheduler() did not run correctly\n");
    } 
    else 
    {
        // Converts scheduling policy to human-readable string
        const char* policy_name;
        if (schedule_policy == SCHED_OTHER)
        {
            policy_name = "SCHED_OTHER (Normal)";
        }
        else if (schedule_policy == SCHED_FIFO)
        {
            policy_name = "SCHED_FIFO (First In First Out)";
        }
        else if (schedule_policy == SCHED_RR)
        {
            policy_name = "SCHED_RR (Round Robin)";
        }
        else if (schedule_policy == SCHED_BATCH)
        {
            policy_name = "SCHED_BATCH (Batch)";
        }
        else if (schedule_policy == SCHED_IDLE)
        {
            policy_name = "SCHED_IDLE (Idle)";
        }
        else
        {
            policy_name = "Unknown";
        }
        printf("Scheduling method: %s\n", policy_name);
    }

    return 0;
}