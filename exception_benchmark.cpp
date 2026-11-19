#include <chrono>
#include <iostream>
#include <stdexcept>
template<class F>double ms(F f){auto a=std::chrono::steady_clock::now();f();auto b=std::chrono::steady_clock::now();return std::chrono::duration<double,std::milli>(b-a).count();}
volatile long sink=0;
long codes(std::size_t n,int pct){long ok=0;for(std::size_t i=0;i<n;++i){bool bad=int(i%100)<pct;if(bad){int status=1;if(status)continue;}++ok;}sink=ok;return ok;}
long exceptions(std::size_t n,int pct){long ok=0;for(std::size_t i=0;i<n;++i){bool bad=int(i%100)<pct;try{if(bad)throw std::invalid_argument("invalid");++ok;}catch(const std::invalid_argument&){}}sink=ok;return ok;}
int main(){constexpr std::size_t n=1000000;for(int p:{0,1,50}){double a=ms([&]{codes(n,p);});double b=ms([&]{exceptions(n,p);});std::cout<<"invalid="<<p<<"% return_code_ms="<<a<<" exception_ms="<<b<<'\n';}}
