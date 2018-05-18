//CPSC 351 Assignment 2 Memory Management

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;


//Class to handle all of the inputs for incoming processes
class Process
{
public:
    int processid;
    int time_start;
    int time_end;
    int time_life;
    int memblock_count;
    int tot_memory;
    int turnaround;
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
	cout << "Turnaround Time: " << turnaround << endl;
    }
};

//Function to compare end times of all processes and choose the smallest
bool compareEndTime(const Process & a, const Process & b)
{
    // smallest end time comes first
    return a.time_end > b.time_end;
}

//Struct to handele memory block parameters
struct Memory_Block
{
    int start;
    int end;
    int process_number;
    int page_number;
    int total_size;
    int release_time;
    bool available;
};

int readFile(vector<Process> & process_queue, vector<int> & events);
void buildMemMap(vector<Memory_Block> & memory_block, int memory_size, int page_size);
bool checkAvailableMem(vector<Memory_Block> & memory_block, Process process, int page_size, vector<int> & pages);
bool checkForContMem(vector<Memory_Block> & memory_block, Process process, vector<int> &pages, int & page_number);
int addProcessToMem(vector<Memory_Block> & memory_block, Process process, vector<int> &pages);


int main()
{
    string file = "in1.txt";
    int process_count, choice;
    int memory_size = 0, page_size = 0, turnaround = 0, end_time = 0, size_of_process_queue = 0;
    vector<Process> process_queue, in_memory, ready_queue;
    vector<Memory_Block> memory_block;
    vector<int> events, pages;
    Process process;
    bool end_of_processes = false;
    
    
    cout << "Enter the memory size(Kbytes): ";
    cin >> memory_size;
    cout << "Enter the page size (1:100, 2:200, 3:400): ";
    cin >> choice;

    //Switch statement to handle user choice
    switch (choice)
    {
        case 1:
            page_size = 100;
            break;
        case 2:
            page_size = 200;
            break;
        case 3:
            page_size = 400;
            break;
    }

    process_count = readFile(process_queue, events);
    
    buildMemMap(memory_block, memory_size, page_size);
    
    //Build the process queue
    for (int time = 0; time < events.back() + 1; time++)
    {
        //cout << "time in miliseconds: " << time << endl;
        while (events[end_time] == time)
        {
            //get the first process in the queue
            if(process_queue.size() < 1)
            {
                end_of_processes = true;
            }
            
            if(end_of_processes == false)
            {
                process_queue.end();
                size_of_process_queue = (int)process_queue.size() - 1;
                
		//allocate process information to queue and Process class
                process.processid = process_queue[size_of_process_queue].processid;
                process.time_start = process_queue[size_of_process_queue].time_start;
                process.time_end = process_queue[size_of_process_queue].time_end;
                process.time_life = process_queue[size_of_process_queue].time_life;
                process.tot_memory = process_queue[size_of_process_queue].tot_memory;
		process.turnaround = process.time_end - process.time_start;
    	   }
            //release finished processes
            for(int i = 0; i < memory_block.size(); i++)
            {
                if(memory_block[i].release_time == time)
                {
                    memory_block[i].available = true;
                }
            }
            
            if (in_memory.size() > 0 && in_memory.back().time_end == time)
            {
                while(in_memory.back().time_end == time)
                {
                    cout <<"\nt = " << time << ": " << "\nRemoving Process: \n";
                    in_memory.back().printProcess();
                    in_memory.pop_back();
                }
                
            }
            
 	}	
   }
}
