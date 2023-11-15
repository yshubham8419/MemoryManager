#include<Process.h>
#include<Reader.h>
#include<bits/stdc++.h>
using namespace std;

ProcessReader::ProcessReader(const string& file_name) {
    file.open(file_name);
    if (!file.is_open()) {
        cout << "File not found." << endl;
    }
}

ProcessReader::~ProcessReader() {
    if (file.is_open()) {
        file.close();
    }
}

process ProcessReader::read_next_process() {
    int size, execution_time;
    if (file >> size >> execution_time) {
        static int id_counter =1; // Return a default process if unable to read 1;
        return process(id_counter++, size, id_counter, execution_time); // Set arrival_time as 0
    }
    return process(0, 0, 0, 0); // Return a default process if unable to read
}
