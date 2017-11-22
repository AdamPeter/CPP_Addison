#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <exception>

using namespace std;

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

int main()
{
    bool b_ex_18_1_1 = false;
    bool b_ex_18_1_2 = true;

    if(b_ex_18_1_1)
    {
        ex_18_1_1::main();
    }

    if(b_ex_18_1_2)
    {
        ex_18_1_2::main();
    }


    return 0;
}

