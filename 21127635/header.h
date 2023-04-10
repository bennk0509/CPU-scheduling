#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <queue>
#include <string>
using namespace std;
ifstream fin;
ofstream fout;

struct Process
{
    vector<int> CPU_time;
    vector<int> IO_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int finish_time;
    bool checkArrival = false;
    int quantum = 0;
    int start_time;
};

void readNormalFile(Process p[4],int &n);
void readRRFile(Process p[4],int &n, int &quantum);
void Print_Info_Processes(Process x);
void FCFS(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time);
void SJF(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time);
void SRTN(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time);
void RR(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time, int quantum);
void FCFS_Scheduling();
void SJF_Scheduling();
void SRTN_Scheduling();
void RR_Scheduling();