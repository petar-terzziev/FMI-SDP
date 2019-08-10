#include <string>
#include "cmake-build-debug/Horo.h"

int main(int argc,char* argv[]) {


Horo opop(argv[1]);
std::string cmd;
while(true){
    if(cmd=="exit"){
        break;
    }
    std::cin>>cmd;
    std::cin.ignore();
    opop.proccess_command(cmd);
}
return 0;
}