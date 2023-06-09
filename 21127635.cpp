#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <queue>
#include <string>
using namespace std;
ifstream fin;
ofstream fout;
// vector<char>CPU_TIME = vector<char>();
 
struct Process
{
    vector<int> CPU_time;
    vector<int> IO_time;
    int arrival_time;
    int waiting_time = 0;
    int turnaround_time = 0;
    int finish_time = 0;
    int start_time = 0;
    bool checkArrival = false;
    int quantum = 0;
};
void readRRFile(Process p[4],int &n, int &quantum)
{
    fin >> quantum;
    fin >> n;
    fin.ignore();
    for(int i=0;i<n;i++)
    {
        string s="";
        string temp = "";
 
        getline(fin,s);
        p[i].arrival_time = (int)s[0] - 48;
        bool checkCPUorIO = true;
        s = s + " ";
        for(int j = 2;j <= s.length();j++)
        {
            if(p[i].CPU_time.size() > 3 && p[i].IO_time.size() > 3) break;
            else
            {
                if(s[j] == ' ')
                {
                    if(checkCPUorIO == true)
                    {
                        p[i].CPU_time.push_back((int)s[j-1] - 48);
                        checkCPUorIO = false;
                    }
                    else
                    {
                        p[i].IO_time.push_back((int)s[j-1] - 48);
                        checkCPUorIO = true;
                    }
                    temp = "";
                }
                else temp = s[j];
            } 
        }
 
    }
}
void readNormalFile(Process p[4],int &n)
{
    fin >> n;
    fin.ignore();
    for(int i=0;i<n;i++)
    {
        string s="";
        string temp = "";
 
        getline(fin,s);
        p[i].arrival_time = (int)s[0] - 48;
        bool checkCPUorIO = true;
        s = s + " ";
        for(int j = 2;j <= s.length();j++)
        {
            if(p[i].CPU_time.size() > 3 && p[i].IO_time.size() > 3) break;
            else
            {
                if(s[j] == ' ')
                {
                    if(checkCPUorIO == true)
                    {
                        p[i].CPU_time.push_back((int)s[j-1] - 48);
                        checkCPUorIO = false;
                    }
                    else
                    {
                        p[i].IO_time.push_back((int)s[j-1] - 48);
                        checkCPUorIO = true;
                    }
                    temp = "";
                }
                else temp = s[j];
            } 
        }
 
    }
}
void Read_RR_Info_Processes(Process arr[4],int &n, int &quantum)
{
    fin>>quantum; //Quantum time
    fin>>n; //Number of processes
 
    fin.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;
 
        getline(fin, s);
        arr[i].arrival_time = int(s[0]) - 48; //Arrival time of process i
        if (s[s.size() - 1] != ' ') s += " ";
 
        int flip_flop = 0; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 2; j < s.size(); j++)
            if (arr[i].CPU_time.size() == 3 && arr[i].IO_time.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].CPU_time.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].IO_time.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
    }
}
void Read_Normal_Info_Processes(Process arr[4], int &n)
{
    fin>> n; //Number of processes
 
    fin.ignore();
    for (int i = 0; i < n; i++)
    {
        // char* s[14]; 
        // memset(s, 0, 13); // Clear the array
        string s = "";
        string temp = "";
        int y = 1;
 
        getline(fin, s);
        arr[i].arrival_time = int(s[0]) - 48; //Arrival time of process i
        if (s[s.size() - 1] != ' ') s += " ";
 
        int flip_flop = 0; // 0: CPU Burst Time, 1: IO Burst Time
        for (int j = 2; j < s.size(); j++)
            if (arr[i].CPU_time.size() == 3 && arr[i].IO_time.size() == 3) break;
            else{
                if (s[j] == ' ') // If s[j] is not a space
                {
                    if (flip_flop == 0){
                        //Read CPU Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].CPU_time.push_back(x);
                        flip_flop = 1;
                    }
                    else {
                        //Read IO Burst Time
                        int x = atoi(temp.c_str());
                        arr[i].IO_time.push_back(x);
                        flip_flop = 0;
                    }
                    temp = "";
                }
                else temp += s[j];
            }
    }
}
void Print_Info_Processes(Process x)
{
    cout<<"Arrival Time: "<<x.arrival_time<<" ";
 
    cout<<"CPU Burst Time: ";
    for (int i = 0; i < x.CPU_time.size(); i++)
        cout << x.CPU_time[i] << " ";
    cout<<". ";
 
    cout<<"IO Burst Time: ";
    for (int i = 0; i < x.IO_time.size(); i++)
        cout<<x.IO_time[i]<<" ";
    cout<<endl;
    return;
}
void FCFS(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time)
{
    int NumOfProcess = 0;
    vector<int>readyCPU;
    vector<int>readyIO;
    while (true)
    {
        //check arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time == time && p[i].checkArrival == false) 
            {
                p[i].checkArrival = true;
                readyCPU.push_back(i);
                p[i].start_time = p[i].arrival_time;
            }
        }
        int id, id_io; 
        //each time, check readyCPU
        if(readyCPU.size() != 0) id = readyCPU.front();
 
        if(readyCPU.size() != 0 && p[id].CPU_time[0] == 0)
        {
            p[id].CPU_time.erase(p[id].CPU_time.begin());
            readyCPU.erase(readyCPU.begin());
            if(p[id].IO_time.size() != 0)
            {
                readyIO.push_back(id);
            }
            else{
                p[id].finish_time = time;
                NumOfProcess++;
            }
        }
 
        if(readyIO.size() != 0) id_io = readyIO.front();
 
        if(readyIO.size() != 0 && p[id_io].IO_time[0] == 0)
        {
            p[id_io].IO_time.erase(p[id_io].IO_time.begin());
            readyIO.erase(readyIO.begin());
            if(p[id_io].CPU_time.size() != 0)
            {
                readyCPU.push_back(id_io);
                p[id_io].checkArrival = true;
                p[id_io].start_time = time;
            }
            else{
                p[id_io].finish_time = time;
                NumOfProcess++;
            }
        }
        if(NumOfProcess == n) break;
        //CPU   
        if(readyCPU.size() != 0)
        {
            id = readyCPU.front();
            if (p[id].checkArrival) 
            {
                p[id].waiting_time += time - p[id].start_time;
                p[id].checkArrival = false;
            }
            CPU.push_back(char(id+1)+48);
            p[id].CPU_time[0]--;
        }
        else CPU.push_back('_');
 
        //IO
        if(readyIO.size() != 0)
        {
            id_io = readyIO.front();
            p[id_io].IO_time[0]--;
            IO.push_back(char(id_io+1)+48);
        }
        else IO.push_back('_');
 
        time++;
    }
    return;
}
void SJF(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time)
{
    int NumOfProcess = 0;
    vector<int>readyCPU;
    vector<int>readyIO;
    while (true)
    {
        //check arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time == time && p[i].checkArrival == false) 
            {
                p[i].checkArrival = true;
                p[i].start_time = p[i].arrival_time;
                readyCPU.push_back(i);
 
            }
        }
        for(int i = 0; i < readyCPU.size(); i++)
        {
            for(int j = i+1; j < readyCPU.size(); j++)
            {
                if(p[readyCPU[i]].CPU_time[0] > p[readyCPU[j]].CPU_time[0])
                {
                    int temp = readyCPU[i];
                    readyCPU[i] = readyCPU[j];
                    readyCPU[j] = temp;
                }
            }
        }
 
        int id, id_io; 
        //each time, check readyCPU
        if(readyCPU.size() != 0) id = readyCPU.front();
 
        if(readyCPU.size() != 0 && p[id].CPU_time[0] == 0)
        {
            p[id].CPU_time.erase(p[id].CPU_time.begin());
            readyCPU.erase(readyCPU.begin());
            if(p[id].IO_time.size() != 0)
            {
                readyIO.push_back(id);
            }
            else{
                p[id].finish_time = time;
                NumOfProcess++;
            }
        }
 
        if(readyIO.size() != 0) id_io = readyIO.front();
        if(readyIO.size() != 0 && p[id_io].IO_time[0] == 0)
        {
            p[id_io].IO_time.erase(p[id_io].IO_time.begin());
            readyIO.erase(readyIO.begin());
            if(p[id_io].CPU_time.size() != 0)
            {
                readyCPU.push_back(id_io);
                p[id_io].start_time = time;
                p[id_io].checkArrival = true;
            }
            else{
                p[id_io].finish_time = time;
                NumOfProcess++;
            }
        }
        if(NumOfProcess == n) break;
 
        if(readyCPU.size() != 0)
        {
            id = readyCPU.front();
            if (p[id].checkArrival) 
            {
                p[id].waiting_time += time - p[id].start_time;
                p[id].checkArrival = false;
            }
            CPU.push_back(char(id+1)+48);
            p[id].CPU_time[0]--;
        }
        else CPU.push_back('_');
 
 
        if(readyIO.size() != 0)
        {
            id_io = readyIO.front();
            p[id_io].IO_time[0]--;
            IO.push_back(char(id_io+1)+48);
        }
        else IO.push_back('_');
 
        time++;
    }
    return;
}
void SRTN(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time)
{
    int NumOfProcess = 0;
    vector<int>readyCPU;
    vector<int>readyIO;
    while (true)
    {
        //check arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time == time && p[i].checkArrival == false) 
            {
                p[i].checkArrival = true;
                p[i].start_time = p[i].arrival_time;
                readyCPU.push_back(i);
 
            }
        }
        /* When the latest process ran out or start to choose which process is perfect to execute*/
        if(readyCPU.size() != 0)
        {
            for(int i = 0; i < readyCPU.size(); i++)
            {
                for(int j = i+1; j < readyCPU.size(); j++)
                {
                    if(p[readyCPU[i]].CPU_time[0] > p[readyCPU[j]].CPU_time[0])
                    {
                        int temp = readyCPU[i];
                        readyCPU[i] = readyCPU[j];
                        readyCPU[j] = temp;
                    }
                }
            }
        }
        int id, id_io; 
        //each time, check readyCPU
        if(readyCPU.size() != 0) id = readyCPU.front();
 
        if(readyCPU.size() != 0 && p[id].CPU_time[0] == 0)
        {
            p[id].CPU_time.erase(p[id].CPU_time.begin());
            readyCPU.erase(readyCPU.begin());
            if(p[id].IO_time.size() != 0)
            {
                readyIO.push_back(id);
            }
            else{
                p[id].finish_time = time;
                NumOfProcess++;
            }
        }
 
        if(readyIO.size() != 0) id_io = readyIO.front();
        if(readyIO.size() != 0 && p[id_io].IO_time[0] == 0)
        {
            p[id_io].IO_time.erase(p[id_io].IO_time.begin());
            readyIO.erase(readyIO.begin());
            if(p[id_io].CPU_time.size() != 0)
            {
                readyCPU.push_back(id_io);
                p[id_io].start_time = time;
                p[id_io].checkArrival = true;
            }
            else{
                p[id_io].finish_time = time;
                NumOfProcess++;
            }
        }
        if(NumOfProcess == n) break;
 
        if(readyCPU.size() != 0)
        {
            id = readyCPU.front();
            if (p[id].checkArrival) 
            {
                p[id].waiting_time += time - p[id].start_time;
                p[id].checkArrival = false;
            }
            CPU.push_back(char(id+1)+48);
            p[id].CPU_time[0]--;
        }
        else CPU.push_back('_');
 
 
        if(readyIO.size() != 0)
        {
            id_io = readyIO.front();
            p[id_io].IO_time[0]--;
            IO.push_back(char(id_io+1)+48);
        }
        else IO.push_back('_');
 
        time++;
    }
    return;
}
void RR(Process p[4], int n, vector<char>&CPU, vector<char>&IO, int &time, int quantum)
{
    int NumOfProcess = 0;
    vector<int>readyCPU;
    vector<int>readyIO;
    while (true)
    {
        //check arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time == time && p[i].checkArrival == false) 
            {
                p[i].checkArrival = true;
                readyCPU.push_back(i);
                p[i].quantum = quantum;
                p[i].start_time = p[i].arrival_time;
            }
        }
 
        int id, id_io; 
 
        if (readyCPU.size() != 0) 
        {   
            id = readyCPU[0]; 
            /* Let the process run with limit time */
            if (p[id].quantum == 0) {
                if (p[id].CPU_time[0] != 0) {
                    readyCPU.erase(readyCPU.begin());
                    readyCPU.push_back(id);
                    p[id].quantum = quantum;
                    p[id].start_time = time;
                    p[id].checkArrival = true;            
                }           
            }
        }
        //each time, check readyCPU
        if(readyCPU.size() != 0) id = readyCPU.front();
 
        if(readyCPU.size() != 0 && p[id].CPU_time[0] == 0)
        {
            p[id].CPU_time.erase(p[id].CPU_time.begin());
            readyCPU.erase(readyCPU.begin());
            if(p[id].IO_time.size() != 0)
            {
                readyIO.push_back(id);
            }
            else{
                p[id].finish_time = time;
                NumOfProcess++;
            }
        }
 
        if(readyIO.size() != 0) id_io = readyIO.front();
        if(readyIO.size() != 0 && p[id_io].IO_time[0] == 0)
        {
            p[id_io].IO_time.erase(p[id_io].IO_time.begin());
            readyIO.erase(readyIO.begin());
            if(p[id_io].CPU_time.size() != 0)
            {
                readyCPU.push_back(id_io);
                p[id_io].start_time = time;
                p[id_io].checkArrival = true;
            }
            else{
                p[id_io].finish_time = time;
                NumOfProcess++;
            }
        }
        if(NumOfProcess == n) break;
 
        if(readyCPU.size() != 0)
        {
            id = readyCPU.front();
            if (p[id].checkArrival) 
            {
                p[id].waiting_time += time - p[id].start_time;
                p[id].checkArrival = false;
            }
            CPU.push_back(char(id+1)+48);
            p[id].CPU_time[0]--;
            p[id].quantum--;
        }
        else CPU.push_back('_');
 
 
        if(readyIO.size() != 0)
        {
            id_io = readyIO.front();
            p[id_io].IO_time[0]--;
            IO.push_back(char(id_io+1)+48);
        }
        else IO.push_back('_');
 
        time++;
    }
    return;
}
void FCFS_Scheduling()
{
    vector<char>CPU_TIME;
    vector<char>IO_TIME;
    int n;
    int quantum;
    int Algorithm;
    int time = 0;
    Process p[4];
    readNormalFile(p,n);
    FCFS(p,n,CPU_TIME,IO_TIME,time);
    while (CPU_TIME.size() < IO_TIME.size())
        IO_TIME.pop_back();
    while (IO_TIME.size() < CPU_TIME.size())
        CPU_TIME.pop_back();
 
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        fout << CPU_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        fout << IO_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].finish_time - p[i].arrival_time << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].waiting_time << " ";
    }
    return;
}
 
