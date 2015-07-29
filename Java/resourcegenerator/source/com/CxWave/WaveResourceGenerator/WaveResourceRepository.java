/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Vector;

public class WaveResourceRepository
{
    private static Vector<WaveResource> m_allWaveResources     = new Vector<WaveResource> ();
    private static String               m_waveResourceEnumName = "AllWaveResources";

    public static void add (final WaveResource waveResource)
    {
        m_allWaveResources.add (waveResource);
    }

    public static void generateAllWaveResourcesJavaFile (final String destinationPath, final String packageName)
    {
        String parentDirectory = destinationPath;

        //System.out.println ("The parent directory is : " + parentDirectory);

        parentDirectory = parentDirectory.trim ();

        if ("".equals (parentDirectory))
        {
            parentDirectory = ".";
        }

        parentDirectory += "/" + packageName.replace ('.', '/');

        File dir = new File (parentDirectory);

        try
        {
            if (! (dir.exists ()))
            {
                dir.mkdirs ();
            }
        }
        catch (SecurityException securityException)
        {
            System.out.println ("Failed to generate Java Resource Enum. Failed to craete parent direcrory : " + securityException.toString ());
        }

        try (Writer writer = new BufferedWriter (new OutputStreamWriter (new FileOutputStream (parentDirectory + "/" + m_waveResourceEnumName + ".java"), "utf-8")))
        {
            writer.write ("package " + packageName + ";\n");
            writer.write ("\n");
            writer.write ("import com.CxWave.Wave.Resources.ResourceEnum.WaveResourceEnumInterface;\n");
            writer.write ("\n");
            writer.write ("public enum " + m_waveResourceEnumName + " implements WaveResourceEnumInterface\n");

            writer.write ("{\n");

            int maximumLengthForWaveResourceName = 0;

            for (WaveResource waveResource : m_allWaveResources)
            {
                int lengthForWaveResourceName = (waveResource.getWaveResourceName ()).length ();

                if (maximumLengthForWaveResourceName < lengthForWaveResourceName)
                {
                    maximumLengthForWaveResourceName = lengthForWaveResourceName;
                }
            }

            boolean firstOne = true;

            for (WaveResource waveResource : m_allWaveResources)
            {
                if (false == firstOne)
                {
                    writer.write (",\n");
                }
                else
                {
                    firstOne = false;
                }

                int    waveResourceNamePaddingSize = maximumLengthForWaveResourceName - (waveResource.getWaveResourceName ()).length ();
                String paddingString               = null;

                if (0 < waveResourceNamePaddingSize)
                {
                    paddingString = new String (new char[waveResourceNamePaddingSize]);
                    paddingString = paddingString.replace ('\0', ' ');
                }
                else
                {
                    paddingString = new String ("");
                }

                writer.write ("    ");
                writer.write (waveResource.getWaveResourceName ());
                writer.write (paddingString);
                writer.write (" (" + (String.format ("0x%08X", waveResource.getEffectiveResourceId ())) + ", \"" + waveResource.getWaveResourceName () + "\"," + paddingString + " \"" + waveResource.getWaveResourceValue () + "\")");

            }

            if (0 != (m_allWaveResources.size ()))
            {
                writer.write (";\n\n");
            }

            writer.write ("    private int    m_effectiveResourceId;\n");
            writer.write ("    private String m_name;\n");
            writer.write ("    private String m_value;\n");

            writer.write ("\n");

            writer.write ("    " + m_waveResourceEnumName + " (final int effectiveResourceId, final String name, final String value)\n");
            writer.write ("    {\n");
            writer.write ("        m_effectiveResourceId = effectiveResourceId;\n");
            writer.write ("        m_name                = name;\n");
            writer.write ("        m_value               = value;\n");
            writer.write ("    }\n");

            writer.write ("\n");

            writer.write ("    public int getEffectiveResourceId ()\n");
            writer.write ("    {\n");
            writer.write ("        return (m_effectiveResourceId);\n");
            writer.write ("    }\n");

            writer.write ("\n");

            writer.write ("    public String getName ()\n");
            writer.write ("    {\n");
            writer.write ("        return (m_name);\n");
            writer.write ("    }\n");

            writer.write ("\n");

            writer.write ("    public String getValue ()\n");
            writer.write ("    {\n");
            writer.write ("        return (m_value);\n");
            writer.write ("    }\n");

            writer.write ("}\n\n");
        }
        catch (IOException ioException)
        {
            System.out.println ("Failed to generate Java Resource Enum.  Failed to write the file : " + ioException.toString ());
        }
    }
}
