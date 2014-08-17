//
//  main.cpp
//  HackerRankChallenges
//
//  Created by Derek Omuro on 8/16/14.
//  Copyright (c) 2014 domuro. All rights reserved.
//

#include <iostream>
using namespace std;

// Project Euler #1: Multiples of 3 and 5
// https://www.hackerrank.com/contests/projecteuler/challenges/euler001
//
// Notes:  Based solution on the story of Gauss adding 1 to 100
// Solved: 8/16/14
unsigned long euler001helper(unsigned long multiple, unsigned long limit)
{
    // round limit down to nearest multiple
    limit = limit/multiple*multiple;
    // calculate sum of an even number of multiples
    unsigned long result = (multiple+limit)*(limit/(multiple*2));
    if (limit%(multiple*2) == multiple) {
        // there is an odd number of multiples (e.g. 15 by 5)
        // add half of the limit rounded up to nearest multiple to compensate
        result += (limit/2/multiple*multiple)+multiple;
    }
    return result;
}
unsigned long euler001(unsigned long n)
{
    unsigned long sum = 0;
    // add sum of multiples of 3 and 5
    sum += euler001helper(3, n-1);
    sum += euler001helper(5, n-1);
    // subtract the overlapping multiples of 15
    sum -= euler001helper(15, n-1);
    return sum;
}

// Project Euler #2: Even Fibonacci numbers
// https://www.hackerrank.com/contests/projecteuler/challenges/euler002
//
// Notes:  Uses dynamic programming
// Solved: 8/16/14
unsigned long long euler002(unsigned long long n)
{
    unsigned long long sum = 0;
    // use to store the three latest fibonacci numbers
    unsigned long long *fib = new unsigned long long [3] {1, 1, 0};
    for (unsigned long long i = 2; fib[2] <= n; i++) {
        // add current fib number if even
        sum += fib[2]%2?0:fib[2];
        // store the next fib number in fib[2]
        fib[2] = fib[0]+fib[1];
        // prepare to calculate the next next fib number
        fib[0] = fib[1];
        fib[1] = fib[2];
    }
    return sum;
}

int main(int argc, const char * argv[])
{
    // multiple input
    int T;
    cin >> T;
    while (T--) {
        unsigned long long n;
        cin >> n;
        cout << euler002(n) << endl;
    }
    return 0;
}