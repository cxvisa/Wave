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

import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class WaveResourceEnum extends WaveResourceGeneratorElement
{
    private String               m_waveResourceEnumName;
    private Vector<WaveResource> m_waveResources;
    private int                  m_componentId;
    private int                  m_moduleId;
    private int                  m_resourceEnumId;
    private int                  m_nextResourceId;
    private int                  m_effectiveResourceId;
    private String               m_packageName;
    private String               m_destinationPath;

    public WaveResourceEnum ()
    {
        super (WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE_ENUM.getXmlTagName ());

        m_waveResources = new Vector<WaveResource> ();

        m_componentId         = 0;
        m_moduleId            = 0;
        m_resourceEnumId      = 0;
        m_nextResourceId      = 0;
        m_effectiveResourceId = 0;
    }

    public String getWaveResourceEnumName ()
    {
        return (m_waveResourceEnumName);
    }

    public void setWaveResourceEnumName (final String waveResourceEnumName)
    {
        m_waveResourceEnumName = waveResourceEnumName;
    }

    public int getComponentId ()
    {
        return (m_componentId);
    }

    public void setComponentId (final int componentId)
    {
        m_componentId = componentId;
    }

    public int getModuleId ()
    {
        return (m_moduleId);
    }

    public void setModuleId (final int moduleId)
    {
        m_moduleId = moduleId;
    }

    public int getResourceEnumId ()
    {
        return (m_resourceEnumId);
    }

    public void setResourceEnumId (final int resourceEnumId)
    {
        m_resourceEnumId = resourceEnumId;
        m_nextResourceId = m_resourceEnumId + 1;
    }

    public int getNextResourceId ()
    {
        return (m_nextResourceId);
    }

    public int getEffectiveResourceId ()
    {
        return (m_effectiveResourceId);
    }

    public void setEffectiveResourceId (final int effectiveResourceId)
    {
        m_effectiveResourceId = effectiveResourceId;
    }

    public String getPackageName ()
    {
        return (m_packageName);
    }

    public void setPackageName (final String packageName)
    {
        m_packageName = packageName;
    }

    @Override
    void loadFromDomNode(Node node)
    {
        String waveResourceEnumName   = null;

        NamedNodeMap attributesMap = node.getAttributes ();

        Node nameAttributeNode = attributesMap.getNamedItem ("Name");

        if (null != nameAttributeNode)
        {
            waveResourceEnumName = nameAttributeNode.getNodeValue ();
        }

        setWaveResourceEnumName (waveResourceEnumName);

        m_effectiveResourceId = (m_componentId << 30) | (m_moduleId << 16) | (m_resourceEnumId);

        System.out.format ("            Wave ResourceEnum (0x%08X, %s)\n", m_effectiveResourceId, waveResourceEnumName);

        NodeList nodeList = node.getChildNodes ();

        int numberOfNodes = nodeList.getLength ();
        int i               = 0;

        for (i = 0; i < numberOfNodes; i++)
        {
            Node childNode = nodeList.item (i);

            if (Node.ELEMENT_NODE == (childNode.getNodeType()))
            {
                final Element element        = (Element) (childNode);
                final String  elementTagName = element.getTagName ();

                if (elementTagName.equals(WaveResourceGeneratorElementType.WAVE_RESOURCE_GENERATOR_ELEMENT_TYPE_RESOURCE.getXmlTagName ()))
                {
                    WaveResource waveResource = new WaveResource ();

                    waveResource.setComponentId    (m_componentId);
                    waveResource.setModuleId       (m_moduleId);
                    waveResource.setResourceEnumId (m_resourceEnumId);
                    waveResource.setResourceId     (m_nextResourceId);

                    m_nextResourceId++;

                    waveResource.setBaseDirectoryPath (getBaseDirectoryPath ());

                    waveResource.loadFromDomNode (childNode);

                    m_waveResources.add (waveResource);

                    WaveResourceRepository.add (waveResource);
                }
            }
        }
    }

    public void generateJavaEnumFile ()
    {
        String parentDirectory = m_destinationPath;

        //System.out.println ("The parent directory is : " + parentDirectory);

        parentDirectory = parentDirectory.trim ();

        if ("".equals (parentDirectory))
        {
            parentDirectory = ".";
        }

        parentDirectory += "/" + m_packageName.replace ('.', '/');

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
            writer.write ("package " + m_packageName + ";\n");
            writer.write ("\n");
            writer.write ("import com.CxWave.Wave.Resources.ResourceEnum.WaveResourceEnumInterface;\n");
            writer.write ("\n");
            writer.write ("public enum " + m_waveResourceEnumName + " implements WaveResourceEnumInterface\n");

            writer.write ("{\n");

            int maximumLengthForWaveResourceName = 0;

            for (WaveResource waveResource : m_waveResources)
            {
                int lengthForWaveResourceName = (waveResource.getWaveResourceName ()).length ();

                if (maximumLengthForWaveResourceName < lengthForWaveResourceName)
                {
                    maximumLengthForWaveResourceName = lengthForWaveResourceName;
                }
            }

            boolean firstOne = true;

            for (WaveResource waveResource : m_waveResources)
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

            if (0 != (m_waveResources.size ()))
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

    public void setDestinationPath (final String destinationPath)
    {
        m_destinationPath = destinationPath;
    }
}
