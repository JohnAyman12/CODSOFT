#include<iostream>
#include<limits>
#include<fstream>
#include <cstring>

// Tasks.txt contains pending tasks
// Completed.txt contains completed tasks

using namespace std;

int* viewTasks()
{
    // opening files
    ifstream tasksListFile("Tasks.txt");
    string tasksListStr;
    ifstream compsListFile("Completed.txt");
    string compsListStr;

    if (!tasksListFile)
        cout << "Error opening the file." << endl;
    if (!compsListFile)
        cout << "Error opening the file." << endl;

    // Checking if file is empty
    if(!getline(tasksListFile, tasksListStr) && !getline(compsListFile, compsListStr))
        cout << "Your list is empty" << endl;
    else
        cout << "Your list contains the following: " << endl;

    tasksListFile.seekg(0, ios::beg);
    compsListFile.seekg(0, ios::beg);
    static int counter[2] = {0, 0}; // this array is used in removeTask() function
    int counter0 = 0, counter1 = 0;

    // Displaying the list
    if(getline(tasksListFile, tasksListStr))
        cout << "Pending: " << endl;
    tasksListFile.seekg(0, ios::beg);
    while(getline(tasksListFile, tasksListStr))
    {
        cout << ++counter0 << ")";
        cout << tasksListStr << endl;
    }

    if(getline(compsListFile, compsListStr))
        cout << "Completed: " << endl;
    compsListFile.seekg(0, ios::beg);
    while(getline(compsListFile, compsListStr))
    {
        cout << ++counter1 << ")";
        cout << compsListStr << endl;
    }

    tasksListFile.close();
    compsListFile.close();
    cout << "----------------------------------------------" <<endl;
    counter[0] = counter0;
    counter[1] = counter1;
    return counter; // this return is used in removeTask() function that represents number of tasks in each section
}

void addTask()
{
    ofstream tasksListFile("Tasks.txt", ios::app);
    string tasksListStr;
    cout << "Enter task: ";
    cin >> tasksListStr;
    tasksListFile << tasksListStr << endl;
    tasksListFile.close();
    cout << "----------------------------------------------" << endl;
}

void removeTask()
{
    // Displaying the list using viewTasks function and getting number of tasks in each section
    int *tasksAv = viewTasks();
    int listCount = 0, in, i;
    char fileName[100];
    string temp;
    ifstream listFile;

    //If the two sections of tasks are available, the user chooses which section he wants to delete from
    if(tasksAv[0] > 0 && tasksAv[1] > 0)
    {
        cout << "You want to delete a completed task or a pending task ?" << endl;
        cout << "1)Pending" << endl << "2)Completed" << endl;
        cout << "Enter the number of your choice: ";
        cin >> in;
        while(cin.fail() || in > 2 || in < 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter the number of your choice: ";
            cin >> in;
        }
        switch (in)
        {
        case 1:
        {
            listFile.open("Tasks.txt", ios::app);
            strcpy(fileName, "Tasks.txt");
            listCount = tasksAv[0];
            break;
        }
        case 2:
        {
            listFile.open("Completed.txt", ios::app);
            strcpy(fileName, "Completed.txt");
            listCount = tasksAv[1];
            break;
        }
        }
    } // If only one section of tasks is available, the user chooses deletes the task from it
    else if(tasksAv[0] > 0)
    {
        listFile.open("Tasks.txt", ios::app);
        strcpy(fileName, "Tasks.txt");
        listCount = tasksAv[0];
    }
    else if(tasksAv[1] > 0)
    {
        listFile.open("Completed.txt", ios::app);
        strcpy(fileName, "Completed.txt");
        listCount = tasksAv[1];
    }
    else
        return;

    if (!listFile) // Making sure that we accessed the file successfully
        cout << "Error opening the file." << endl;

    // Choosing the task user wants to delete
    cout << "Enter the number of task you want to delete: ";
    cin >> in;
    while(cin.fail() || in > listCount || in < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, enter the number of your choice: ";
        cin >> in;
    }

    // Performing the deletion proccess
    fstream tempfile("Temp.txt", ios::app);

    for(i = 1; i < in; i++)
    {
        getline(listFile, temp);
        tempfile << temp << endl;
    }
    getline(listFile, temp);
    i++;
    for(i; i <= listCount; i++)
    {
        getline(listFile, temp);
        tempfile << temp << endl;
    }

    listFile.close();
    tempfile.close();
    remove(fileName);
    rename("Temp.txt", fileName);
    cout << "----------------------------------------------" << endl;
}

void markCompleted()
{
    // opening files
    ifstream tasksListFile("Tasks.txt");
    ofstream compsListFile("Completed.txt", ios::app);
    string taskStr;
    int in, i = 0;

    if (!tasksListFile)
        cout << "Error opening the file." << endl;
    if (!compsListFile)
        cout << "Error opening the file." << endl;

    // Checking if file is empty
    if(!getline(tasksListFile, taskStr))
    {
        cout << "Your list is empty" << endl;
        return;
    }
    else
        cout << "Your pending tasks list contains the following: " << endl;

    // Displaying the list
    tasksListFile.seekg(0, ios::beg);
    int counter = 0;
    while(getline(tasksListFile, taskStr))
    {
        cout << ++counter << ")";
        cout << taskStr << endl;
    }
    tasksListFile.close();

    // Choosing the task user wants to mark as completed
    cout << "Choose the number of task you want to mark as completed: ";
    cin >> in;
    while(cin.fail() || in > counter || in < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, enter the number of task you want to mark as completed: ";
        cin >> in;
    }

    // Performing the process of marking as copmleted
    ofstream tempFile("Temp.txt");
    if (!tempFile)
        cout << "Error opening the file." << endl;

    ifstream tasksListFile2("Tasks.txt");
    if (!tasksListFile2)
        cout << "Error opening the file." << endl;

    for(i = 1; i < in; i++)
    {
        getline(tasksListFile2, taskStr);
        tempFile << taskStr << endl;
        cout << taskStr << "here1" << endl;
    }
    getline(tasksListFile2, taskStr);
    compsListFile << taskStr << endl;
    i++;
    for(i; i <= counter; i++)
    {
        getline(tasksListFile2, taskStr);
        tempFile << taskStr << endl;
        cout << taskStr << "here2" << endl;
    }

    tasksListFile2.close();
    compsListFile.close();
    tempFile.close();
    remove("Tasks.txt");
    rename("Temp.txt", "Tasks.txt");
    cout << "----------------------------------------------" << endl;
}

int main()
{
    cout << "***TO-DO LIST***"<< endl << endl;
    bool exit = false;
    while(!exit)
    {
        cout << "Chose an operation to do to your list: " << endl;
        cout << "1) View tasks" << endl << "2) Add task" << endl << "3) Remove task" << endl << "4) Mark task as completed" << endl << "5) Exit" << endl;

        cout << "Enter the number of your choice: ";
        int in;
        cin >> in;
        while(cin.fail() || in > 5 || in < 1)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, enter the number of your choice: ";
            cin >> in;
        }
        switch (in)
        {
        case 1:
            viewTasks();
            break;
        case 2:
            addTask();
            break;
        case 3:
            removeTask();
            break;
        case 4:
            markCompleted();
            break;
        case 5:
            exit = true;
            break;
        }
    }
    cout << "See you later!";
    return 0;
}
