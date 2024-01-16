#include <iostream>
using namespace std;

class Task{

    public:  
    string datetime;
    string desc;
    bool done;

    Task(){
        this->datetime = "";
        this->desc = "";
        this->done = false;
    }

    Task(string datetime, string desc){
        this->datetime = datetime;
        this->desc = desc;
        this->done = false;
    }

    void finished();

};

void Task::finished(){
    this->done = true;
}

class Node{
    public:
    Task item;
    Node* next;

    Node(){
        this->next = nullptr;
    }

    Node(Task item){
        this->item = item;
        this->next = nullptr;
    }
};

class LSE{
    public:
    
};

void printTask(Task t){
    cout << t.datetime << ", ";
    cout << t.desc << ", ";
    cout << (t.done ? "done" : "to do") << "\n";
}

void clearTask(Task &t){
    t.datetime = "";
    t.desc = "";
    t.done = false;
}

int main(){

    Task t1("28/10/2023 8:00", "Wake up");
    Task t2("29/10/2023 10:00", "take a shower");
    Task t3("31/10/2023 14:00", "Go to class");
    Task t4("30/10/2023 18:00", "Go to the gym");

    printTask(t2);

    // LSE lse;
    /*lse.add(t1);
    lse.add(t2);
    lse.add(t3);
    lse.add(t4);*/

    // lse.print();

    return 0;
}
