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
// Solved: 8/16/14
unsigned long euler001helper(int multiple, int limit)
{
    limit = limit/multiple*multiple;
    unsigned long result = (multiple+limit)*(limit/(multiple*2));
    if (limit%(multiple*2) == multiple) {
        result += (limit/2/multiple*multiple)+multiple;
    }
    // returns the sum of all multiples of a multiple up to a limit
    return result;
}
unsigned long euler001(int n)
{
    unsigned long sum = 0;
    sum += euler001helper(3, n-1);
    sum += euler001helper(5, n-1);
    sum -= euler001helper(15, n-1);
    return sum;
}

int main(int argc, const char * argv[])
{
    // Multiple input
    cout << "Enter the input:\n";
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << euler001(n) << endl;
    }
    return 0;
}