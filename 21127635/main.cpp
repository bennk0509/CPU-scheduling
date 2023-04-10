#include "header.h"
#include "header.cpp"

int main()
{
    int Scheduling;
    fin.open("input.txt");
    fout.open("output.txt");
    fin >> Scheduling;
    switch (Scheduling)
    {
    case 1:
        FCFS_Scheduling();
        break;
    case 2:
        RR_Scheduling();
        break;
    case 3:
        SJF_Scheduling();
        break;
    case 4:
        SRTN_Scheduling();
        break;
    default:
        break;
    }
    fin.close();
    fout.close();
    return 0;
}