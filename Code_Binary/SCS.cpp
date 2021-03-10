#include <set>
#include <tuple>
#include <random>
#include <vector>

#include "SCS.h"

using namespace std;
using namespace SCS;

unsigned int SCS::PairsToAdd(Strand s1, Strand s2)
{
    auto s1OriginalValue = s1.to_ulong();
    auto s2OriginalValue = s2.to_ulong();

    // Reverse s1 and s2
    auto s1Reversed = Reverse(s1);
    auto s2Reversed = Reverse(s2);
    auto s1ReversedValue = s1Reversed.to_ulong();
    auto s2ReversedValue = s2Reversed.to_ulong();

    if (min(s1ReversedValue, s2ReversedValue) < s1OriginalValue)
        // Reverse is a symmetric action, so in this case, because we go over the strands in an ascending order,
        // we have already seen this pair (s1, s2) when we calculated (s1Reversed, s2Reversed).
    {
        return 0;
    }
    if ((s1ReversedValue == s1OriginalValue and s2ReversedValue < s2OriginalValue) or
        (s2ReversedValue == s1OriginalValue and s1ReversedValue < s2OriginalValue))
    {
        return 0;
    }

    // Flip s1 and s2, and the reversed s1 and s2.
    s1.flip(); s2.flip();
    s1Reversed.flip(); s2Reversed.flip();

    // For readability.
    auto s1Flipped = s1;
    auto s2Flipped = s2;
    auto s1ReversedFlipped = s1Reversed;
    auto s2ReversedFlipped = s2Reversed;

    auto s1FlippedValue = s1Flipped.to_ulong();
    auto s2FlippedValue = s2Flipped.to_ulong();
    auto s1ReversedFlippedValue = s1ReversedFlipped.to_ulong();
    auto s2ReversedFlippedValue = s2ReversedFlipped.to_ulong();

    if (min(min(s1ReversedFlippedValue, s2ReversedFlippedValue), s2FlippedValue) < s1OriginalValue)
        // Reverse and Flip are symmetric actions, so in this case, because we go over the strands in an ascending order,
        // we have already seen this pair (s1, s2) when we calculated one of the other pairs.
    {
        return 0;
    }
    if ((s1ReversedFlippedValue == s1OriginalValue and s2ReversedFlippedValue < s2OriginalValue) or
        (s2ReversedFlippedValue == s1OriginalValue and s1ReversedFlippedValue < s2OriginalValue) or
        (s2FlippedValue == s1OriginalValue and s1FlippedValue < s2OriginalValue))
    {
        return 0;
    }

    // We insert all the flipped and\or reversed pairs into a set, to see how many different pairs there are (as some of the pairs might be identical).
    // The first value is always smaller or equal to the second value.
    set<tuple<unsigned long, unsigned long>> s;

    s.insert(make_tuple(s1OriginalValue, s2OriginalValue));
    s.insert(make_tuple(min(s1ReversedValue, s2ReversedValue), max(s1ReversedValue, s2ReversedValue)));
    s.insert(make_tuple(min(s1ReversedFlippedValue, s2ReversedFlippedValue), max(s1ReversedFlippedValue, s2ReversedFlippedValue)));
    s.insert(make_tuple(min(s1FlippedValue, s2FlippedValue), max(s1FlippedValue, s2FlippedValue)));

    return s.size();
}

Strand SCS::Reverse(const Strand& s)
{
    Strand res;
    for (auto i = 0; i < N; ++i)
    {
        res[i] = s[N - i - 1];
    }
    return res;
}

unsigned int SCS::GetS2StartIndex(const Strand& prevS2, const Strand& s2)
{
    if (prevS2.to_ulong() == 0)
    {
        return 1;
    }
    auto xorRes = prevS2 ^ s2;
    for (auto i = 0; i < N; ++i)
    {
        if (xorRes[i])
            // If the xor bit is '1' then this index differs between the strands.
        {
            return i + 1;
        }
    }
    return 1; // Shouldn't get here.
}

unsigned int SCS::Calculate(const Strand& s1, const Strand& s2, unsigned int solutionArray[N + 1][N + 1], const Strand& lastS2)
{
    auto s2Start = GetS2StartIndex(lastS2, s2);
    for (auto i = 1; i <= N; i++)
    {
        for (auto j = s2Start; j <= N; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                solutionArray[i][j] = solutionArray[i - 1][j - 1] + 1;
            }
            else
            {
                solutionArray[i][j] = min(solutionArray[i - 1][j] + 1,
                    solutionArray[i][j - 1] + 1);
            }
        }
    }
    return solutionArray[N][N];
}

Strand SCS::GenerateStrand()
{
    /* Seed */
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<uint64_t> distribution(0, ((1 << N + 1) - 1));

    return Strand(distribution(generator));
}
