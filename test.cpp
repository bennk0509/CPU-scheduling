#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

// I/O variable for read File
ifstream finp; ofstream fout;

struct Process
{
    /* Process Info */
    int arrival_time;
    vector<int> cpu_burst_time;
    vector<int> io_burst_time;
    int finished_time;
    int waiting_time = 0;
    int wt_Until_AccessCPU = 0;
    bool hasArrived = false;

    int timeout = 0; // Use for Round Robin Scheduling
};

void Print_Info_Processes(Process x)
{
    cout<<"Arrival Time: "<<x.arrival_time<<" ";

    cout<<"CPU Burst Time: ";
    for (int i = 0; i < x.cpu_burst_time.size(); i++)
        cout<<x.cpu_burst_time[i]<<" ";
    cout<<". ";

    cout<<"IO Burst Time: ";
    for (int i = 0; i < x.io_burst_time.size(); i++)
        cout<<x.io_burst_time[i]<<" ";
    cout<<endl;
    
    return;
}

void Read_Normal_Info_Processes(Process arr[4], int &n)
{
    finp>> n; //Number of processes

    finp.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;

        getline(finp, s);
        arr[i].arrival_time = int(s[0]) - 48; //Arrival time of process i
        if (s[s.size() - 1] != ' ') s += " ";

        int flip_flop = 0; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 2; j < s.size(); j++)
            if (arr[i].cpu_burst_time.size() == 3 && arr[i].io_burst_time.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].cpu_burst_time.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].io_burst_time.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
            

        cout<<"Process "<<i+1<<":\n"; //Print information of process i
        Print_Info_Processes(arr[i]);
    }
}

void Read_RR_Info_Processes(Process arr[4], int &n, int &q)
{
    finp>> q; //Quantum Time
    finp>> n; //Number of processes

    finp.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;

        getline(finp, s);
        arr[i].arrival_time = int(s[0]) - 48; //Arrival time of process i
        if (s[s.size() - 1] != ' ') s += " ";
        
        int flip_flop = 0; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 2; j < s.size(); j++)
            if (arr[i].cpu_burst_time.size() == 3 && arr[i].io_burst_time.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].cpu_burst_time.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].io_burst_time.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
            

        cout<<"Process "<<i+1<<":\n"; //Print information of process i
        Print_Info_Processes(arr[i]);
    }
}

void FCFS_Scheduling(vector<char> &cpu_time, vector<char> &io_time, int &time, int n, Process arr[4])
{
    /* Declaration */
    int finished_Process = 0; // Use for check whether all process is finished or not
    int authority_CPU_process = 0; // Use for check whether the process still have CPU authority or not
    int authority_IO_process = 0; // Use for check whether the process still have IO authority or not
    vector<int> Ready_CPU_Queue; // Use for store the index of process that is ready to run
    vector<int> Ready_IO_Queue; // Use for store the index of process that is ready to run

    while (true)
    {
        /* Arrival Time*/
        for (int i = 0; i < n; i++)
            if (arr[i].arrival_time == time && !arr[i].hasArrived) {
                Ready_CPU_Queue.push_back(i);
                arr[i].wt_Until_AccessCPU = arr[i].arrival_time;
                arr[i].hasArrived = true;
            }
        /* Declaration */
        int x, y; // Use for index of Ready_CPU_Queue and Ready_IO_Queue
        int k = 1; // Use for break Point

        if (Ready_CPU_Queue.size() != 0) x = Ready_CPU_Queue[0];
        if (Ready_CPU_Queue.size() != 0 && arr[x].cpu_burst_time[0] == 0 )
        {
            arr[x].cpu_burst_time.erase(arr[x].cpu_burst_time.begin());
            Ready_CPU_Queue.erase(Ready_CPU_Queue.begin());
            if (arr[x].io_burst_time.size() != 0) Ready_IO_Queue.push_back(x);
            else 
            {
                arr[x].finished_time = time;
                finished_Process ++;
            }
        }

        if (Ready_IO_Queue.size() != 0) y = Ready_IO_Queue[0];
        if (Ready_IO_Queue.size() != 0 && arr[y].io_burst_time[0] == 0)
        {
            arr[y].io_burst_time.erase(arr[y].io_burst_time.begin());
            Ready_IO_Queue.erase(Ready_IO_Queue.begin());
            if (arr[y].cpu_burst_time.size() != 0) 
            {
                Ready_CPU_Queue.push_back(y);
                arr[y].wt_Until_AccessCPU = time;
                arr[y].hasArrived = true;
            }
            else 
            {
                arr[y].finished_time = time;
                finished_Process ++;
            }
        }

        if (finished_Process == n) break;


        Burst_Time: // Label for break Point, also Burst Time
        if (Ready_CPU_Queue.size() != 0) 
        {
            x = Ready_CPU_Queue[0];

            if (arr[x].hasArrived) 
            {
                arr[x].waiting_time += time - arr[x].wt_Until_AccessCPU;
                arr[x].hasArrived = false;
            }

            authority_CPU_process = arr[x].cpu_burst_time[0];

            authority_CPU_process --;
            arr[x].cpu_burst_time[0] --;

            cpu_time.push_back(char(x + 1) + 48);

        }
        else cpu_time.push_back('_');
        

        IO:
        if (Ready_IO_Queue.size() != 0)
        { 
            y = Ready_IO_Queue[0];
            authority_IO_process = arr[y].io_burst_time[0];

            authority_IO_process --;
            arr[y].io_burst_time[0] --;

            io_time.push_back(char(y + 1) + 48);
        }
        else io_time.push_back('_');

        time ++;
    }
    

    return;
}

void FCFS_Algorithm()
{
    int n; int arrival_time; Process arr[4];
    Read_Normal_Info_Processes(arr, n);

    //Start Scheduling
    int time = 0;
    vector<char> cpu_time;
    vector<char> io_time;
    
    FCFS_Scheduling(cpu_time, io_time, time, n, arr);
    
    /* Deleting all redundant element */
    while (cpu_time.size() < io_time.size())
        io_time.pop_back();
    while (io_time.size() < cpu_time.size())
        cpu_time.pop_back();

    cout<<"\n"<<"Running Time: "<<time<<endl;

    for (int i = 0; i < cpu_time.size(); i++)
        cout<<cpu_time[i]<<" ";
    cout<<endl;

    for (int i = 0; i < io_time.size(); i++)
        cout<<io_time[i]<<" ";
    cout<<endl;
    
    cout<<left;
    for (int i = 0; i < n; i++)
    {
        cout<<"Process "<<i + 1<<" Finish Time: "<<setw(3)<<arr[i].finished_time<<". Turn-around Time: "<<setw(3)<<arr[i].finished_time - arr[i].arrival_time<<". Waiting Time: "<<arr[i].waiting_time<<endl;
    }

    // for (int i = 0; i < cpu_time.size(); i++)
    //     fout<<cpu_time[i]<<" ";
    // fout<<endl;

    // for (int i = 0; i < io_time.size(); i++)
    //     fout<<io_time[i]<<" ";
    // fout<<endl;
    
    // //cout<<left;
    // for (int i = 0; i < n; i++) fout<<arr[i].finished_time - arr[i].arrival_time<<" ";
    // fout<<endl;

    // for (int i = 0; i < n; i++) fout<<arr[i].waiting_time<<" ";

    return;
}

int main()
{
    int Scheduling_Algorithm;

    finp.open("input.txt");
    fout.open("Output.txt");
    finp>> Scheduling_Algorithm; //Determine the scheduling algorithm
    finp.close(); fout.close();
    return 0;
}