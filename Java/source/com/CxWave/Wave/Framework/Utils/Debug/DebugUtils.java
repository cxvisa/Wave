/***************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Utils.Debug;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class DebugUtils
{
    public static void prettyPrint (final List<?> inputList)
    {
        int numberOfEntries = inputList.size ();
        int numberOfDecimalPositions = 0;
        int i = 0;

        while (0 != numberOfEntries)
        {
            numberOfEntries /= 10;
            numberOfDecimalPositions++;
        }

        final Iterator<?> iterator = inputList.iterator ();
        final StringBuilder printFormatString = new StringBuilder ();

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

    public static <T> void prettyPrint (final Set<T> inputSet)
    {
        prettyPrint (new ArrayList<T> (inputSet));
    }
}
