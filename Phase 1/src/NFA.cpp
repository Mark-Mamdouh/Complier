/*
 * NFA.cpp
 *
 *  Created on: 22 Mar 2017
 *      Author: Paula B. Bassily
 */

#include "NFA.h"
#include "DFA.h"
#include <vector>

namespace std
{

void NFA::attach_states_on(int s1, int s2, char in)
{
    State st1=all_nodes[s1];
    //State st2=all_nodes[s2];
    st1.input = in;
    //st1.terminal=st2.terminal;
    st1.next.push_back(s2);
    all_nodes[s1]=st1;
}
int NFA::create_state()
{
    State s(state_num);
    all_nodes.push_back(s);
    state_num++;
    return s.num;
}
void NFA::nfa_or()
{
    int start = create_state();
    int end = create_state();

    int s1 = input_stack.top();
    input_stack.pop();

    int s2 = input_stack.top();
    input_stack.pop();

    State st1 = all_nodes[s1];
    State st2 = all_nodes[s2];
    attach_states_on(st1.terminal, end, ' ');
    attach_states_on(st2.terminal, end, ' ');

    attach_states_on(start,s1,' ');
    attach_states_on(start,s2,' ');

    update_terminal(start,end);

    input_stack.push(start);
}
void NFA::nfa_input(char in)
{
    int s1 = create_state();
    int  s2 = create_state();
    attach_states_on(s1, s2, in);
    update_terminal(s1,s2);
    input_stack.push(s1);
}
void NFA::nfa_and()
{

    int s2 = input_stack.top();
    input_stack.pop();
    State st2 = all_nodes[s2];

    int  s1 = input_stack.top();
    State st1 = all_nodes[s1];

    attach_states_on(st1.terminal,s2,' ');
    update_terminal(s1,s2);

}
void NFA::nfa_astrick()
{
    int start = create_state();
    int end = create_state();

    int s1 = input_stack.top();
    input_stack.pop();
    State st1 = all_nodes[s1];

    attach_states_on(start, s1, ' ');
    attach_states_on(st1.terminal,end,' ');
    attach_states_on(end,s1,' ');
    attach_states_on(start,end,' ');

    update_terminal(start,end);

    input_stack.push(start);
}
void NFA::nfa_plus()
{
    int start = create_state();
    int end = create_state();

    int s1 = input_stack.top();
    input_stack.pop();
    State st1 = all_nodes[s1];

    attach_states_on(start, s1, ' ');
    attach_states_on(st1.terminal,end,' ');
    attach_states_on(end,s1,' ');

    update_terminal(start,end);

    input_stack.push(start);
}
void NFA::get_acceptance(int s)
{
    State real_state=all_nodes[s];
    if(real_state.next.empty())
    {
        cout<<"acceptance state of "<<real_state.num<<" is "
            <<real_state.acceptance<<endl;
        return ;
    }
    for(int i=0; i<real_state.next.size(); i++)
    {
        int child = real_state.next[i];
        get_acceptance(child);
    }
}
void NFA::nfa_check()
{
    int start= input_stack.top();
    State st = all_nodes[start];
    State terminal = all_nodes[st.terminal];
    cout<<"acceptance token : "<<terminal.acceptance<< "  node :" << st.terminal <<endl;
}

void NFA::nfa_accpetance(string token)
{
    int start = input_stack.top();
    State st = all_nodes[start];
    State terminal = all_nodes[st.terminal];
    terminal.acceptance=token;
    all_nodes[st.terminal]=terminal;
}
void NFA::update_terminal(int state, int state_of_terminal)
{
    State st1=all_nodes[state];
    State st2=all_nodes[state_of_terminal];
    st1.terminal=st2.terminal;
    all_nodes[state]=st1;
}

void NFA::build_nfa(string token, string experssion)
{
    for (string::iterator it = experssion.begin(); it != experssion.end(); it++)
    {
        switch (*it)
        {
        case '*':
            // call NFA kleene closure creator
            nfa_astrick();
            break;
        case '+':
            // call NFA + closure creator
            nfa_plus();
            break;
        case '^':
            // call NFA concatenation creator
            nfa_and();
            break;
        case '|':
            // call NFA OR creator
            nfa_or();
            break;
        case '\\':
            // call NFA OR creator
            it++;
        default :
            nfa_input(*it);
        }
    }
    nfa_accpetance(token);
    //separated_nfas.push_back(input_stack.top());
//	input_stack.pop();
    nfa_check();

}
int NFA::build_combined_nfa()
{
    int el7azina = create_state();
    cout<<"----------------------------"<<endl;
    cout<<"expressions count = "<<input_stack.size()<<endl;
    while(!input_stack.empty())
    {
        attach_states_on(el7azina,input_stack.top(),' ');
        input_stack.pop();

    }
    return el7azina;
}

NFA::NFA()
{
    // TODO Auto-generated constructor stub
    state_num = 0;
    cout << "NFA generator created" << endl;
}

NFA::~NFA()
{
    // TODO Auto-generated destructor stub
}

} /* namespace std */
