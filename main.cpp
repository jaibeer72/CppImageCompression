#include "Arguments.hpp"

int main(int argc , char* argv[]) {

    Args* appArgs = new Args(argc,argv);

    std::cout<< (appArgs->isRunnableConfig ? "this is a runnable config" : "this is not a runnable config");


    return 0;
}
