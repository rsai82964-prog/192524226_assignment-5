#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
class Bill {
protected: std::string patient;
public:
 explicit Bill(std::string p):patient(std::move(p)){}
 virtual ~Bill()=default;
 virtual double total()const=0;
 virtual std::string type()const=0;
 void print()const{std::cout<<type()<<' '<<patient<<": "<<std::fixed<<std::setprecision(0)<<total()<<'\n';}
};
class OutPatient:public Bill{
 double consultation,tests;
public: OutPatient(std::string p,double c,double t):Bill(std::move(p)),consultation(c),tests(t){if(c<0||t<0)throw std::invalid_argument("negative charge");}
 double total()const override{return consultation+tests;} std::string type()const override{return "OP";}
};
class InPatient:public Bill{
 int days;double rate,surgery;
public: InPatient(std::string p,int d,double r,double s):Bill(std::move(p)),days(d),rate(r),surgery(s){if(d<0||r<0||s<0)throw std::invalid_argument("negative charge");}
 double total()const override{return days*rate+surgery;} std::string type()const override{return "IP";}
};
class DayCare:public Bill{
 double package;
public: DayCare(std::string p,double x):Bill(std::move(p)),package(x){if(x<0)throw std::invalid_argument("negative package");}
 double total()const override{return package;} std::string type()const override{return "DAYCARE";}
};
class Emergency:public Bill{
 double base,hourly;int hours;
public: Emergency(std::string p,double b,double h,int n):Bill(std::move(p)),base(b),hourly(h),hours(n){if(b<0||h<0||n<0)throw std::invalid_argument("negative emergency charge");}
 double total()const override{return base+hourly*hours;} std::string type()const override{return "EMERGENCY";}
};
class Payer{public:virtual ~Payer()=default;virtual double amountCovered(const Bill&)const=0;};
class SelfPay:public Payer{public:double amountCovered(const Bill&)const override{return 0;}};
class Insurance:public Payer{
 double limit,copay;
public:Insurance(double l,double c):limit(l),copay(c){if(l<0||c<0||c>100)throw std::invalid_argument("invalid policy");}
 double amountCovered(const Bill&b)const override{return std::min(limit,b.total()*(1-copay/100));}
};
class GovernmentScheme:public Payer{
 double packageRate;
public:explicit GovernmentScheme(double r):packageRate(r){}
 double amountCovered(const Bill&b)const override{return std::min(packageRate,b.total());}
};
class CorporateTieUp:public Payer{public:double amountCovered(const Bill&b)const override{return b.total()*.80;}};
int main(){
 std::vector<std::unique_ptr<Bill>> bills;
 bills.emplace_back(std::make_unique<OutPatient>("Ravi",500,1200));
 bills.emplace_back(std::make_unique<InPatient>("Meena",3,2500,40000));
 bills.emplace_back(std::make_unique<DayCare>("Arun",18000));
 bills.emplace_back(std::make_unique<Emergency>("Sara",2000,500,4));
 double sum=0;for(const auto&b:bills){b->print();sum+=b->total();}
 std::cout<<"Total "<<std::fixed<<std::setprecision(0)<<sum<<'\n';
 Insurance ins(50000,20);CorporateTieUp corp;SelfPay self;
 std::cout<<"Insurance Ravi "<<ins.amountCovered(*bills[0])<<'\n';
 std::cout<<"Corporate Meena "<<corp.amountCovered(*bills[1])<<'\n';
 std::cout<<"SelfPay Arun "<<self.amountCovered(*bills[2])<<'\n';
}
