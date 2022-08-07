/*****************************************************************************************************************
 * Program to demonstrate the first come first serve cpu scheduling algorithm.
 * In FCFS, the process that has arrived the earliest is executed first.
 * For this a structure representing a process, with members as:
 *      Process id [Id]
 *      Arrirval Time [AT]
 *      Burst Time [BT]
 *      Completion Time [CT]
 *      Turnaround Time [TAT]
 *      Waiting Time [WT] is used.
 * Turnaround time [TAT] = Completion time [CT] - Arrival time [AT]
 * Waiting time [WT] = Turnaround time [TAT] - Burst time [BT]
******************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct process {
    int Id, AT, BT, CT, TAT, WT; 
} pro;

pro p[15];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return; 
}

void sort(int n) {
    for(int i = 0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                swap(&p[j].Id, &p[j+1].Id);
                swap(&p[j].AT, &p[j+1].AT);
                swap(&p[j].BT, &p[j+1].BT);
            }
        }
    }
}

void printGanttChart(int n) {
    for(int i=0; i<n; i++) {
        if(p[i].AT > p[i-1].CT) {
            for(int j=1; j<=(p[i].AT - p[i-1].CT); j++) {
                printf("-");
            }
            printf("|");
        }
        for(int j=1; j<=p[i].BT; j++) {
            printf("-");
        }
        printf("|");
    }
    printf("\n");

    for(int i=0; i<n; i++) {
        if(p[i].AT > p[i-1].CT) {
            printf("I");
            for(int j=1; j<=(p[i].AT - p[i-1].CT); j++) {
                printf(" ");
            }  
        }
        printf("P%d", p[i].Id);
        for(int j=1; j<=(p[i].BT); j++) {
            printf(" ");
        }
    }
    printf("\n");

    printf("0");
    for(int i=0; i<n; i++) {
        if(p[i].AT > p[i-1].CT) {
            for(int j=1; j<=(p[i].AT - p[i-1].CT); j++) {
                printf(" ");
            }  
            printf("%d", p[i-1].CT + (p[i].AT - p[i-1].CT));
        }
        for(int j=1; j<=(p[i].BT); j++) {
            printf(" ");
        }
        printf("%d", p[i].CT);
    }
    printf("\n");
}

void main() {
    int n, total_WT=0, total_TAT=0;
    float avg_WT=0, avg_TAT=0;
    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);
    printf("\nEnter the arrival time and burst time of the process:\n");
    printf("AT BT\n");
    for(int i=0; i<n; i++) {
        p[i].Id = (i+1);
        scanf("%d%d", &p[i].AT, &p[i].BT);
    }

    sort(n);

    //Finding the completion time of all the processes
    p[0].WT = 0;
    p[0].CT = p[0].AT + p[0].BT;
    for(int i=1; i<n; i++) {
        if(p[i].AT > p[i-1].CT) {
            p[i].CT = p[i-1].CT + (p[i].AT - p[i-1].CT) + p[i].BT;
            continue;
        } 
        p[i].CT = p[i-1].CT + p[i].BT;
    }

    //Finding the turnaround time and waiting time of all the processes
    for(int i=0; i<n; i++) {
        if(p[i].AT > p[i-1].CT) {
            p[i].TAT = p[i].CT - p[i].AT;
            total_TAT += p[i].TAT;
            p[i].WT = 0;
            continue;
        }
        p[i].TAT = p[i].CT - p[i].AT;
        total_TAT += p[i].TAT;
        p[i].WT = p[i].TAT - p[i].BT;
        total_WT += p[i].WT;
    }
    avg_TAT = (float)total_TAT/n;
    avg_WT = (float)total_WT/n;

    //Printing the table of processes with details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);

    printGanttChart(n);
}
