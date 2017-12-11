#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <exception>
#include <mutex>
#include <array>
#include <condition_variable>
#include <queue>
#include <atomic>

using namespace std;

// async and future
namespace ex_18_1_1
{
   
    int do_something(char c)
    {
        default_random_engine dre(c);
        uniform_int_distribution<int> id(10,1000);

        for(int i = 0; i < 10; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }

        return c;
    }

    int func1()
    {
        return do_something('.');
    }

    int func2()
    {
        return do_something('+'); 
    }

     /*
     * Main function for chapter 18.1.1
     */
    int main()
    {
        cout << "starting func1() in background and func2() in foreground\n";

        future<int> result1(async(func1)); // try starting in a separate thread

        int result2 = func2(); // call in main thread

        int result = result1.get() + result2;

        cout << "result = " << result << endl;

        return result;
    }


}

// Polling
namespace ex_18_1_2
{
    void do_something(char c)
    {
        default_random_engine dre(c);
        uniform_int_distribution<int> id(10,1000);

        for(int i = 0; i < 10; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }

    }

    void main()
    {
        cout << "Example 18.1.2\n";
        cout << "starting two operations at once" << endl;

        auto f1 = async([]{ do_something('.');});
        auto f2 = async([]{ do_something('+');});

        // if at least one of the background tasks is running
        if(f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
            f2.wait_for(chrono::seconds(0)) != future_status::deferred)
        {
            while(f1.wait_for(chrono::seconds(0)) != future_status::ready &&
                f2.wait_for(chrono::seconds(0)) != future_status::ready)
            {
                this_thread::yield();
            }
        }

        cout << endl;
        try {
            f1.get();
            f2.get();
        }
        catch(const exception& e)
        {
            cout << "\nException: " << e.what() << endl;
        }

        cout << "\ndone" << endl;
     }
}

// Shared future
namespace ex_18_1_3
{
    int query_number()
    {
        cout << "read number: ";
        int num = 0;
        cin >> num;

        if(!cin) throw runtime_error("no number read");

        return num;
    }

    void work(char c, shared_future<int> f)
    {
        try 
        {
            int num = f.get(); // this will be the result of query_number
            
            for(int i = 0; i < num; ++i)
            {
                this_thread::sleep_for(chrono::milliseconds(100));
                cout.put(c).flush();
            }
        }
        catch (const exception& e)
        {
            cerr << "Exception in: " << this_thread::get_id() << ": " << e.what() <<endl;
        }
    }

    void main()
    {
        try
        {
            shared_future<int> f = async(query_number);

            auto f1 = async(launch::async, work,'.', f);
            auto f2 = async(launch::async, work,'+', f);
            auto f3 = async(launch::async, work,'=', f);

            f1.get();
            f2.get();
            f3.get();
        }
        catch (const exception& e)
        {
            cout << "Exception: " << e.what() << endl;
        }

        cout << "\ndone" << endl;

    }
}

namespace ex_18_2_1
{
    void work(int num, char c)
    {
        try
        {
            default_random_engine dre(c*42);
            uniform_int_distribution<int> id(10,1000);

            for(int i = 0; i < 10; ++i)
            {
                this_thread::sleep_for(chrono::milliseconds(id(dre)));
                cout.put(c).flush();
            }
        }
        catch(const exception& e)
        {
            cerr << "exception: " << this_thread::get_id() << ": " << e.what() << endl;
        }
        catch(...)
        {
            cerr << "exception: " << this_thread::get_id() << endl;
        }
    }

    void main()
    {
        try
        {
            thread t1(work, 5, '.');

            cout << "started work" << endl;

            for( int i = 0; i < 5; ++i )
            {
                thread t(work, 10, 'a'+i);
                cout << "detaching: " << t.get_id() << endl;
                t.detach();
            }

            cin.get();

            t1.join();
        }
        catch(const exception& e)
        {
            cerr << "exception: " << e.what() << endl;
        }
    }
}

namespace ex_18_2_2
{
    void work(std::promise<std::string>& p)
    {
        try
        {
            std::cout << "read char ('x' for exception): ";
            char c = std::cin.get();
            if(c == 'x')
            {
                throw std::runtime_error(std::string("char ") + c + " read");
            }

            std::string s = std::string("char " ) + c + "processed";
            p.set_value(std::move(s)); // causes ready state!
        }
        catch(...)
        {
            p.set_exception(current_exception()); // causes ready state
        }
    }

    void main()
    {
        try
        {
            std::promise<std::string> p;
            std::thread t(work, std::ref(p));

            t.detach();

            future<string> f(p.get_future());

            std::cout << "result: " << f.get() << std::endl;
        }
        catch(...)
        {
            std::cerr << "exception " << endl;
        }
    }
}

namespace ex_18_5_1
{
    mutex print_mutex;

    void Print(const std::string& s)
    {
        std::lock_guard<std::mutex> l(print_mutex);
        for(char c : s)
        {
            cout.put(c);
        }

        cout << endl;
    } // unlocked here

    int main()
    {
        auto f1 = async(launch::async, Print, "Hello from first thread. ");
        auto f2 = async(launch::async, Print, "Hello from second thread. ");
        Print("Hello from the main thread. ");

        return 0;
    }
}

namespace ex_18_5_1_2
{
    bool ready_flag;
    mutex ready_mutex;

    void thread1()
    {
        {
            this_thread::sleep_for(chrono::milliseconds(200));
            lock_guard<mutex> lg(ready_mutex);
            cout << "Getting ready. " << endl;
            ready_flag = true;
        }
    }

