//
// Created by oref1 on 04/02/2021.
//

#ifndef SCSLENGTHSTATISTICS_DEBUG_FUNC_H
#define SCSLENGTHSTATISTICS_DEBUG_FUNC_H

#include <iostream>
#include <vector>
#include "SCS/Common.h"

using namespace std;

void print_base(const Base& b){
    switch(b)
    {
        case A:
            cout<<"A";
            break;
        case C:
            cout<<"C";
            break;
        case G:
            cout<<"G";
            break;
        default:
            cout<<"T";
            break;
    }
}

void print_strand(const vector<Base> & s){
    for (auto& b:s){
        print_base(b);
    }
    cout<<endl;
}

static bool IncrementInner(std::vector<Base>& vec, int index, bool isAC)
{
    if (index == 1 && ((not isAC and vec[index] == T) or (isAC and vec[index] ==  C)))
    {
        return false;
    }

    if (vec[index] != T)
    {
        IncrementIndex(vec[index]);
        return true;
    }
    else
    {
        vec[index] = A;
        return IncrementInner(vec, index - 1, isAC);
    }
}

static bool Increment(std::vector<Base>& vec, bool isAC)
{
    return IncrementInner(vec, vec.size() - 1, isAC);
}

static bool IncrementInner2(std::vector<Base>& vec, int index)
{
    if (index == 0 && vec[index] ==  T)
    {
        return false;
    }

    if (vec[index] != T)
    {
        IncrementIndex(vec[index]);
        return true;
    }
    else
    {
        vec[index] = A;
        return IncrementInner2(vec, index - 1);
    }
}

static bool Increment2(std::vector<Base>& vec)
{
    return IncrementInner2(vec, vec.size() - 1);
}

#endif //SCSLENGTHSTATISTICS_DEBUG_FUNC_H
