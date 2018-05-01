//CPSC 351 Assignment 2 Memory Management

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

class Process
{
public:
    int processid;
    int time_start;
    int time_end;
    int time_life;
    int memblock_count;
    int tot_memory;
    vector<int> memblocks;
    
    bool operator < (const Process & a) const
    {
        return time_start > a.time_start;
    }
    
    void printProcess() const
    {
        cout << "\nProcess id: " << processid << endl;
        cout << "Process Time Start: " << time_start << endl;
        cout << "Process Time End: " << time_end << endl;
        cout << "Process Time Life: " << time_life << endl;
        cout << "Total Memory: " << tot_memory << endl;
    }
};


int main()
{
    string file = "in1.txt";
    int process_count, choice;
    int memory_size = 0, page_size = 0, turnaround = 0, end_time = 0, size_of_process_queue = 0;

    
    
    cout << "Enter the memory size(Kbytes): ";
    cin >> memory_size;
    cout << "Enter the page size (1:100, 2:200, 3:400): ";
    cin >> choice;
}
