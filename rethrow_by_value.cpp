#include <iostream>
#include <stdexcept>
struct ClaimError:std::runtime_error{using std::runtime_error::runtime_error;};
struct DetailedClaimError:ClaimError{using ClaimError::ClaimError;};
int main(){try{try{throw DetailedClaimError("exceeds cover");}
 catch(const ClaimError&e){std::cout<<"caught: "<<e.what()<<'\n';throw e;}}
 catch(const DetailedClaimError&){std::cout<<"derived caught\n";}
 catch(const ClaimError&){std::cout<<"base caught after throw e\n";}}
