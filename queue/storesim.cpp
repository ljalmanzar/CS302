//--------------------------------------------------------------------
//
//  Laboratory 7, Programming Exercise 1                   storesim.cs
//
//  Program implementation shell.
//
//--------------------------------------------------------------------

// Simulates the flow of customers through a line in a store.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"

// Use which ever implementation is currently configured.
#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif

using namespace std;

int main ()
{
#if LAB7_TEST1
    QueueLinked<int> custQ;      // Line (queue) of customers containing the
#else
    QueueArray<int> custQ;       // Line (queue) of customers containing the
#endif 				 //   time that each customer arrived and
                                 //   joined the line
    int simLength = 0,               // Length of simulation (minutes)
        minute = 0,                  // Current minute
        timeArrived = 0,             // Time dequeued customer arrived
        waitTime = 0,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0,         // Number of new arrivals
        randnum = 0;               // holder for generated number

    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand(7);

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.

    // while sim not done

    /**
    This is the main loop that will handle the whole simulation, always increases
    and decreases the simulation length.

    always takes someone out of the "line" if the line is not empty

    generates a random number that decides how many go into the line if any
    */
    while (minute <= simLength)
        {
                /// increment time by one minute
                minute ++;

                /// if queue not empty, dequeue
                if (!custQ.isEmpty())
                    {
                        timeArrived = custQ.dequeue();
                        waitTime = minute - timeArrived;
                        totalServed++;

                        if (waitTime > maxWait)
                            maxWait = waitTime;  

                        totalWait += waitTime;
                    }

                /// compute rand [0,4)
                randnum = rand()%4;
                
                /// if k==1 add one customer
                if (randnum == 1)
                    {
                        custQ.enqueue(minute);
                        numArrivals++;   
                    }

                /// if k==2 and two customers
                if (randnum == 2)
                    {
                        custQ.enqueue(minute); 
                        custQ.enqueue(minute);  
                        numArrivals+=2;
                    }

        }

    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}
