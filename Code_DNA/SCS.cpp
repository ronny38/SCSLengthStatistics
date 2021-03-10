#include <algorithm>
#include <set>
#include <tuple>
#include <random>
#include <vector>

#include "SCS.h"
#include "Settings.h"

using namespace std;
using namespace SCS;

unsigned int SCS::PairsToAdd(const Strand& s1, const Strand& s2)
{
    // Reverse s1 and s2
    auto s1Reversed = Strand::Reverse(s1);
    auto s2Reversed = Strand::Reverse(s2);

    if (Strand::Min(s1Reversed, s2Reversed) < s1)
        // Reverse is a symmetric action, so in this case, because we go over the strands in an ascending order,
        // we have already seen this pair (s1, s2) when we calculated (s1Reversed, s2Reversed).
    {
        return 0;
    }
    if (Strand::Min(s1Reversed, s2Reversed) == s1 and
		Strand::Max(s1Reversed, s2Reversed) < s2)
    {
        return 0;
    }

    // Flip s1 and s2, and also the reversed s1 and s2.
    auto s1Flipped = Strand::Flip(s1);
    auto s2Flipped = Strand::Flip(s2);
    auto s1ReversedFlipped = Strand::Flip(s1Reversed);
    auto s2ReversedFlipped = Strand::Flip(s2Reversed);

    if (Strand::Min(s1ReversedFlipped, s2ReversedFlipped, s2Flipped) < s1)
        // Reverse and Flip are symmetric actions, so in this case, because we go over the strands in an ascending order,
        // we have already seen this pair (s1, s2) when we calculated one of the other pairs.
    {
        return 0;
    }
    if ((s1ReversedFlipped == s1 and s2ReversedFlipped < s2) or
        (s2ReversedFlipped == s1 and s1ReversedFlipped < s2) or
        (s2Flipped == s1 and s1Flipped < s2))
    {
        return 0;
    }

    auto s1FlippedTwice = Strand::Flip(s1Flipped);
    auto s2FlippedTwice = Strand::Flip(s2Flipped);
    auto s1ReversedFlippedTwice = Strand::Flip(s1ReversedFlipped);
    auto s2ReversedFlippedTwice = Strand::Flip(s2ReversedFlipped);

    if (Strand::Min(s1ReversedFlippedTwice, s2ReversedFlippedTwice, s2FlippedTwice) < s1)
    {
        return 0;
    }
    if ((s1ReversedFlippedTwice == s1 and s2ReversedFlippedTwice < s2) or
        (s2ReversedFlippedTwice == s1 and s1ReversedFlippedTwice < s2) or
        (s2FlippedTwice == s1 and s1FlippedTwice < s2))
    {
        return 0;
    }

    auto s1FlippedAgain = Strand::Flip(s1FlippedTwice);
    auto s2FlippedAgain = Strand::Flip(s2FlippedTwice);
    auto s1ReversedFlippedAgain = Strand::Flip(s1ReversedFlippedTwice);
    auto s2ReversedFlippedAgain = Strand::Flip(s2ReversedFlippedTwice);

    if (Strand::Min(s1ReversedFlippedAgain, s2ReversedFlippedAgain, s2FlippedAgain) < s1)
    {
        return 0;
    }
    if ((s1ReversedFlippedAgain == s1 and s2ReversedFlippedAgain < s2) or
        (s2ReversedFlippedAgain == s1 and s1ReversedFlippedAgain < s2) or
        (s2FlippedAgain == s1 and s1FlippedAgain < s2))
    {
        return 0;
    }

    // We insert all the flipped and\or reversed pairs into a set, to see how many different pairs there are (as some of the pairs might be identical).
    // The first value is always smaller or equal to the second value.
    set<tuple<uint64_t, uint64_t>> s;

    s.insert(make_tuple(s1.Value(), s2.Value()));
	s.insert(make_tuple(Strand::Min(s1Reversed, s2Reversed).Value(), Strand::Max(s1Reversed, s2Reversed).Value()));

	s.insert(make_tuple(Strand::Min(s1Flipped, s2Flipped).Value(), Strand::Max(s1Flipped, s2Flipped).Value()));
	s.insert(make_tuple(Strand::Min(s1ReversedFlipped, s2ReversedFlipped).Value(), Strand::Max(s1ReversedFlipped, s2ReversedFlipped).Value()));

	s.insert(make_tuple(Strand::Min(s1FlippedTwice, s2FlippedTwice).Value(), Strand::Max(s1FlippedTwice, s2FlippedTwice).Value()));
	s.insert(make_tuple(Strand::Min(s1ReversedFlippedTwice, s2ReversedFlippedTwice).Value(), Strand::Max(s1ReversedFlippedTwice, s2ReversedFlippedTwice).Value()));

	s.insert(make_tuple(Strand::Min(s1FlippedAgain, s2FlippedAgain).Value(), Strand::Max(s1FlippedAgain, s2FlippedAgain).Value()));
	s.insert(make_tuple(Strand::Min(s1ReversedFlippedAgain, s2ReversedFlippedAgain).Value(), Strand::Max(s1ReversedFlippedAgain, s2ReversedFlippedAgain).Value()));

    return s.size();
}


unsigned int SCS::GetS2StartIndex(const Strand& prevS2, const Strand& s2)
{
    if (prevS2.Value() == 0)
    {
        return 1;
    }

    for (auto i = 0; i < N; ++i)
    {
        if (prevS2[i] != s2[i])
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
    std::uniform_int_distribution<uint64_t> distribution(0, Strand::MaxValue() - 1);

    return Strand(distribution(generator));
}