#include <iostream>
#include "phase2.h"
#include "InputParser.h"


using namespace std;

int main()
{
    cout << "Hello Team el 7azina el gamed gidnnnn:D!" << endl;
    /*  */
    LL_Productions p;
    p.get_bonus();
    InputParser ip;
    ip.parse_rules();

    /**/
    ParsingTable t(ip.elements, ip.prod_rules_indexes) ;
    t.construct_parsing_table();



    /* */
    Matching m(t.parsing_table,ip.elements);
    m.match_input();
    m.write_file();


    return 0;
}
