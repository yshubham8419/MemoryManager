#include <fstream>
#include <Process.h> // Include the Process struct header

class ProcessReader {
private:
    std::ifstream file;

public:
    ProcessReader(const std::string& file_name);
    ~ProcessReader();
    process read_next_process();
};