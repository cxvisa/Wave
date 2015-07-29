/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Debug;

import java.util.Iterator;
import java.util.List;

public class DebugUtils
{
    public static void prettyPrint (List<?> inputList)
    {
        int numberOfEntries          = inputList.size ();
        int numberOfDecimalPositions = 0;
        int i                        = 0;

        while (0 != numberOfEntries)
        {
            numberOfEntries /= 10;
            numberOfDecimalPositions++;
        }

        Iterator<?>   iterator          = inputList.iterator ();
        StringBuilder printFormatString = new StringBuilder ();

        printFormatString.append ("[%1$0");
        printFormatString.append ((new Integer (numberOfDecimalPositions)).toString ());
        printFormatString.append ("d] %2$s");

        while (iterator.hasNext ())
        {
            System.out.format (printFormatString.toString (), i, (iterator.next ()).toString ());
            System.out.println ();

            i++;
        }
    }
}
