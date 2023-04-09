#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
ifstream fin;
ofstream fout;
// vector<char>CPU_TIME = vector<char>();

struct Process
{
    vector<int>CPU_time;
    vector<int>IO_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int finish_time;
    bool checkArrival = false;
};

void readNormalFile(Process p[4],int &n)
{
    fin >> n;
    fin.ignore();
    for(int i=0;i<n;i++)
    {
        string s;
        getline(fin,s);
        p[i].arrival_time = (int)s[0] - 48;
        bool checkCPUorIO = true;
        string temp ;
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

void FCFS(Process p[4], int n, vector<char>&CPU_TIME, vector<char>&IO_TIME)
{
    int time = 0;
    int NumOfProcess = 0;
    queue<int>readyCPU;
    queue<int>readyIO;
    while (true)
    {
        //check arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time == time && p[i].checkArrival == false) 
            {
                
                p[i].checkArrival = true;
                readyCPU.push(i);
            }
        }
        int id = 0;
        int id_io = 0;
        //each time, check readyCPU
        if(readyCPU.empty() == false) id = readyCPU.front();

        if(!readyCPU.empty() && p[id].CPU_time[0] == 0)
        {
            readyCPU.pop();
            if(p[id].IO_time.size() != 0)
            {
                readyIO.push(id);
            }
            else{
                p[id].finish_time = time;
                NumOfProcess++;
            }
            p[id].CPU_time.erase(p[id].CPU_time.begin());
        }
        if(readyIO.empty()==false) id_io = readyIO.front();
        if(!readyIO.empty() && p[id_io].IO_time[0] == 0)
        {
            readyIO.pop();
            if(p[id_io].CPU_time.size() != 0)
            {
                readyCPU.push(id_io);
            }
            else{
                p[id_io].finish_time = time;
                NumOfProcess++;
            p[id_io].IO_time.erase(p[id_io].IO_time.begin());
        }
        }
        if(NumOfProcess == n) break;


        if(!readyCPU.empty() == false)
        {
            CPU_TIME.push_back(char(id+1)+48);
            p[id].CPU_time[0]--;
        }
        else CPU_TIME.push_back('_');

        if(!readyIO.empty() == false)
        {
            p[id_io].IO_time[0]--;
            IO_TIME.push_back(char(id_io+1)+48);
        }
        else IO_TIME.push_back('_');
        time++;

    }
}

int main()
{
    vector<char>CPU_TIME;
    vector<char>IO_TIME;
    fin.open("input.txt");
    int n;
    Process p[4];
    readNormalFile(p, n);
    for( int i=0 ; i<n ; i++)
    {
        Print_Info_Processes(p[i]);
    }
    FCFS(p,n,CPU_TIME,IO_TIME);
    for(int i=0;i<CPU_TIME.size();i++)
    {
        cout<<CPU_TIME[i]<<" ";
    }
    return 0;
}

