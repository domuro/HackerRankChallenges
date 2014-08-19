//
//  projectEuler.cpp
//  HackerRankChallenges
//
//  Created by Derek Omuro on 8/17/14.
//  Copyright (c) 2014 domuro. All rights reserved.
//

#include "projectEuler.h"

using namespace std;

// Project Euler #1: Multiples of 3 and 5
// https://www.hackerrank.com/contests/projecteuler/challenges/euler001
//
// Based on the story of Gauss adding 1 to 100
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
// Uses dynamic programming
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

// Project Euler #3: Largest prime factor
// https://www.hackerrank.com/contests/projecteuler/challenges/euler003
//
// Uses Sieve of Eratosthenes to find primes
// Short circuts when no divisible prime is found less than or equal to the square root
// Solved: 8/17/14
unsigned long long euler003(unsigned long long n)
{
    unsigned long long biggestPrime = 2, root = (unsigned long long)sqrt(n), primes[root+1], j;
    // primes array contains [0, n]
    for (unsigned long long i = 0; i <= root; i++) primes[i] = i;
    while (true) {
        // divide n if possible
        while (n%biggestPrime == 0) n /= biggestPrime;
        // if dividing n by the biggest prime equals 1, then we have found the biggest prime
        if (n == 1) return biggestPrime;
        // save square root to avoid recalculations
        root = (unsigned long long)sqrt(n);
        // apply Sieve of Eratosthenes by setting composite numbers to 0
        for (j = biggestPrime; j <= root; j += biggestPrime) primes[j] = 0;
        // find next biggest prime (composite numbers have been set to 0)
        while (!primes[++biggestPrime])
            // if next biggest prime is bigger than root, the next divisible biggest prime is itself
            if (biggestPrime > root) return n;
    }
}

// Project Euler #4: Largest palindrome product
// https://www.hackerrank.com/contests/projecteuler/challenges/euler004
//
// Brute force approach
// Solved: 8/17/14
int euler004(int n)
{
    int i;
    // calculate largest palindrome less than or equal to n
    while (n%10 != n/100000) n--;
    while (n%100/10 != n/10000%10) n-=10;
    while (n%1000/100 != n/1000%10) n-=100;
    // loop over all smaller palindromes
    while (n/1000 > 100) {
        // one multiple must be less than or equal to the square root
        for (i = (int)sqrt(n); i >= 100; i--)
            // return palindrome if a multiple is found and the quotient is three digits.
            if (n%i==0 && n/i < 1000) return n;
        // observe that to find the next smaller palindrome we must subtract by 1100, 110, or 11
        for (i = 1; i <= n%1000; i*=10);
        n -= i/10*11;
    }
    return -1;
}

// Project Euler #5: Smallest multiple
// https://www.hackerrank.com/contests/projecteuler/challenges/euler005
//
// Uses Sieve of Eratosthenes to find primes
// Solved: 8/18/14
unsigned long long euler005(int n)
{
    // find all prime numbers below n using Sieve of Eratosthenes
    int numbers[n+1], primes[n/2+1], counter, primeCount = 0;
    for (counter = 2; counter <= n; counter++) numbers[counter] = counter;
    for (int prime = 2; prime <= (int)sqrt(n); prime++)
        if (numbers[prime])
            for (int multiple = prime*2; multiple <= n; multiple += prime) numbers[multiple] = 0;
    for (int i = 2, counter = 0; i <= n; i++){
        if (numbers[i]){
            primes[counter++] = numbers[i];
        }
        primeCount = counter;
    }
    
    // track prime factorization of each number
    int maxPrimeFactorization[primeCount];
    int primeFactorization[primeCount];
    for (int i = 0; i < primeCount; i++) {
        maxPrimeFactorization[i] = 0;
        primeFactorization[i] = 0;
    }
    
    // find prime factorization of each number
    for (int i = 2; i <= n; i++) {
        for (int j = 0, k = i; primes[j] && k != 1; j++) {
            while (k%primes[j]==0){
                k/=primes[j];
                primeFactorization[j]++;
            }
        }
        for (int j = 0; j < primeCount; j++) {
            // store max occurances of each prime factor
            maxPrimeFactorization[j] = max(maxPrimeFactorization[j], primeFactorization[j]);
            primeFactorization[j] = 0;
        }
    }
    
    // calculate lcm using the maximum occurances of each prime factor
    unsigned long long result = 1;
    for (int i = 0; i < primeCount; i++) {
        result *= pow(primes[i], maxPrimeFactorization[i]);
    }
    return result;
}

// Project Euler #6: Sum square difference
// https://www.hackerrank.com/contests/projecteuler/challenges/euler006
//
// Brute force approach
// Solved: 8/18/14
unsigned long long euler006(int n)
{
    unsigned long long squareOfSum = 0, sumOfSquare = 0;
    for (int i = 1; i <= n; i++) {
        squareOfSum += i;
        sumOfSquare += i*i;
    }
    return squareOfSum*squareOfSum - sumOfSquare;
}

// Project Euler #7: 10001st prime
// https://www.hackerrank.com/contests/projecteuler/challenges/euler007
//
// Uses Massias and Robin [MR96] to estimate nth prime.
// Solved: 8/18/14
int euler007(int n)
{
    int estimate;
    // refer to [MR96]
    if (n > 15985)   estimate = n * (log(n)+log(log(n))-0.9427);
    else if (n > 13) estimate = n * (log(n)+log(log(n))-1+1.8*log(log(n))/log(n));
    else             estimate = 41;
    
    // find all prime numbers below estimtae using Sieve of Eratosthenes (from euler005)
    int numbers[estimate+1], primes[estimate/2+1], counter, primeCount = 0, root = sqrt(estimate);
    for (counter = 2; counter <= estimate; counter++) numbers[counter] = counter;
    for (int prime = 2; prime <= root; prime++)
        if (numbers[prime])
            for (int multiple = prime*2; multiple <= estimate; multiple += prime) numbers[multiple] = 0;
    for (int i = 2, counter = 0; i <= estimate; i++){
        if (numbers[i]){
            primes[counter++] = numbers[i];
        }
        primeCount = counter;
    }
    
    return primes[n-1];
}
