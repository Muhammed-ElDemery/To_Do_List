#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class list {
    private :
        struct task;
        typedef task *link;
        struct task {
            string data;
            link next;
            bool completed = false;
            unsigned int index;
        };
        link current, tail, head;
    public :
        list();
        void add_task(string describtion);
        void view_tasks();
        void completed_task(unsigned int index);
        void remove(unsigned int index);
        unsigned int counter();
};

list :: list() {
    current = tail = head = NULL;
}

unsigned int list :: counter () {
    unsigned int index = 0;
    current = head;
    while(current != NULL) {
        index++;
        current->index = index;
        current = current->next;
    }
    return index;
}

void list :: add_task(string describtion) {
    link addnode = new task;
    addnode->data = describtion;
    addnode->next = NULL;
    if (head == NULL){
        head = addnode;
        addnode->index = 1;
    }
    else{
        tail->next = addnode;
        addnode->index = tail->index + 1;
    }
    tail = addnode;
}

void list :: view_tasks() {
    if (head == NULL) {
        cout << "There are no tasks to be showed! \n";
    }else {
    current = head;
        while(current != NULL) {
            if (current->completed) {
                cout << current->index << "- "<< current->data << " [completed]"<<endl;
            }else {
                cout << current->index << "- "<< current->data << " [pendding]"<<endl;
            }
            current = current->next;
        }
    }
}

void list :: completed_task(unsigned int index) {
    unsigned int number_of_tasks = counter();
    if (index > number_of_tasks) {
        cout << "Invalid task index \n";
        return;
    }
    current = head;
    while(current != NULL) {
        if (current->index == index) {
            current->completed = true;
        }
        current = current->next;
    }
    cout << "Task marked as completed. \n";
}

void list :: remove(unsigned int index) {
    unsigned int number_of_tasks = counter();
    if (index > number_of_tasks) {
        cout << "Invalid task index \n";
        return;
    } else if (head->index == index) {
        link temp = head;
        head = head->next;
        delete temp;
    } else {
        link prev = head;
        current = head->next;
        while(current != NULL) {
            if (current->index == index) {
                link temp = current;
                prev->next = current->next;
                delete temp;
                break;
            }
            prev = current;
            current = current->next;
        }
    }
    counter();
    cout << "Task removed \n";
}

int main()
{  
    list tasks;
    string describtion;
    unsigned int deter;
    unsigned int index;
    
    cout << "TO-DO List Manager (for codsoft intern) \n";
    while (1) {
        cout << "1. Add Task \n";
        cout << "2. View Tasks \n";
        cout << "3. Mark Task as Completed \n";
        cout << "4. Remove Task \n";
        cout << "5. Exit \n";
        cout << "Enter your choice : ";
        cin >> deter;
        cin.ignore();
        if (deter == 1)
        {
            cout << "Enter task description : ";
            getline(cin, describtion);
            tasks.add_task(describtion);
            cout << "Task added successfully! \n";
            cout << "----------------------------------\n";
        }else if (deter == 2) 
        {
            tasks.view_tasks();
            cout << "----------------------------------\n";
        }else if (deter == 3) 
        {
            if (tasks.counter() == 0) {
                cout << "There are no tasks! \n";
            }else {
                cout << "Enter task index : ";
                cin >> index;
                tasks.completed_task(index);
            }
            cout << "----------------------------------\n";
        }else if (deter == 4) 
        {
            if (tasks.counter() == 0) {
                cout << "There are no tasks to br removed! \n";
            }else {
                cout << "Enter task index : ";
                cin >> index;
                tasks.remove(index);
            }
            cout << "----------------------------------\n";
        }else if (deter == 5) {
            break;
        }else {
            cout << "Invalid choice! \n";
        }
    }
    return 0;
}