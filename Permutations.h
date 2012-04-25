/*
    Author : Christopher Scoggins
    Title  : Permuation Templates
            Contains 5 different types of Permuation Algorithms
    Started: 2/21/12
    Due    : 2/24/12
    Mod    : 2/21/12
*/

#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/*
    Comments on All Functions:
        Since template for any type of Vector, will use another array to keep track of indicies
*/

// Indicie array to Permuted Array Function

template <typename T>
vector<T> getPermutedArray(vector<T> orig, vector<int> per)
{
    vector<T> a;

    for(int i = 0; i < orig.size(); i++)
    {
        a.push_back(orig[ per[i] ]);
    }

    return a;
}

// Function to set up the indicie array for all functions

void setIndicieArray(vector<int>& per, int size)
{
    for(int i = 0; i < size; i++)
    {
        per.push_back(i);
    }
}

// Recursive portion of Minimal-change

vector< vector<int> > rMinChange(vector<int> per)
{
    vector< vector<int> > answers;
    int size = per.size();

    if(size <= 1)
    {
        answers.push_back( per );
        return answers;
    }
    else
    {
        int newInt = per[size - 1];
        vector<int> tmp(per);
        tmp.pop_back();

        vector< vector<int> > lastAns = rMinChange(tmp);


        bool moveRight = false;

        for(int i = 0; i < lastAns.size(); i++)
        {

            // Initial Setup

            if(!moveRight)
            {
                per = lastAns[i];
                per.push_back(newInt);

                answers.push_back(per);     // add new Permutaion

                // Shift new number through, adding new permutations




                for(int k = size - 1; k > 0; k--)
                {
                    swap(per[k], per[k - 1]);
                    answers.push_back(per);
                }
            }
            else
            {
                for(int j = 1; j < size; j++)
                    per[j] = lastAns[i][j-1];

                answers.push_back(per);      // add new Permutation

                // Shift new number through, adding new permutations
                for(int k = 0; k < size - 1; k++)
                {
                    swap(per[k], per[k + 1]);
                    answers.push_back(per);
                }

            }

            moveRight = !moveRight;

        }

        return answers;
    }
}


// Minimal-change (decrease-by-one algorithm)

template <typename T>
vector<vector<T> > Minimal_Change(vector<T> a)
{

    vector<int> per;
    vector< vector<int> > intAns;
    vector<vector<T> > answer;

    setIndicieArray(per, a.size() );

    intAns = rMinChange(per);

    for(int i = 0; i < intAns.size(); i++)
    {
        answer.push_back(getPermutedArray(a, intAns[i] ) );
    }

    return answer;

}

// Function to find a mobile element for Johnson-Trotter

int findMobileElement(vector<int> per, vector<bool> arrow)          // Will return index to largest Mobile Element, or -1 if there is none
{
    int ans = -1;
    int maxVal = -1;

    for(int i = 0; i < per.size(); i++)
    {
        if(per[i] > maxVal)
        {
            if(arrow[i])        // Arrow Points left
            {
                if(i != 0)      // If not left-most element
                {
                    if(per[i] > per[i - 1])
                    {
                        ans = i;
                        maxVal = per[i];
                    }
                }
            }
            else                // Arrow Points Right
            {
                if(i != per.size() - 1)      // If not right-most element
                {
                    if(per[i] > per[i + 1])
                    {
                        ans = i;
                        maxVal = per[i];
                    }
                }
            }
        }

    }

    return ans;
}

// Johnson-Trotter

