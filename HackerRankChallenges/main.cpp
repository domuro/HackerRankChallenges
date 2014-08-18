//
//  main.cpp
//  HackerRankChallenges
//
//  Created by Derek Omuro on 8/16/14.
//  Copyright (c) 2014 domuro. All rights reserved.
//
#include "projectEuler.h"

using namespace std;

int main(int argc, const char * argv[])
{
    // multiple input
    int T;
    cin >> T;
    while (T--) {
        unsigned long long n;
        cin >> n;
        cout << euler004((int)n) << endl;
    }
    return 0;
}