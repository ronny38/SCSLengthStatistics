#ifndef SCS_H
#define SCS_H

#include <bitset>

#include "Settings.h"

/**
 * Implementation of a solution for the Shortest Common Supersequence's Length problem.
 *
 * Given two strands, theses functions provide solutions to find the length of their shortest common supersequence.
 * It uses dynamic programming in order to provide a solution withing a time complexity of O(n^2).
 */
namespace SCS
{
    using Strand = std::bitset<N>;

    /*
    * PairsToAdd:
    * This function is implemented for running-time optimization purposes.
    *
    * Given a pair of strands, this function determines how many "similar" pairs there are:
    * That is, how many more pairs of strands would certainly have the exact same SCS result as this pair, so later, in a single calculation, we would be able to get the results for more than one pair of strands.
    *
    * @param s1, @param s2 - the strands that are about to be calculated. We assume that s1 <= s2.
    * @returns - 0, if the given pair of strands has already been taken into considerations, so there is no need to recalculate its SCS length;
    *            1, 2, 3 or 4 - depends on how many more different pairs we can optimize.
    *
    * In this function, the strands are reversed and\or flipped, because their SCS length should be the same as the original pair's.
    */
    unsigned int PairsToAdd(Strand s1, Strand s2);


    /*
    * Reverse:
    * Given a strand, returns its reversed version.
    *
    * For example, given the following strand:
    *   1  0  1  0  0  0
    * Returns:
    *   0  0  0  1  0  1
    */
    Strand Reverse(const Strand& s);


    /*
    * GetS2StartIndex:
    * This function is implemented for running-time optimization purposes.
    *
    * Given a pair of strands, this function returns the first index (that is, the index that is nearest to the LSB) that is different between the two strands.
    *
    * @param prevS2 - the last 's2' strand that was used in an actual calculation of SCS length with the current 's1' strand.
    *                 prevS2 is not necessarily (s2 - 1) because in some pairs of strands we skip the calculation (see PairsToAdd for more details).
    * @param s2 - the next 's2' strand that its SCS length with the current 's1' strand is about to be calculated.
    *
    * The return value allows us to reuse parts of the matrix that is used to calculate the SCS length problem (solutionArray), and to avoid recalculating values that would not change since the last calculation.
    */
    unsigned int GetS2StartIndex(const Strand& prevS2, const Strand& s2);


    /*
    * GenerateStrand:
    * Returns a randomly generated strand of length N.
    */
    Strand GenerateStrand();


    /*
    * Calculate:
    * Calculates the SCS length of two given strands.
    *
    * @param s1, @param s2 - the strands to calculate their SCS length.
    * @param solutionArray - a pointer to a matrix that is used for the calculation. We assume that it wasn't changed since the last calculation (therefore, for example, there is no need to initialize its constant values).
    * @param lastS2 - the previous 's2' strand that was used in an actual calculation of SCS length with the current 's1' strand. This parameter helps us to understand which cells in solutionArray might not need any recalculation.
    *
    * @returns the SCS length of (s1, s2).
    */
    unsigned int Calculate(const Strand& s1, const Strand& s2, unsigned int solutionArray[N + 1][N + 1], const Strand& lastS2);
}

#endif // !SCS_H