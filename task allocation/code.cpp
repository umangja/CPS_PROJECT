// code author: Dhruva Mahajan
 
#include<bits/stdc++.h> 
using namespace std;
 
#define ll long long  
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define tr(container, it) for(auto it = container.begin(); it != container.end(); it++)
#define bitcount(a) __builtin_popcount(a) // set bits (add ll)
#define testcase(t) int t;cin>>t;while(t--)
 


class Task {
private:
    int deadline;
    int computeTime;
public:
    string name;
    Task(int deadline, int computeTime, string name):	
        deadline(deadline), computeTime(computeTime), name(move(name)) {}
    void execute();
    int getSlackTime(int currentTime) const;
    bool isOver() const;
};


void Task::execute() {
    printf("run %s\n", name.c_str());
    computeTime--;
}

int Task::getSlackTime(int currentTime) const {
    return ( deadline - currentTime ) - computeTime;
}

bool Task::isOver() const {
    return computeTime == 0;
}


class Scheduler {
private:
    int currentTime = 0;
    deque<Task> tasks;
public:
    explicit Scheduler(deque<Task> tasks) : tasks(move(tasks)) {}
    void run();
};



void Scheduler::run() {
    while (! tasks.empty()) {
        auto task = this->tasks.begin();
        auto lowestSlackTimeTask = task;

        while (task != this->tasks.end()) {

            if (task->isOver()) {
                task = tasks.erase(task);
            }
            else {
                int lowestSlackTime = lowestSlackTimeTask->getSlackTime(currentTime);
                int slackTime = task->getSlackTime(currentTime);

                if (lowestSlackTime > slackTime) lowestSlackTimeTask = task;

                task++;
            }
        }

        lowestSlackTimeTask->execute();

        currentTime++;
    }
}


int main(){
 
	fastio;
 
 	// deadline, compute time, name of task.
	deque<Task> tasks = {
		Task(10, 7, "test1"),
		Task(21, 3, "test2"),
		Task(6, 1, "test3")
	};
 
 	Scheduler scheduler = Scheduler(tasks);
 	scheduler.run();
	
	return 0;
}

