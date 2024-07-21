#include "TaskManager.h"

TaskManager::~TaskManager() {
    for (int i = 0; i < personAmount; i++) {
        delete persons[i];
    }
}

void TaskManager::assignTask(const string &personName, const Task &task) {
    for (int i = 0; i < personAmount; i++) {
        if (personName == (*persons[i]).getName()) {
            Task temp = task;
            temp.setId((*persons[i]).getTasks().length());
            (*persons[i]).assignTask(task);
            return;
        }
    }
    if (personAmount == MAX_PERSONS) {
        throw std::runtime_error("Task manager is full");
    } else {
        Task temp = task;
        temp.setId(0);
        persons[personAmount] = new Person(personName);
        (*persons[personAmount]).assignTask(temp);
        personAmount++;
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < personAmount; i++) {
        if (personName == (*persons[i]).getName()) {
            (*persons[i]).completeTask();
            return;
        }
    }
    throw std::runtime_error("Person isn't exist");
}

Task addPriority(Task task, int priority, TaskType type);

Task addPriority(Task task, int priority, TaskType type) {
    if (task.getType() == type) {
        return Task(task.getPriority() + priority, task.getType(),
                    task.getDescription());
    } else {
        return Task(task);
    }
}


void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for (int i = 0; i < personAmount; i++) {
        (*persons[i]).getTasks().apply([=](Task task) {
            return Task(
                    task.getPriority() + (task.getType() == type) * priority,
                    task.getType(),
                    task.getDescription());
        });
    }
}

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < personAmount; i++) {
        std::cout << (*persons[i]) << std::endl;
    }
}


SortedList<Task> TaskManager::mergeAll() const {
    SortedList<Task> all;
    for (int i = 0; i < personAmount; i++) {
        for (Task task: (*persons[i]).getTasks()) {
            all.insert(task);
        }
    }
    return all;
}

void TaskManager::printAllTasks() const {
    SortedList<Task> all = mergeAll();
    for (Task task: all) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> all = mergeAll();
    SortedList<Task> filtered = all.filter([=](Task task) {
        return task.getType() == type;
    });
    for (Task task: all) {
        std::cout << task << std::endl;
    }
}











