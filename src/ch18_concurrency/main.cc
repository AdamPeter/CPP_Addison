#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <exception>

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

int main()
{
    bool b_ex_18_1_1 = false;
    bool b_ex_18_1_2 = false;
    bool b_ex_18_1_3 = false;
    bool b_ex_18_2_1 = false;
    bool b_ex_18_2_2 = true;

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

    return 0;
}

