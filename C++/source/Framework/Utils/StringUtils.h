/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "Framework/Types/Types.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

string operator +                       (const string &string1, const unsigned long long int &ulli1);
string operator +                       (const unsigned long long int &ulli1, const string &string1);

string operator +                       (const string &string1, int &si1);
string operator +                       (int &si1, const string &string1);

string operator +                       (const string &string1, const void *&pPointer);
string operator +                       (const void *&pPointer, const string &string1);

void   tokenize                         (const string &inputString, vector<string> &tokens, const char separator = ' ');
void   tokenizeConsideringStringQuotes  (const string &inputString, vector<string> &tokens, const char separator = ' ');

class StringUtils
{
    private :
    protected :
    public :
        static void                 replaceAllInstancesOfInputStringWith                            (string &source, const string &inputString, const string &replacementString);
        static void                 replaceAllInstancesOfInputCharWith                              (string& source, const char& inputChar, const char& replacementChar);
        static void                 removeAllInstancesOfInputString                                 (string &source, const string &inputString);
        static void                 removeAllInstancesOfInputChar                                   (string &source, const char &inputChar);

        static void                 tokenize                                                        (const string &inputString, vector<string> &tokens, const char separator = ' ');
        static void                 tokenizeConsideringStringQuotes                                 (const string &inputString, vector<string> &tokens, const char separator = ' ');
        static char                 getLowerCase                                                    (char in);

        static void                 stripFromLastOccuranceOf                                        (string &inputString, const char &inputCharacter = '/');
        static void                 stripFromFirstOccuranceOf                                       (string &inputString, const char &inputCharacter = '/');

        static bool                 endsWith                                                        (const string &inputString, const string &pattern);

        static void                 splitBasedOnLastOccuranceOf                                     (const string &inputString, const char &inputCharacter, string &firstPart, string &secondPart);
        static void                 splitBasedOnFirstOccuranceOf                                    (const string &inputString, const char &inputCharacter, string &firstPart, string &secondPart);
        static void                 splitBasedOnFirstOccuranceOfConsideringStringQuotes             (const string &inputString, const char &inputCharacter, string &firstPart, string &secondPart);

        static void                 stripAllOccurancesAtTheBegining                                 (string &inputString, const char &inputCharacter);
        static void                 stripAllOccurancesAtTheEnd                                      (string &inputString, const char &inputCharacter);

        static void                 getCommonStringAtBeginning                                      (const vector<string> &inputStrings, string &commonStringAtBeginning);
        static void                 tokenizeStringWithCount                                         (const string &inputString, vector<string> &tokens);

        static string               joinStrings                                                     (const string &string1, const string &string2, const char separator = ' ');
        static void                 getLowerCaseString                                              (const string &inputString, string &outputString);
        static void                 applyConfigStringFormatting                                     (string &stringToBeProcessed, const bool &allowMultiWordValueWithoutQuotes);
        static bool                 contains                                                        (const string &inputString, const string &pattern);
        static bool                 isStringAlphaNumeric                                            (const string &inputString);

        static string               removeAllCharactersBetweenNewLineCharacterAndReturnCharacter    (const string &inputString);

        static UI32                 getCharCountAtTheBegining                                       (const string &inputString, const char &inputChar);

        static void                 convertToUpperCase                                              (string &inputString);

        static void                 trimWhiteSpacesAtTheBeginingAndTheEnd                           (string &inputString);

        static string::size_type    findFirstOccuranceOfConsideringStringQuotes                     (const string &inputString, const char &inputCharacter, const string::size_type &inputStartPosition = 0);

        static void                 removeFirstCharacterIfMatches                                   (string &inputString, const char &inputCharatcer);
        static void                 removeLastCharacterIfMatches                                    (string &inputString, const char &inputCharacter);
        static void                 removeFirstAndLastCharactersIfMatch                             (string &inputString, const char &inputCharacter);

        static void                 unquote                                                         (string &inputString);

        static string::size_type    getNumberOfOccurances                                           (const string &inputString, const char &inputCharacter);
        static string::size_type    findNthOccurance                                                (const string &inputString, const char &inputCharacter, const string::size_type &n);

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // STRINGUTILS_H
