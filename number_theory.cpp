#include <bits/stdc++.h>
using namespace std;


// Euclidean algorithm


// Bézout's identity :-
// Acc to Bézout's identity let there is two number a and b the there must exist two numbers x and y such that
// a*x + b*y = gcd(a , b)

// Linear Diophantine equation
// A linear Diophantine equations is in form of :- a*x + b*y = c
// where a , b , c are known and x , y are unknown variables

// We focus on finding one solution , finding all solutions , find number of solution in the given intervals , find solution with minimum value of x and y
// a diophantine equation has solution only when c is divisible by __gcd(a,b).

// a) Get one solutions:- to find one solution we can use extended euclied theorem (read from cp algo)


int gcd(int a , int b , int &x , int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1 = -1 , y1 = -1;
    int gcd = gcd(b , a%b , x1 , y1);
    x = y1;
    y = x1 - y1*(a/b);
    return gcd;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) 
{
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g; // this value of x and y is for ax + by = gcd(a,b) not ax+by = c , so thats why we are multiplying it with c/gcd
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// b) Get all solution
// let we get one solution using above method
// take a eq 10*x + 15*y = 65,this equation has (2,3) as solution
// now take the general point (u+2 , v+3) put this in equation
// 10*(u+2) + 15*(v+3) = 65;
// 10*u + 15*v = 0;
// u = -15v/10;
// menas all even value of v has a corresponding value of u (if only integral solution are accepted)
// so v = 2m => y = 2m+3 and u = -3m => x = -3m+2


// c) number of solution in the given intervals
// If we dont impose any restriction on solutions then we get the infinite number of solution so we have to impose some restriction to get the finite number of solutions
// let suppose x1 and y1 is one solution of eq
// a.x1 + b.y1 = c
// => a*(x1 + b/g) + b*(y1 - a/g) = a*x1 + b*y1 + a*(b/g) - b*(a/g) = c
// we can repeat this porcess again and again
// so x = x1 + k*(b/g)
// y = y1 - k*(a/g);
// find value of k such that x lies in [xmin , xmax] and same for y lies in [ymin , ymax] and take the intersection of that case





// Modulo Inverse 
// We need find the modulo inverse beacause when we do modulo division it will give wrong answer 
// so modulo inverse of number X is Y such that (X*Y)%M == 1 means X*Y is modulo congruent to 1 under modulo M 
// modulo inverse of number a under modulo M exist if and only if gcd(a, M) = 1 means a and M is coprime 

// a. MODULO INVERSE USING FERMAT LITTLE THEOREM (this only valid when M is prime number)
// Acc to fermat little theorem (a^(p-1))%p = 1
// now a*a^(p-2) == 1 (if X*Y = 1     => X = 1/Y   => Y = X^-1)
// So a^-1 = a^(p-2) under modulo p where p is prime number 

// b. By using extended eucledian theorem 
// if inverse of a is x means (a*x)%m = 1 and this also imploys (a*x + b*m)%m = 1
// treat this as two variable equation having a*x + b*y = 1 , 
// to exist for a solution gcd(a , b) = 1
// calculate the value of x using extended eucledian theorem just like did in calculate the value of value of variable in linear Diophantine equation

// c. Linear congruence (☰)
// a*x ☰ b(mod M) 
// this means (a*x)%M == b%M 

// ques : given equation a*X ☰ b (mod M), find the number of distinct value of b can take depending upon values of X.
// 2*X ☰ {b}%4 here,
//  when X = 0 , b = 0
//  when X = 1 , b = 2
//  when X = 2 , b = 0
//  when X = 3 , b = 2
//  when X = 4 , b = 0 , show b can take two different values i.e 0, 2 (and we are not getting 1, 3)
// sol : here a*X ☰ b (mod m) can be represented as aX + Ym = b 
// so solution exist only when b%gcd(a,m) == 0
// value of b = multiple of gcd(a, m) such that it is less than m i.e = (m-1)/gcd(a,m);

// d. chinese remainder theorem
// given set of congruences
// x ☰ b1 (mod m1)
// x ☰ b2 (mod m2)
// x ☰ b3 (mod m3)
// now we have to find the value x under modulo m which satisfy these equations
// so value m = lcm(m1 , m2 .... mn)/gcd(m1 , m2 , ..... mn)
// lets take two equations only
// a1*x ☰ b1 (mod m1) and a2*x ☰ b2(mod m2)
// a1*x + Y1*M1 = b1  (eq 1)
// a2*x + Y2*M2 = b1  (eq 2) multiple eq1 with a2 and eq2 with a1
// so a1*a2*x + Y1*M1*a2 = b1*a2 
// so a2*a1*x + Y2*M2*a1 = b2*a1  substract 1 from 2
// then Y2*M2*a1 - Y1*M1*a2 = b2*a1 - b1*a2   (last)
// M1 , M2 , a1 , a2 are know constant 
// So eq last becomes
// Y2*c1 + Y2*(-c2)  = c2 (this Diophantine eq)  calculate this Y1 and Y2 and put any of eq 1 or 2 nad find value of x.