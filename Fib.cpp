//
// Created by 龚世炎 on 2021/1/24.
//


class Fib {
private:int f,g; //f = fib(k-1);g = fib(k) int型很快就会溢出65535，可对输入的n做限制
public:
    Fib(int n) {f = 1;g = 0;while(g < n) next();}//初始化不小于n的fib项
    int get() {return g;}
    int next() {g += f; f = g - f; return g;}
    int prev() {f = g - f; g -= f; return g;}
};