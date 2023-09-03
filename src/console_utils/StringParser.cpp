#include <iostream>
#include "structure/BalancedTree.h"
#include "console_utils/StringParser.h"

void parse_string(){
    BalancedTree<int> tree{};
    char op;
    int num;
    while(std::cin >> op >> num) {
        switch(op) {
            case 'K':
            case 'k':
                tree.insert(num);
                break;
            case 'M':
            case 'm':
                std::cout << tree.min_at(num) << ' ';
                break;
            case 'N':
            case 'n':
                std::cout << tree.count_less(num) << ' ';
                break;
            default:
                break;
        }
    }
    std::cout << std::endl;
}
