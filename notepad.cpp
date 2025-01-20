#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string title;
    string description;
};

vector<Task> tasks;

void saveTasksToFile() {
    ofstream file("tasks.txt");
    for (auto& task : tasks) {
        file << task.title << endl;
        file << task.description << endl;
    }
    file.close();
}

void loadTasksFromFile() {
    ifstream file("tasks.txt");
    if (file.is_open()) {
        tasks.clear();
        Task task;
        while (getline(file, task.title)) {
            getline(file, task.description);
            tasks.push_back(task);
        }
        file.close();
    }
}

void addTask() {
    Task task;
    cout << "Enter task title: ";
    getline(cin, task.title);
    cout << "Enter task description: ";
    getline(cin, task.description);
    tasks.push_back(task);
    saveTasksToFile();
}

void viewTasks() {
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].title << endl;
    }

    int choice;
    cout << "Enter the number of the task to view details, or 0 to return: ";
    cin >> choice;
    cin.ignore();
    if (choice > 0 && choice <= tasks.size()) {
        Task& task = tasks[choice - 1];
        cout << "Task description: " << task.description << endl;
    }
}

void deleteTask() {
    viewTasks();
    int choice;
    cout << "Enter the number of the task to delete, or 0 to return: ";
    cin >> choice;
    cin.ignore();
    if (choice > 0 && choice <= tasks.size()) {
        tasks.erase(tasks.begin() + choice - 1);
        saveTasksToFile();
        cout << "Task deleted successfully." << endl;
    }
}

int main() {
    loadTasksFromFile();
    int choice;
    do {
        cout << "1. Add task\n";
        cout << "2. View tasks\n";
        cout << "3. Delete task\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
        }
    } while (choice != 0);
    return 0;
}
