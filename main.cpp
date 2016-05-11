#include <iostream>
#include "TemplatesFromTree.h"
using namespace std;

int main() {

    std::map<Triple*,int,TripleComp> tri_count;

    std::set<TemplateTree*,TreeComp> templateTrees;


    cout << "Hello, World!" << endl;
    return 0;
}