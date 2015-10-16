/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc             *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.WaveResourceGenerator;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.net.URL;
import java.net.URLDecoder;
import java.security.CodeSource;
import java.security.ProtectionDomain;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

class WaveResourceGenerator
{
    private String m_waveComponentsFilePath;
    private String m_packageName;
    private String m_destinationPath;

    WaveResourceGenerator ()
    {
        m_waveComponentsFilePath = "";
        m_packageName            = "";
        m_destinationPath        = "";
    }

    public String getPackageName ()
    {
        return (m_packageName);
    }

    public String getDestinationPath ()
    {
        return (m_destinationPath);
    }

    private static void print (final String[] arguments)
    {
        for (String argument : arguments)
        {
            System.out.print (argument + " ");
        }

        System.out.println ();
    }

    private void printCurrentSettings()
    {
        System.out.format ("Wave Components File  : %s\n", m_waveComponentsFilePath);
        System.out.format ("Package Name          : %s\n", m_packageName);
        System.out.format ("Destination Directory : %s\n", m_destinationPath);

    }

    private static void usage (final String[] arguments)
    {
        print (arguments);
    }

    private void parseAndSetArguments (final String[] arguments)
    {
        final int numberOfArguments = arguments.length;

        for (int i = 0; i < numberOfArguments; i++)
        {
            final String argument = arguments[i];

            if (argument.equals("-wavecomponents"))
            {
                m_waveComponentsFilePath = arguments[i + 1];
                i++;
            }
            else if (argument.equals("-package"))
            {
                m_packageName = arguments[i + 1];
                i++;
            }
            else if (argument.equals ("-destination"))
            {
                m_destinationPath = arguments[i + 1];
                i++;
            }
        }
    }

    public void load ()
    {
        try
        {
            WaveComponents waveComponents = new WaveComponents ();

            waveComponents.setPackageName     (m_packageName);
            waveComponents.setDestinationPath (m_destinationPath);

            waveComponents.loadFromFile (m_waveComponentsFilePath);
        }
        catch (Exception exception)
        {
            System.err.println ("Errored out with Exception : " + exception.toString ());

            exception.printStackTrace ();
        }
    }

    public void printAllAvailableClassesInThisBundle ()
    {
        ProtectionDomain protectionDomain = (getClass ()).getProtectionDomain ();
        CodeSource       codeSource       = protectionDomain.getCodeSource ();
        URL              locationUrl      = codeSource.getLocation ();
        String           locationString   = null;

        try
        {
            locationString = URLDecoder.decode (locationUrl.toString (), "UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        System.out.println ("Location : " + locationString);

        boolean isLoadedFromAJarFile = locationString.endsWith (".jar");
        String  method               = null;
        String  jarFileLocation      = null;

        if (isLoadedFromAJarFile)
        {
            String[] locationStringComponents = locationString.split (":", 2);

            if (2 == locationStringComponents.length)
            {
                method          = locationStringComponents[0];
                jarFileLocation = locationStringComponents[1];
            }

            System.out.println ("Method   : " + method);
            System.out.println ("Jar File : " + jarFileLocation);
        }

        if (null != jarFileLocation)
        {
            try
            {
                JarFile jarFile = new JarFile (jarFileLocation);

                Enumeration<JarEntry> jarEntries = jarFile.entries ();

                for (;jarEntries.hasMoreElements ();)
                {
                    JarEntry jarEntry = jarEntries.nextElement ();

                    System.out.println ("    " + jarEntry.getName ());
                    System.out.println ("        " + jarEntry.toString ());

                }

                jarFile.close ();
            }
            catch (IOException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    public static void printAllLoadedClasses ()
    {
        Field f = null;

        try
        {
            f = ClassLoader.class.getDeclaredField("classes");
        }
        catch (NoSuchFieldException | SecurityException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        f.setAccessible(true);

        Object object = null;

        try
        {
            object = f.get (ClassLoader.getSystemClassLoader ());
        }
        catch (IllegalArgumentException | IllegalAccessException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        Vector<Class<?>> classes = new Vector<Class<?>> ();

        if (object instanceof Vector<?>)
        {
            Vector<?> temporaryClassesVector = (Vector<?>) object;
            int numberOfElements = temporaryClassesVector.size ();

            for (int i = 0; i < numberOfElements; i++)
            {
                Class<?> temporaryClass = (Class<?>) temporaryClassesVector.elementAt (i);

                classes.add (temporaryClass);
            }
        }

        Iterator<Class<?>> iterator = classes.iterator ();

        while (iterator.hasNext ())
        {
            Class<?> loadedClass = (Class<?>) (iterator.next ());

            System.out.println ("Loaded Class : " + loadedClass.getCanonicalName () + ",\n" +
                    "               " + loadedClass.getName () + ",\n" +
                    "               " + loadedClass.getSimpleName ());
        }
    }

    public static void printManifestInfo ()
    {
        Enumeration<URL> resEnum;
        try {
            resEnum = Thread.currentThread().getContextClassLoader().getResources(JarFile.MANIFEST_NAME);

            while (resEnum.hasMoreElements()) {
                try {
                    URL url = (URL)resEnum.nextElement();

                    System.out.println ("URL : " + url.toString ());
                    /*
                    InputStream is = url.openStream();
                    if (is != null) {
                        Manifest manifest = new Manifest(is);
                        Attributes mainAttribs = manifest.getMainAttributes();

                        for (Map.Entry<Object, Object> entry : mainAttribs.entrySet ())
                        {
                            System.out.printf ("Manifest Key : %s, Value : %s\n", entry.getKey ().toString (), entry.getValue ().toString ());
                        }
                    }
                    */
                }
                catch (Exception e) {
                    // Silently ignore wrong manifests on classpath?
                    e.printStackTrace ();
                }

            }
        } catch (IOException e1) {
            // Silently ignore wrong manifests on classpath?
            e1.printStackTrace ();
        }
    }

    public static void main (String[] arguments)
    {
        int numberOfArguments = arguments.length;

        if ((0 == numberOfArguments) || (0 != (numberOfArguments % 2)))
        {
            usage (arguments);

            System.exit (-1);
        }

        WaveResourceGenerator waveResourceGenerator = new WaveResourceGenerator ();

        waveResourceGenerator.parseAndSetArguments (arguments);
        waveResourceGenerator.printCurrentSettings ();
        waveResourceGenerator.load ();

        printAllLoadedClasses ();

        waveResourceGenerator.printAllAvailableClassesInThisBundle ();

        WaveResourceRepository.generateAllWaveResourcesJavaFile         (waveResourceGenerator.getDestinationPath (), waveResourceGenerator.getPackageName ());
        WaveResourceRepository.generateWaveResourcesRepositoryPopulator (waveResourceGenerator.getDestinationPath (), waveResourceGenerator.getPackageName ());

        printManifestInfo ();
    }
}