void SJF_Scheduling()
{
    vector<char>CPU_TIME;
    vector<char>IO_TIME;
    int n;
    int quantum;
    int Algorithm;
    int time = 0;
    Process p[4];
    readNormalFile(p,n);
    SJF(p,n,CPU_TIME,IO_TIME,time);
    while (CPU_TIME.size() < IO_TIME.size())
        IO_TIME.pop_back();
    while (IO_TIME.size() < CPU_TIME.size())
        CPU_TIME.pop_back();
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        fout << CPU_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        fout << IO_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].finish_time - p[i].arrival_time << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].waiting_time << " ";
    }
    return;
}
 
void SRTN_Scheduling()
{
    vector<char>CPU_TIME;
    vector<char>IO_TIME;
    int n;
    int quantum;
    int Algorithm;
    int time = 0;
    Process p[4];
    readNormalFile(p,n);
    SRTN(p,n,CPU_TIME,IO_TIME,time);
    while (CPU_TIME.size() < IO_TIME.size())
        IO_TIME.pop_back();
    while (IO_TIME.size() < CPU_TIME.size())
        CPU_TIME.pop_back();
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        fout << CPU_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        fout << IO_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].finish_time - p[i].arrival_time<< " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].waiting_time << " ";
    }
    return;
}
void RR_Scheduling()
{
    vector<char>CPU_TIME;
    vector<char>IO_TIME;
    int n;
    int quantum;
    int Algorithm;
    int time = 0;
    Process p[4];
    readRRFile(p,n,quantum);
    RR(p,n,CPU_TIME,IO_TIME,time,quantum);
    while (CPU_TIME.size() < IO_TIME.size())
        IO_TIME.pop_back();
    while (IO_TIME.size() < CPU_TIME.size())
        CPU_TIME.pop_back();
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        fout << CPU_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        fout << IO_TIME[i] << " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].finish_time - p[i].arrival_time<< " ";
    }
    fout << endl;
    for(int i = 0; i < n; i++)
    {
        fout << p[i].waiting_time << " ";
    }
    return;
}
 
 
 
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