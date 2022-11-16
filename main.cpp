/** Author Omar Mohammad **/
/** ------KNOWLEDGE is Power.. Share it with others ^_-  ------ **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;
class Process{
    int PID;
    string Name;
    int memory;
public:
    Process(string name, int pid, int mem): Name(name), PID(pid) ,memory(mem){}
    string getName(){return Name;}
    int getPID(){return PID;}
    int getMemory(){return memory;}
};

class TaskManager{
public:
    vector<Process> process;
    // function to add process
    void addProcess(Process p){
        process.push_back(p);
    }
    // function to print the task manager after modification
    void printTaskManager(){
        cout << "Name" << setw(38)  << "PID" << setw(18) << "Memory" << endl;
        cout << "================================================================" << endl;
        for (int i = 0; i < process.size(); i++){
            cout << process[i].getName() << setw(39 - process[i].getName().size() + 4) << process[i].getPID()
            << setw(18) << process[i].getMemory() << " KB" << endl;
        }

    }
    // sort the Process ID (PID) in ascending order
    void sortByPID(){
        sort(process.begin(), process.end(),
            [](Process &pr1, Process &pr2){return pr1.getPID() < pr2.getPID();});
    }
    // sort the Name of the process by name
    void sortByName(){
        sort(process.begin(), process.end(),
            [](Process &pr1, Process &pr2){return pr1.getName() < pr2.getName();});
    }
    // sort the memory use of the process in ascending order
    void sortByMemory(){
        sort(process.begin(), process.end(),
            [](Process &pr1, Process &pr2){return pr1.getMemory() > pr2.getMemory();});
    }


};

int main()
{
    TaskManager t1; // creating an object of Task manager
    ifstream readsFromFile; ofstream createsFile;
    createsFile.open("newFile.txt"); // create new File named newFile.txt
    createsFile.close(); // closing the file because we need it in another process
    system("tasklist > newFile.txt"); // command to copy the task list in a file
    readsFromFile.open("newFile.txt"); // opening the file in reading mode only
    string name, pid, memUsage;
    vector<string> process; // vector of process
    string word;
    // Escaping first three lines
    while(readsFromFile.get() != '\n');
    while(readsFromFile.get() != '\n');
    while(readsFromFile.get() != '\n');

    // storing the data in a vector
    while(true){
        if (readsFromFile >> word){
            process.push_back(word);
        }
        else break;
    }
    // adding process to the class operation
    for (int i = 0; i < process.size() - 1; i += 6){
        name = process[i];
        if (process[i] == "System" and process[i+1] == "Idle"){
            i += 2;
        }

        if (process[i] == "Memory"){
            i++;
        }
        pid = process[i + 1];
        memUsage = process[i + 4];
        // checking the place of ',' in memory use and deleting it
        int found = memUsage.find(',');
        // checks of it is found
        if (found != string::npos){
            memUsage.erase(found, 1);
        }
        int x = stoi(pid);      // converting the PID into integer
        int y = stoi(memUsage); //converting the PID into integer
        Process p(name, x, y);  // creating an object of process
        t1.addProcess(p);
        x = y = 0;
        name = pid = memUsage = "";
    }

    //t1.sortByPID();     // to be sorted by PID
    //t1.sortByName();    // to be sorted by Name
    //t1.sortByMemory();  // to be sorted by MEM usage

    t1.printTaskManager();
    readsFromFile.close();
    return 0;
}
