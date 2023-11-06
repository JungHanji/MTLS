#pragma once
#include "AdtClasses.hpp"
#include <thread>
#include <mutex>

namespace nsc{

template<class RT, class PT, class... Args>
function<void(RT*, PT, Args...)> getWrapped(function<RT(PT, Args...)> func ){
    return [func](RT* result, PT arg, Args... args) {
        (*result) = func(arg, args...);
    };
}

template<class RT, class PT, class... Args>
function<void(RT*, PT, Args...)> getLockingWrapped(function<RT(PT, Args...)> func, mutex *tmutex){
    return [func, tmutex](RT* result, PT arg, Args... args) {
        tmutex->lock();
        (*result) = func(arg, args...);
        tmutex->unlock();
    };
}

template<class RT, class PT, class... Args>
class future{
    private:
    thread *this_thread = nullptr;
    function<RT(PT, Args...)> func;
    function<void(RT*, PT, Args...)> wrapped;
    function<void(RT*, PT, Args...)> wrapped_locking;
    mutex this_mutex;
    RT output;


    bool is_locking = false,
         is_deffered = false;

    

    public:
    
    future(function<RT(PT, Args...)> func, PT arg, Args... args, bool is_locking = false, bool is_deffered = false) : 
            func(func), is_locking(is_locking), is_deffered(is_deffered)
    {
        if(!is_deffered){
        if(!is_locking){
            wrapped = getWrapped<RT, PT, Args...>(func);
            this_thread = new thread(wrapped, &output, arg, args...);
        } else {
            wrapped_locking = getLockingWrapped<RT, PT, Args...>(func, &this_mutex);
            this_thread = new thread(wrapped_locking, &output, arg, args...);
        }
        }
    }
    future(){;}

    RT get(){
        if(!is_deffered)
            this_thread->join();
        else
            throw custom_exception("Cannot use method get(void) with deffered call");
        return output;
    }

    RT get(PT arg, Args... args){
        if(is_deffered){
            if(!is_locking){
                wrapped = getWrapped<RT, PT, Args...>(func);
                this_thread = new thread(wrapped, &output, arg, args...);
            } else {
                wrapped_locking = getLockingWrapped<RT, PT, Args...>(func, &this_mutex);
                this_thread = new thread(wrapped_locking, &output, arg, args...);
            }

            this_thread->join();
        } else {
            throw custom_exception("Cannot use method get(PT, Args...) with non-deffered call");
        }
        return output;
    }

    ~future() {
        this_thread->detach();
        delete this_thread;
    }
};

template<class T>
class _queue{
    private:
    std::thread *this_thread;
    vector<T> &input;
    vector<T> &output;
    function<void(vector<T>&, vector<T>&)> async_handler;
    int task_num;

    public:
    
    _queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler, int task_num):
           this_thread(this_thread), input(input), output(output), async_handler(async_handler), task_num(task_num){
        this_thread = new std::thread();
    }

    _queue(){
        ;
    }

    ~_queue(){
        this_thread->detach();
        delete this_thread;
    }

    void wait_until_done(){
        ;
    }
};

class async{
    public:
    template<class RT, class PT, class... Args>
    nsc::future<RT, PT> static call(function<RT(PT, Args...)> func, PT arg, Args... args){
        return nsc::future<RT, PT>(func, arg, args...);
    }
    
    template<class RT, class PT, class... Args>
    nsc::future<RT, PT> static lock_call(function<RT(PT, Args...)> func, PT arg, Args... args){
        return nsc::future<RT, PT>(func, arg, args..., true);
    }
    
    template<class RT, class PT, class... Args>
    nsc::future<RT, PT> static deffered_call(function<RT(PT, Args...)> func, PT arg, Args... args){
        return nsc::future<RT, PT>(func, arg, args..., false, true);
    }

    template<class RT, class PT, class... Args>
    nsc::future<RT, PT> static deffered_lock_call(function<RT(PT, Args...)> func, PT arg, Args... args){
        return nsc::future<RT, PT>(func, arg, args..., true, true);
    }

    template<class T>
    _queue<T> static create_queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler, int task_num){
        ;
    }
};
}