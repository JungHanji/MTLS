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

template<class T>
function<void(vector<T>&, vector<T>&)> makeLocking(function<void(vector<T>&, vector<T>&)> func, mutex *tmutex){
    return [func, tmutex](vector<T>& iv, vector<T>& ov) {
        tmutex->lock();
        func(iv, ov);
        tmutex->unlock();
    };
}

template<class RT, class PT, class... Args>
class future{
    private:
    std::unique_ptr<std::thread> this_thread;
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
            this_thread = std::make_unique<std::thread>(wrapped, &output, arg, args...);
        } else {
            wrapped_locking = getLockingWrapped<RT, PT, Args...>(func, &this_mutex);
            this_thread = std::make_unique<std::thread>(wrapped_locking, &output, arg, args...);
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
                this_thread = std::make_unique<std::thread>(wrapped, &output, arg, args...);
            } else {
                wrapped_locking = getLockingWrapped<RT, PT, Args...>(func, &this_mutex);
                this_thread = std::make_unique<std::thread>(wrapped_locking, &output, arg, args...);
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
    std::unique_ptr<std::thread> this_thread;
    std::mutex this_mutex;
    vector<T> &input;
    vector<T> &output;
    function<void(vector<T>&, vector<T>&)> async_handler;

    public:
    
    _queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler):
           input(input), output(output), async_handler(async_handler){
        async_handler = makeLocking(async_handler, &this_mutex);
        this_thread = std::make_unique<std::thread>(async_handler, std::ref(input), std::ref(output));
    }

    void run_detached(){ this_thread->detach(); }
    void wait_until_done(){ this_thread->join(); }

    _queue(){;}

    ~_queue(){
        if (this_thread->joinable()) {
            this_thread->detach();
        }
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
    nsc::_queue<T> static create_queue(vector<T> &input, vector<T> &output, function<void(vector<T>&, vector<T>&)> async_handler){
        return nsc::_queue(input, output, async_handler);
    }
};
}