template <typename T>
vector<vector<T> > Johnson_Trotter(vector<T> a)
{
    vector<vector<T> > answer;
    vector< int > per;
    vector< bool > arrow;
    int mobileElem;

    setIndicieArray(per, a.size());

    // Set arrow array to all arrows left

    for(int i = 0; i < a.size(); i++)
        arrow.push_back(true);

    answer.push_back( getPermutedArray(a, per) );   // Add first permutation to array

    mobileElem = findMobileElement(per, arrow);

    while(mobileElem > -1)
    {
        int val = per[mobileElem];

        if(arrow[mobileElem])       // If arrow points left
        {
            swap(per[mobileElem], per[mobileElem - 1]);

            bool tmp = arrow[mobileElem];                   // Swap doesn't work on bool vectors, so swapped manually
            arrow[mobileElem] = arrow[mobileElem - 1];
            arrow[mobileElem - 1] = tmp;
        }
        else                        // If arrow points right
        {
            swap(per[mobileElem], per[mobileElem + 1]);

            bool tmp = arrow[mobileElem];
            arrow[mobileElem] = arrow[mobileElem + 1];
            arrow[mobileElem + 1] = tmp;
        }

        for(int i = 0; i < per.size(); i++)
        {
            if(per[i] > val)
            {
                arrow[i] = !arrow[i];
            }
        }

        answer.push_back( getPermutedArray(a, per) );

        mobileElem = findMobileElement(per, arrow);
    }

    return answer;
}

// Checks to see if there is an increasing pair

bool hasIncreasingPair(vector<int> per)
{
    bool test = false;

    for(int i = 0; i < per.size() - 1 && !test; i++)
    {
        if(per[i] < per[i + 1])
            test = true;
    }

    return test;
}

// Finds i in Lexiographic algorithm

int findI(vector<int> per)
{
    int ans = -1;

    for(int i = per.size() - 2; i >= 0 && ans == -1; i--)
    {
        if(per[i] < per[i + 1])
            ans = i;
    }

    return ans;
}

// Finds j

int findJ(vector<int> per, int val)
{
    int ans = -1;

    for(int i = per.size() - 1; i >= 0 && ans == -1; i--)
    {
        if(val < per[i])
            ans = i;
    }

    return ans;
}

// Lexicographic-order algorithm

template <typename T>
vector<vector<T> > Lexicographic(vector<T> a)
{
    vector<vector<T> > answer;
    vector< int > per;

    setIndicieArray(per, a.size());

    answer.push_back( getPermutedArray(a, per));    // Get inital Permutation

    while(hasIncreasingPair(per))
    {
        int i = findI(per);
        int j = findJ(per, per[i]);

        swap(per[i], per[j]);           // Swap elements

        // Reverse order of i+1 to end

        int k = i + 1;
        int l = per.size() - 1;

        while(k < l)
        {
            swap(per[k], per[l]);
            k++;
            l--;
        }

        answer.push_back( getPermutedArray(a, per));
    }

    return answer;
}

template <typename T>
void rHeapsAlgorithm(vector<T>& a, vector<vector<T> >& answer, vector<int>& per, int n)
{
    if(n == 1)
    {
        answer.push_back( getPermutedArray(a, per));
        return;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            rHeapsAlgorithm(a, answer, per, n - 1);
            if(n % 2 == 1)
            {
                swap(per[0], per[n - 1]);
            }
            else
                swap(per[i], per[n - 1]);
        }

        return;
    }
}


// Heap’s algorithm

template <typename T>
vector<vector<T> > Heaps_Algorithm(vector<T> a)
{
    vector<vector<T> > answer;
    vector< int > per;

    setIndicieArray(per, a.size());

    rHeapsAlgorithm(a, answer, per, a.size());

    return answer;
}


// BozoPermutation

// Passes all test cases I have given it, but fails on upload site.

template <typename T>
vector<vector<T> > BozoPermutation(vector<T> a)
{
    set< vector<int> > intAnswers;
    vector<vector<T> > answers;
    vector<int> per;
    int numPer = 1;

    // Get indicie vector ready

    setIndicieArray(per, a.size());

    // Calculate number of per

    for(int i = 2; i <= a.size(); i ++)
        numPer *= i;

    // Shuffle and add to set till size is correct

    while(intAnswers.size() < numPer)
    {
        random_shuffle( per.begin(), per.end() );

        if(intAnswers.count(per) == 0)                      // If not in set, add to set and answers
        {
            intAnswers.insert(per);
            answers.push_back( getPermutedArray( a, per ) );
        }
    }

    return answers;
}



#endif // PERMUTATIONS_H_INCLUDED
