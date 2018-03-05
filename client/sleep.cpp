#include <chrono>
#include <thread>
#include <string>
using namespace std;

int main(int argc, char **argv){
    string::size_type sz;
    this_thread::sleep_for( std::chrono::nanoseconds(stol(argv[1], &sz)));

    return 0;
}
