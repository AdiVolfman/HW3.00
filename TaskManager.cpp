#include "TaskManager.h"

TaskManager::TaskManager() : personAmount(0), taskCounter(0) {
    for (int i = 0; i < MAX_PERSONS; ++i) {
        persons[i] = nullptr;
    }
}

TaskManager::~TaskManager() {
    for (int i = 0; i < personAmount; i++) {
        delete persons[i];
    }
}

void TaskManager::assignTask(const string &personName, const Task &task) {
    Task temp = task;
    temp.setId(taskCounter);
    for (int i = 0; i < personAmount; i++) {
        if (personName == (*persons[i]).getName()) {
            (*persons[i]).assignTask(temp);
            taskCounter++;
            return;
        }
    }
    if (personAmount == MAX_PERSONS) {
        throw std::runtime_error("Task manager is full");
    } else {
        persons[personAmount] = new Person(personName);
        (*persons[personAmount]).assignTask(temp);
        taskCounter++;
        personAmount++;
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < personAmount; i++) {
        if (personName == (*persons[i]).getName()) {
            (*persons[i]).completeTask();
            //taskCounter--;
            return;
        }
    }
    throw std::runtime_error("Person isn't exist");
}

Task addPriority(Task &task, int priority, TaskType type);

Task addPriority(Task &task, int priority, TaskType type) {
    Task newTask(task.getPriority() + (task.getType() == type) * priority,
                 task.getType(),
                 task.getDescription());
    newTask.setId(task.getId());
    return newTask;
}


void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for (int i = 0; i < personAmount; i++) {
        SortedList<Task> temp = (*persons[i]).getTasks().apply([=](Task &task) {
            return addPriority(task, priority, type);
        });
        (*persons[i]).setTasks(temp);
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
    for (Task task: filtered) {
        std::cout << task << std::endl;
    }
}













