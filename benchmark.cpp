
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
    keyLayout qwerty;
    p.shuffle();

    // pass in layout
    // method.benchmark
    Method expertMethod = ExpertMethod(p);
    long weight = expertMethod.benchmark();
    std::cout<<"random total weight is"<<weight<<std::endl;
    expertMethod.updateLayout(qwerty);
    weight = expertMethod.benchmark();
    std::cout<<"qwerty total weight is"<<weight<<std::endl;
    p.printLayout();

}