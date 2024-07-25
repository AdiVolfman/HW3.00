#include "TaskManager.h"

TaskManager::TaskManager() : personAmount(0), taskCounter(0) {}


void TaskManager::assignTask(const string &personName, const Task &task) {
    Task temp = task;
    temp.setId(taskCounter);
    //case: person is existed
    for (int i = 0; i < personAmount; i++) {
        if (personName == persons[i].getName()) {
            persons[i].assignTask(temp);
            taskCounter++;
            return;
        }
    }
    //case: person is not existed and the TaskManager is full
    if (personAmount == MAX_PERSONS) {
        throw std::runtime_error("Task manager is full");
    } else {
        //case: new person in the TaskManager
        persons[personAmount] = Person(personName);
        persons[personAmount].assignTask(temp);
        taskCounter++;
        personAmount++;
    }
}

void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < personAmount; i++) {
        if (personName == persons[i].getName()) {
            persons[i].completeTask();
            //taskCounter--;
            return;
        }
    }
    throw std::runtime_error("Person isn't exist");
}

Task addPriority(const Task &task, int priority, TaskType type);

Task addPriority(const Task &task, int priority, TaskType type) {
    Task newTask(task.getPriority() + (task.getType() == type) * priority,
                 task.getType(),
                 task.getDescription());
    newTask.setId(task.getId());
    return newTask;
}


void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for (int i = 0; i < personAmount; i++) {
        SortedList<Task> temp = persons[i].getTasks().apply(
                [=](const Task &task) {
                    return addPriority(task, priority, type);
                });
        persons[i].setTasks(temp);
    }
}

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < personAmount; i++) {
        std::cout << persons[i] << std::endl;
    }
}


SortedList<Task> TaskManager::mergeAll() const {
    SortedList<Task> all;
    for (int i = 0; i < personAmount; i++) {
        for (const Task &task: persons[i].getTasks()) {
            all.insert(task);
        }
    }
    return all;
}

void TaskManager::printAllTasks() const {
    SortedList<Task> all = mergeAll();
    for (const Task &task: all) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> all = mergeAll();
    SortedList<Task> filtered = all.filter([=](const Task &task) {
        return task.getType() == type;
    });
    for (const Task &task: filtered) {
        std::cout << task << std::endl;
    }
}