    void thread2()
    {
        {
            unique_lock<mutex> ul(ready_mutex);
            while(!ready_flag)
            {
                ul.unlock();
                // Give the ready thread a chance at the lock.  
                this_thread::yield();
                this_thread::sleep_for(chrono::milliseconds(100));
                ul.lock();
            }

            cout << "ready!!";

         }
     }

     void main()
     {
         auto f1 = async(launch::async, thread1);
         auto f2 = async(launch::async, thread2);

         f1.wait();
         f2.wait();
     }
}

namespace ex_18_5_2
{

    mutex m1;
    mutex m2;
    
    array<int,10> array1;
    array<int,10> array2;

    void work1()
    {
        {
            lock_guard<mutex> lg(m1);

            for(int i = 0; i < array1.size(); ++i)
            {
                array1[i] = i*2;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
    }

    void work2()
    {
        {
            lock_guard<mutex> lg(m2);
            for(int i = 0; i < array2.size(); ++i)
            {
                array2[i] = i*2+1;
                this_thread::sleep_for(chrono::milliseconds(110));
            }

        }
    }

    void main()
    {
        auto f1 = async(launch::async, work1);
        auto f2 = async(launch::async, work2);

        while(std::try_lock(m1,m2) >= 0)
        {
            this_thread::yield();
            this_thread::sleep_for(chrono::milliseconds(200));
        }

        {
            std::lock_guard<mutex> l1(m1, adopt_lock);
            std::lock_guard<mutex> l2(m2, adopt_lock);

            for(int i = 0; i < array1.size(); ++i)
            {
                cout << array1[i] << endl;
                cout << array2[i] << endl;
            }
        }

    }
}

namespace ex_18_6_1
{
    bool ready_flag;
    mutex ready_mutex;
    condition_variable condition;

    void thread1()
    {
        cout << "<return>" << endl;
        cin.get();

        {
            std::lock_guard<mutex> lg(ready_mutex);
            ready_flag = true;
        }

        condition.notify_one();
    }

    void thread2()
    {
        {
            std::unique_lock<mutex> ul(ready_mutex);
            condition.wait(ul, [] { return ready_flag;});
        }

        cout << "done" << endl;

    }

    void main()
    {
        auto f1 = async(launch::async, thread1);
        auto f2 = async(launch::async, thread2);

        f1.wait();
        f2.wait();
    }

}

namespace ex_18_6_2
{
    queue<int> q;
    mutex mq;
    condition_variable cond;

    void provider(int val)
    {
        for( int i = 0; i < 6; ++i)
        {
            {
                std::lock_guard<mutex> lg(mq);
                q.push(val+i);
            }
            cond.notify_one();

            this_thread::sleep_for(chrono::milliseconds(val));
        }
    }

    void consumer(int num)
    {
        while(true)
        {

            int val;

            {
                std::unique_lock<mutex> ul(mq);
                cond.wait(ul, []{return !q.empty();});

                val = q.front();
                q.pop();
            }

            cout << "consumer: " << num << ": " << val << endl;
        }
    }

    void main()
    {
        vector<future<void>*> futures;
        auto p1 = async(launch::async, provider, 100);
        auto p2 = async(launch::async, provider, 300);
        auto p3 = async(launch::async, provider, 500);

        auto c1 = async(launch::async, consumer, 1);
        auto c2 = async(launch::async, consumer, 2);
        
        futures.push_back(&p1);
        futures.push_back(&p2);
        futures.push_back(&p3);
        futures.push_back(&c1);
        futures.push_back(&c2);

        for(auto p = futures.begin(); p != futures.end(); ++p)
        {
            (*p)->wait();
        }

    }
}

namespace ex_18_7_1
{
    long data;
    atomic<bool> ready_flag(false);// doesn't guarantee value.

    void provider()
    {
        cout << "<return>" << endl;
        cin.get();

        data = 42;

        ready_flag.store(true);
    }

    void consumer()
    {
        while(!ready_flag.load())
        {
            cout.put('.').flush();
            this_thread::sleep_for(chrono::milliseconds(200));
        }

        cout << data << endl;
    }

    void main()
    {
        auto p = async(launch::async, provider);
        auto c = async(launch::async, consumer);
        
        p.wait();
        c.wait();
    }

}


int main()
{
    bool b_ex_18_1_1 = false;
    bool b_ex_18_1_2 = false;
    bool b_ex_18_1_3 = false;
    bool b_ex_18_2_1 = false;
    bool b_ex_18_2_2 = false;
    bool b_ex_18_5_1 = false;
    bool b_ex_18_5_1_2 = false;
    bool b_ex_18_5_2 = false;
    bool b_ex_18_6_1 = false;
    bool b_ex_18_6_2 = false;
    bool b_ex_18_7_1 = true;

    if(b_ex_18_1_1)
    {
        ex_18_1_1::main();
    }

    if(b_ex_18_1_2)
    {
        ex_18_1_2::main();
    }

    if(b_ex_18_1_3)
    {
        ex_18_1_3::main();
    }
    
    if(b_ex_18_2_1)
    {
        ex_18_2_1::main();
    }

    if(b_ex_18_2_2)
    {
        ex_18_2_2::main();
    }

    if(b_ex_18_5_1)
    {
        ex_18_5_1::main();
    }

    if(b_ex_18_5_1_2)
    {
        ex_18_5_1_2::main();
    }

    if(b_ex_18_5_2)
    {
        ex_18_5_2::main();
    }

    if(b_ex_18_6_1)
    {
        ex_18_6_1::main();
    }

    if(b_ex_18_6_2)
    {
        ex_18_6_2::main();
    }

    if(b_ex_18_7_1)
    {
        ex_18_7_1::main();
    }

    return 0;
}

