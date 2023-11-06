#include <AdtClasses/Async.hpp>
#include <windows.h>

void handler(vector<int>& iv, vector<int>& ov){
    cout<<"handler sleep "<<getTimeT()<<endl;
    Sleep(100);
    cout<<"handler awake "<<getTimeT()<<endl;
    
    ov.push_back(*(iv.end()-1) * 2);
    iv.pop_back();
}

int main(){
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 9},
                output;
    auto queue = nsc::async::create_queue<int>(
        input, output, handler
    );

    cout<<"queue is working... "<<getTimeT()<<endl;

    queue.wait_until_done();
    printv(output);
}