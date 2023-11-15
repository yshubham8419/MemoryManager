#include <Process.h>
#include <Reader.h>
#include <MemoryManager.h>
#include <set>

using namespace std;
multiset<process> running_process;
MemoryManager manager(500);

int main(){
    ProcessReader pr("./input/req.txt");
    process p = pr.read_next_process();
    int time = 0;
    while(!(p==null_process)){
        bool alocated =  manager.allocate(p);
        if(alocated){
            p.exit_time = time+p.execution_time;
            running_process.insert(p);
            p=pr.read_next_process();
            manager.display();
        }

        bool rn = false;
        while(running_process.size()>0 && time>=((running_process.begin())->exit_time)){
            manager.deallocate(*running_process.begin());
            running_process.erase(running_process.begin());
            rn  = true;
        }
        if(rn)
        manager.display();

        time++;
    }
}
