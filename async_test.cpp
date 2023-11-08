#include <AdtClasses/Async.hpp>
using namespace adc;

bool is_prime (int x) {
    std::cout << "Calculating. Please, wait...\n";
    for (int i=2; i<x; ++i) {
        cout<<"is_prime: "<<getTime()<<endl;
        if (x%i==0) return false;
    }
    return true;
}

int main(){

    auto fut = nsc::async::call(
        is_prime,
        313222313
    );
    std::cout << "Checking whether 313222313 is prime.\n";
    // ...

    for(int i : range(10)){
        cout<<"main: "<<getTime()<<endl;
    }

    bool ret = fut.get();      // waits for is_prime to return

    if (ret) std::cout << "It is prime!\n";
    else std::cout << "It is not prime.\n";

    return 0;
}