#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
struct BillingError:std::runtime_error{using std::runtime_error::runtime_error;};
struct ClaimError:BillingError{using BillingError::BillingError;};
struct Bill{virtual ~Bill()=default;virtual double total()const=0;virtual std::string type()const=0;};
struct OPBill:Bill{double c,t;OPBill(double a,double b):c(a),t(b){if(a<0||b<0)throw BillingError("negative charge");}double total()const override{return c+t;}std::string type()const override{return "OP";}};
struct MaternityBill:Bill{double package;explicit MaternityBill(double p):package(p){if(p<0)throw BillingError("negative package");}double total()const override{return package;}std::string type()const override{return "MATERNITY";}};
struct Payer{virtual ~Payer()=default;virtual double amountCovered(const Bill&)const=0;};
struct CorporatePayer:Payer{double amountCovered(const Bill&b)const override{return b.total()*.75;}};
double approve(double amount,double cover){if(amount<0||cover<0)throw std::invalid_argument("negative amount");if(amount>cover)throw ClaimError("exceeds cover");return amount;}
int main(){try{std::vector<std::unique_ptr<Bill>>b;b.push_back(std::make_unique<OPBill>(500,1200));b.push_back(std::make_unique<MaternityBill>(65000));CorporatePayer p;for(auto&x:b)std::cout<<x->type()<<" total="<<x->total()<<" corporate_cover="<<p.amountCovered(*x)<<'\n';try{approve(60000,50000);}catch(const ClaimError&e){std::cout<<"caught: "<<e.what()<<'\n';}std::cout<<"sanitizer test completed\n";}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}catch(...){std::cerr<<"unknown error\n";return 2;}}
