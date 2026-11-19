#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
struct Resource{~Resource(){std::cout<<"Resource released\n";}};
int main(){
 try{throw std::invalid_argument("negative charge");}catch(const std::exception&e){std::cout<<"validation: "<<e.what()<<'\n';}
 try{throw std::runtime_error("claim above cover");}catch(const std::exception&e){std::cout<<"claim: "<<e.what()<<'\n';}
 try{throw std::runtime_error("unknown package");}catch(const std::exception&e){std::cout<<"package: "<<e.what()<<'\n';}
 try{(void)std::stod("not-a-number");}catch(const std::invalid_argument&e){std::cout<<"number: "<<e.what()<<'\n';}
 try{Resource r;std::vector<int> v;v.resize(v.max_size());}
 catch(const std::bad_alloc&){std::cout<<"bad_alloc caught\n";}
 catch(const std::exception&e){std::cout<<"allocation rejected: "<<e.what()<<'\n';}
 try{Resource r;throw 7;}catch(...){std::cout<<"top-level catch-all recovered\n";}
}
