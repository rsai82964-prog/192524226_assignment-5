#include <chrono>
#include <iostream>
#include <memory>
#include <type_traits>
#include <variant>
#include <vector>
struct Base{virtual ~Base()=default;virtual double total()const=0;};
struct OP:Base{double a,b;OP(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
struct IP:Base{double a,b;int d;IP(double x,double y,int z):a(x),b(y),d(z){}double total()const override{return a*d+b;}};
struct DC:Base{double p;explicit DC(double x):p(x){}double total()const override{return p;}};
struct EM:Base{double b,h;int t;EM(double x,double y,int z):b(x),h(y),t(z){}double total()const override{return b+h*t;}};
struct Tagged{int type;double x,y;int n;};
double sw(const Tagged&v){switch(v.type){case 0:return v.x+v.y;case 1:return v.x*v.n+v.y;case 2:return v.x;default:return v.x+v.y*v.n;}}
using V=std::variant<OP,IP,DC,EM>;
double visit(const V&v){return std::visit([](const auto&x)->double{using T=std::decay_t<decltype(x)>;if constexpr(std::is_same_v<T,OP>)return x.a+x.b;else if constexpr(std::is_same_v<T,IP>)return x.a*x.d+x.b;else if constexpr(std::is_same_v<T,DC>)return x.p;else return x.b+x.h*x.t;},v);}
template<class F>double timeMs(F f,std::size_t n){auto s=std::chrono::steady_clock::now();volatile double sum=0;for(std::size_t i=0;i<n;++i)sum+=f(i);auto e=std::chrono::steady_clock::now();if(sum<0)std::cerr<<sum;return std::chrono::duration<double,std::milli>(e-s).count();}
int main(){for(std::size_t n:{1000u,1000000u,10000000u}){
 std::vector<std::unique_ptr<Base>> p;p.reserve(n);std::vector<Tagged> t;t.reserve(n);std::vector<V> v;v.reserve(n);
 for(std::size_t i=0;i<n;++i)switch(i%4){case 0:p.push_back(std::make_unique<OP>(500,1200));t.push_back({0,500,1200,0});v.emplace_back(OP(500,1200));break;case 1:p.push_back(std::make_unique<IP>(2500,40000,3));t.push_back({1,2500,40000,3});v.emplace_back(IP(2500,40000,3));break;case 2:p.push_back(std::make_unique<DC>(18000));t.push_back({2,18000,0,0});v.emplace_back(DC(18000));break;default:p.push_back(std::make_unique<EM>(2000,500,4));t.push_back({3,2000,500,4});v.emplace_back(EM(2000,500,4));}
 double a=timeMs([&](auto i){return p[i]->total();},n),b=timeMs([&](auto i){return sw(t[i]);},n),c=timeMs([&](auto i){return visit(v[i]);},n);
 std::cout<<"n="<<n<<" virtual_ms="<<a<<" switch_ms="<<b<<" variant_ms="<<c<<'\n';
 if(n==1000){double x=0,y=0,z=0;for(std::size_t i=0;i<n;++i){x+=p[i]->total();y+=sw(t[i]);z+=visit(v[i]);}std::cout<<"totals="<<x<<','<<y<<','<<z<<'\n';}
}}
