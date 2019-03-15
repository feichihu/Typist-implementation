
#include "Method.hpp"

using u_int = unsigned int;
Dict dict;

std::istream &operator>>(std::istream &str, TXTRow &data)
{
    data.readNextRow(str);
    return str;
}
int main()
{
    // read corpus

    // init Dict

    // init layout
    keyLayout p;
    //p.shuffle();
    keyLayout newp(p);
    keyLayout qwerty;

    // pass in layout
    // method.benchmark
    Method expertMethod = ExpertMethod(p);
    long weight = expertMethod.benchmark();
    std::cout << "random total weight is" << weight << std::endl;
    expertMethod.updateLayout(qwerty);
    long qwerty_weight = expertMethod.benchmark();
    std::cout << "qwerty total weight is" << qwerty_weight << std::endl;
    p.printLayout();

    //simulated annealing
    //start with a random layout
    //random swap 2 keys, accept new layout if weight is reduced
    //repeat EXPLOIT times, if accept, start swapping again
    //else, start random choosing neigbors
    //swap 2 keys
    //accept with prob(exp(old_weight-new_weight)/qwerty_weight)
    //repeat EXPLORE times
    //bool annealing = true;
    int exploit = 100;
    int explore = 100;
    long newweight = weight;
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < explore; i++)
        {
            std::cout << "+";
            newp = p;
            newp.swap();
            newp.swap();
            newp.swap();
            expertMethod.updateLayout(newp);
            newweight = expertMethod.benchmark();
            double power = 1000 * (double)(weight - newweight) / (double)weight;
            std::cout << exp(power);
            std::bernoulli_distribution acc(exp(power));
            std::default_random_engine gen;
            if (acc(gen))
            {
                std::cout << "accept neigbor" << std::endl;
                p = newp;
                weight = newweight;
                break;
            }
            if(i==explore-1) 
                std::cout << "no neigbor accepted" << std::endl;
        }
        bool pass = false;
        while (!pass)
        {
            for (int i = 0; i < exploit; i++)
            {
                std::cout << "-";
                newp = p;
                newp.swap();
                expertMethod.updateLayout(newp);
                newweight = expertMethod.benchmark();
                if (newweight < weight)
                {
                    std::cout << "optimized neighbor found" << std::endl;
                    p = newp;
                    weight = newweight;
                    break;
                }
                if (i == exploit - 1){
                    std::cout << "no optimized neighbor found" << std::endl;
                    pass = true;
                }
            }
        }
    }
    std::cout << "final total weight is" << weight << std::endl;
    std::cout << "qwerty total weight is" << qwerty_weight << std::endl;
    p.printLayout();
}