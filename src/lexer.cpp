#include <iostream>
#include "include/mio/mio.hpp"

using namespace std;

int handle_error(const error_code& error) 
{
    const auto& errmsg = error.message();
    cout << "Error mapping file: " << errmsg << ", exiting..." << endl;
    return error.value();
}

int main(int argc, char **argv) 
{
    string path = "test.txt";
    error_code error;

    mio::mmap_source ro_mmap;
    ro_mmap.map(path, error);
    if (error) { return handle_error(error); }

    // read
    for (auto& b : ro_mmap) {
        
    }

    // cleanup
    ro_mmap.unmap();

    return EXIT_SUCCESS;
}