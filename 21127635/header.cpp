
#include "header.h"

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
void Print_Info_Processes(Process x)
{
    cout << "Arrival time: " << x.arrival_time << endl;
    cout << "CPU time: ";
    for(int i=0;i<x.CPU_time.size();i++)
    {
        cout << x.CPU_time[i] << " ";
    }
    cout << endl;
    cout << "IO time: ";
    for(int i=0;i<x.IO_time.size();i++)
    {
        cout << x.IO_time[i] << " ";
    }
    cout << endl;
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
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        cout << CPU_TIME[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        cout << IO_TIME[i] << " ";
    }
    for(int i = 0; i < n; i++)
    {
        cout << p[i].finish_time << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << p[i].waiting_time << " ";
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
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        cout << CPU_TIME[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        cout << IO_TIME[i] << " ";
    }
    for(int i = 0; i < n; i++)
    {
        cout << p[i].finish_time << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << p[i].waiting_time << " ";
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
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        cout << CPU_TIME[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        cout << IO_TIME[i] << " ";
    }
    for(int i = 0; i < n; i++)
    {
        cout << p[i].finish_time << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << p[i].waiting_time << " ";
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
    for(int i = 0; i < CPU_TIME.size(); i++)
    {
        cout << CPU_TIME[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < IO_TIME.size(); i++)
    {
        cout << IO_TIME[i] << " ";
    }
    for(int i = 0; i < n; i++)
    {
        cout << p[i].finish_time << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << p[i].waiting_time << " ";
    }
    return;
}
