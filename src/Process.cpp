// process.cpp

#include <Process.h>

// Definition of the constructor
process::process(int process_id, int process_size, int arrival_t, int exec_time) :
    id(process_id),
    size(process_size),
    arrival_time(arrival_t),
    execution_time(exec_time),
    exit_time(-1),
    memory_node(nullptr) {}

// Definition of null_process
process null_process(0, 0, 0, 0);

// Definition of the equality operator
bool operator==(const process& lhs, const process& rhs) {
    return lhs.id == rhs.id && lhs.size == rhs.size &&
           lhs.arrival_time == rhs.arrival_time &&
           lhs.execution_time == rhs.execution_time &&
           lhs.exit_time == rhs.exit_time;
}

bool process::operator<(const process& other) const {
    return exit_time < other.exit_time;
}