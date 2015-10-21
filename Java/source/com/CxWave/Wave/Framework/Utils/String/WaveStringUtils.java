/***************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.String;

import java.util.Vector;

public class WaveStringUtils
{
    private WaveStringUtils ()
    {
    }

    public static boolean isWhiteSpace (final String inputString)
    {
        if (inputString.matches ("^[\\s]*$"))
        {
            return (true);
        }

        return (false);
    }

    public static boolean isNotWhiteSpace (final String inputString)
    {
        return (!(isWhiteSpace (inputString)));
    }

    public static boolean isBlank (final String inputString)
    {
        if ((null == inputString) || (inputString.isEmpty ()))
        {
            return (true);
        }

        if (isWhiteSpace (inputString))
        {
            return (true);
        }

        return (false);
    }

    public static boolean isNotBlank (final String inputString)
    {
        return (!(isBlank (inputString)));
    }

    public static void tokenize (final String inputString, final Vector<String> tokens, final char separator)
    {
        final int inputLength = inputString.length ();
        int startPosition = 0;
        int endPosition = 0;
        String token;

        tokens.clear ();

        while (startPosition < inputLength)
        {
            endPosition = inputString.indexOf (separator, startPosition);

            if (-1 != endPosition)
            {
                if (endPosition > startPosition)
                {
                    token = inputString.substring (startPosition, endPosition);
                    tokens.add (token);
                }

                startPosition = endPosition + 1;
            }
            else
            {
                token = inputString.substring (startPosition);
                tokens.add (token);
                break;
            }
        }
    }

    public static int findFirstOccuranceOfConsideringStringQuotes (final String inputString, final char inputCharacter, final int inputStartPosition)
    {
        if (inputCharacter == '"')
        {
            return (-1);
        }

        boolean insideStringQuotes = false;
        int startPosition = inputStartPosition;
        final int stringLength = inputString.length ();
        char previousCharacter = '\0';
        char currentCharacter = '\0';

        while (stringLength > startPosition)
        {
            currentCharacter = inputString.charAt (startPosition);

            if (true == insideStringQuotes)
            {
                if (('"' == currentCharacter) && ('\\' != previousCharacter))
                {
                    insideStringQuotes = false;
                }
            }
            else
            {
                if (('"' == currentCharacter) && ('\\' != previousCharacter))
                {
                    insideStringQuotes = true;
                }
                else
                {
                    if (inputCharacter == currentCharacter)
                    {
                        return (startPosition);
                    }
                }
            }

            previousCharacter = currentCharacter;
            startPosition++;
        }

        return (-1);
    }

    public static void tokenizeConsideringStringQuotes (final String inputString, final Vector<String> tokens, final char separator)
    {
        final int inputLength = inputString.length ();
        int startPosition = 0;
        int endPosition = 0;
        String token;

        tokens.clear ();

        while (startPosition < inputLength)
        {
            endPosition = findFirstOccuranceOfConsideringStringQuotes (inputString, separator, startPosition);

            if (-1 != endPosition)
            {
                if (endPosition > startPosition)
                {
                    token = inputString.substring (startPosition, endPosition);
                    tokens.add (token);
                }

                startPosition = endPosition + 1;
            }
            else
            {
                token = inputString.substring (startPosition);
                tokens.add (token);
                break;
            }
        }
    }

    public static String replaceAllInstancesOfInputStringWith (final String source, final String inputString, final String replacementString)
    {
        return (source.replaceAll (inputString, replacementString));
    }

    public static String replaceAllInstancesOfInputCharWith (final String source, final char inputChar, final char replacementChar)
    {
        return (source.replace (inputChar, replacementChar));
    }

    public static String removeAllInstancesOfInputString (final String source, final String inputString)
    {
        return (replaceAllInstancesOfInputStringWith (source, inputString, ""));
    }

    public static String removeAllInstancesOfInputChar (final String source, final char inputChar)
    {
        return (removeAllInstancesOfInputString (source, "" + inputChar));
    }

    public static String stripFromLastOccuranceOf (final String inputString, final char inputCharacter)
    {
        final int position = inputString.lastIndexOf (inputCharacter);

        if (-1 != position)
        {
            return (inputString.substring (0, position));
        }
        else
        {
            return (inputString);
        }
    }

    public static String stripFromFirstOccuranceOf (final String inputString, final char inputCharacter)
    {
        final int position = inputString.indexOf (inputCharacter);

        if (-1 != position)
        {
            return (inputString.substring (0, position));
        }
        else
        {
            return (inputString);
        }
    }

    public static char getLowerCase (final char in)
    {
        return (Character.toLowerCase (in));
    }

    public static boolean endsWith (final String inputString, final String pattern)
    {
        boolean foundPattern = false;

        final int position = inputString.lastIndexOf (pattern);

        if (-1 != position)
        {
            if ((inputString.length ()) == (position + (pattern.length ())))
            {
                foundPattern = true;
            }
        }

        return (foundPattern);
    }

    public static boolean contains (final String inputString, final String pattern)
    {
        boolean foundPattern = false;

        final int position = inputString.indexOf (pattern);

        if (-1 != position)
        {
            foundPattern = true;
        }

        return (foundPattern);
    }

    public static void splitBasedOnLastOccuranceOf (final String inputString, final char inputCharacter, final Vector<String> firstAndSecondParts)
    {
        final int position = inputString.lastIndexOf (inputCharacter);
        String firstPart;
        String secondPart;

        if (-1 != position)
        {
            firstPart = inputString.substring (0, position);
            secondPart = inputString.substring (position + 1);
        }
        else
        {
            firstPart = inputString;
            secondPart = "";
        }

        firstAndSecondParts.add (firstPart);
        firstAndSecondParts.add (secondPart);
    }

    public static void splitBasedOnFirstOccuranceOf (final String inputString, final char inputCharacter, final Vector<String> firstAndSecondParts)
    {
        final int position = inputString.indexOf (inputCharacter);
        String firstPart;
        String secondPart;

        if (-1 != position)
        {
            firstPart = inputString.substring (0, position);
            secondPart = inputString.substring (position + 1);
        }
        else
        {
            firstPart = inputString;
            secondPart = "";
        }

        firstAndSecondParts.add (firstPart);
        firstAndSecondParts.add (secondPart);
    }

    public static void splitBasedOnFirstOccuranceOfConsideringStringQuotes (final String inputString, final char inputCharacter, final Vector<String> firstAndSecondParts)
    {
        final int position = findFirstOccuranceOfConsideringStringQuotes (inputString, inputCharacter, 0);
        String firstPart;
        String secondPart;

        if (-1 != position)
        {
            firstPart = inputString.substring (0, position);
            secondPart = inputString.substring (position + 1);
        }
        else
        {
            firstPart = inputString;
            secondPart = "";
        }

        firstAndSecondParts.add (firstPart);
        firstAndSecondParts.add (secondPart);
    }

    public static String stripAllOccurancesAtTheBegining (final String inputString, final char inputCharacter)
    {
        int position = 0;
        final int length = inputString.length ();

        while ((length > position) && (inputCharacter == (inputString.charAt (position))))
        {
            position++;
        }

        if (length > position)
        {
            return (inputString.substring (position));
        }
        else
        {
            return ("");
        }
    }

    public static String stripAllOccurancesAtTheEnd (final String inputString, final char inputCharacter)
    {
        final int length = inputString.length ();
        int position = length - 1;

        while ((0 <= position) && (inputCharacter == (inputString.charAt (position))))
        {
            position--;
        }

        if (0 <= position)
        {
            return (inputString.substring (0, position + 1));
        }
        else
        {
            return ("");
        }
    }

    public static void tokenizeStringWithCount (final String inputString, final Vector<String> tokens)
    {
        tokens.clear ();

        int startFromIndex = 0;
        int firstIndex = 0;
        int stringSize = 0;

        while (-1 != (firstIndex = inputString.indexOf ('#', startFromIndex)))
        {
            stringSize = (new Integer (inputString.substring (startFromIndex, firstIndex))).intValue ();
            tokens.add (inputString.substring (firstIndex + 1, firstIndex + 1 + stringSize));
            startFromIndex = firstIndex + stringSize + 1;
        }
    }

    public static void getCommonStringAtBeginning (final Vector<String> inputStrings, String commonStringAtBeginning)
    {
        final int numberOfInputStrings = inputStrings.size ();
        int leastStringLength = 0;
        int i = 0;
        int stringLength = 0;
        char inputCharacter;
        int j = 0;
        boolean isInputCharacterSame = true;

        if (0 == numberOfInputStrings)
        {
            commonStringAtBeginning = "";
        }
        else
        {
            leastStringLength = (inputStrings.get (0)).length ();

            for (i = 0; i < numberOfInputStrings; i++)
            {
                stringLength = (inputStrings.get (i)).length ();

                if (stringLength < leastStringLength)
                {
                    leastStringLength = stringLength;
                }
            }

            if (0 == leastStringLength)
            {
                commonStringAtBeginning = "";
            }
            else
            {
                for (i = 0; i < leastStringLength; i++)
                {
                    inputCharacter = (inputStrings.get (0)).charAt (i);
                    isInputCharacterSame = true;

                    for (j = 0; j < numberOfInputStrings; j++)
                    {
                        if (inputCharacter != (inputStrings.get (j)).charAt (i))
                        {
                            isInputCharacterSame = false;
                            break;
                        }
                    }

                    if (false == isInputCharacterSame)
                    {
                        break;
                    }
                }

                commonStringAtBeginning = (inputStrings.get (0)).substring (0, i + 1);
            }
        }
    }

    public static String joinStrings (final String string1, final String string2, final char separator)
    {
        String outputString = string1;

        if (false == (isNotBlank (string2)))
        {
            if (false == (isNotBlank (outputString)))
            {
                outputString += separator;
            }
            else
            {
                outputString = "";
            }

            outputString += string2;
        }

        return outputString;
    }

    public static String getLowerCaseString (final String inputString)
    {
        return (inputString.toLowerCase ());
    }

    public static String applyConfigStringFormatting (final String stringToBeProcessed, final boolean allowMultiWordValueWithoutQuotes)
    {
        String outputString;

        if (true == stringToBeProcessed.isEmpty ())
        {
            outputString = "\"\"";
        }
        else
        {
            boolean needsToBeQuoted = false;

            if (-1 != stringToBeProcessed.indexOf ("\n"))
            {
                needsToBeQuoted = true;
            }

            outputString = replaceAllInstancesOfInputStringWith (stringToBeProcessed, "\n", "\\n");

            if (true == needsToBeQuoted)
            {
                outputString = (new String ("\"")) + outputString + (new String ("\""));
            }
            else if (false == allowMultiWordValueWithoutQuotes)
            {
                if (-1 != stringToBeProcessed.indexOf (' '))
                {
                    outputString = (new String ("\"")) + stringToBeProcessed + (new String ("\""));
                }
            }
        }

        return (outputString);
    }

    public static boolean isStringAlphaNumeric (final String inputString)
    {
        for (final char ch : inputString.toCharArray ())
        {
            if (!((Character.isAlphabetic (ch)) || (Character.isDigit (ch))))
            {
                return (false);
            }
        }

        return (true);
    }

    public static String removeAllCharactersBetweenNewLineCharacterAndReturnCharacter (final String inputString)
    {
        String lastToken = null;
        String outputString = null;

        for (final char characterAtIterator : inputString.toCharArray ())
        {
            if ('\n' == characterAtIterator)
            {
                lastToken += characterAtIterator;

                outputString += lastToken;

                lastToken = "";
            }
            else if ('\r' == characterAtIterator)
            {
                lastToken = "";
            }
            else
            {
                lastToken += characterAtIterator;
            }
        }

        return (outputString);
    }

    public static int getCharCountAtTheBeginning (final String inputString, final char ch)
    {
        int numberOfOccurancesAtTheBegining = 0;

        for (final char characterAtInterator : inputString.toCharArray ())
        {
            if (ch == characterAtInterator)
            {
                numberOfOccurancesAtTheBegining++;
            }
            else
            {
                break;
            }
        }

        return (numberOfOccurancesAtTheBegining);
    }

    public static String convertToUpperCase (final String inputString)
    {
        return (inputString.toUpperCase ());
    }

    public static String trimWhiteSpacesAtTheBeginingAndTheEnd (final String inputString)
    {
        return (inputString.trim ());
    }

    public static String removeFirstCharacterIfMatches (final String inputString, final char inputCharacter)
    {
        if (isBlank (inputString))
        {
            return ("");
        }

        final int length = inputString.length ();
        final char firstCharacter = inputString.charAt (0);

        if (inputCharacter == firstCharacter)
        {
            return (inputString.substring (1, length));
        }
        else
        {
            return (inputString);
        }
    }

    public static String removeLastCharacterIfMatches (final String inputString, final char inputCharacter)
    {
        if (isBlank (inputString))
        {
            return ("");
        }

        final int length = inputString.length ();
        final char lastCharacter = inputString.charAt (length - 1);

        if (inputCharacter == lastCharacter)
        {
            return (inputString.substring (0, length - 1));
        }
        else
        {
            return (inputString);
        }
    }

    public static String removeFirstAndLastCharactersIfMatch (final String inputString, final char inputCharacter)
    {
        final String tempString = removeFirstCharacterIfMatches (inputString, inputCharacter);

        return (removeLastCharacterIfMatches (tempString, inputCharacter));
    }

    public static String unquote (final String inputString)
    {
        final StringBuffer tempString = new StringBuffer (removeFirstAndLastCharactersIfMatch (inputString, '"'));

        boolean insideStringQuotes = false;
        int startPosition = 0;
        final int stringLength = tempString.length ();
        char previousCharacter = '\0';
        char currentCharacter = '\0';
        final char inputCharacter = '"';

        while (stringLength > startPosition)
        {
            currentCharacter = tempString.charAt (startPosition);

            if (true == insideStringQuotes)
            {
                if (('"' == currentCharacter) && ('\\' != previousCharacter))
                {
                    insideStringQuotes = false;
                }
            }
            else
            {
                if (('"' == currentCharacter) && ('\\' != previousCharacter))
                {
                    insideStringQuotes = true;
                }
                else
                {
                    if ((inputCharacter == currentCharacter) && ('\\' == previousCharacter))
                    {
                        tempString.deleteCharAt (startPosition - 1);
                        startPosition--;
                    }
                }
            }

            previousCharacter = currentCharacter;
            startPosition++;
        }

        return (tempString.toString ());
    }
}
