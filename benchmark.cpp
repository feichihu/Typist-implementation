
#include "Method.hpp"


using u_int = unsigned int;
Dict dict;



std::istream &operator>>(std::istream &str, TXTRow &data)
{
    data.readNextRow(str);
    return str;
}
int main(){
    // read corpus

    // init Dict

    // init layout
    keyLayout p;

    // pass in layout
    // method.benchmark
    Method expertMethod = ExpertMethod(p);
    long weight = expertMethod.benchmark();
    std::cout<<"total weight is"<<weight<<std::endl;

}