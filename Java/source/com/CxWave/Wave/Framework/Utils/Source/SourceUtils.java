/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Source;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Vector;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import com.CxWave.Wave.Framework.Utils.Environment.EnvironmentUtils;

/**
 * A toolkit to interact with the source code in the project environment.
 *
 * @author Vidyasagara Guntaka
 *
 */

public class SourceUtils
{
    private static boolean s_isInitialized = false;

    public static boolean getIsInitialized ()
    {
        return (s_isInitialized);
    }

    private static void setIsInitialized (final boolean isInitialized)
    {
        s_isInitialized = isInitialized;
    }

    private static void getListOfAllFilesInTheDirectoryInternal (final File[] inputFiles, final Vector<String> allFiles)
    {
        for (final File file : inputFiles)
        {
            if (file.isDirectory ())
            {
                try
                {
                    allFiles.add (file.getCanonicalPath ());
                }
                catch (final IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace ();
                }

                final File[] filesInDirecrory = file.listFiles ();

                getListOfAllFilesInTheDirectoryInternal (filesInDirecrory, allFiles);
            }
            else
            {
                try
                {
                    if (file.exists ())
                    {
                        allFiles.add (file.getCanonicalPath ());
                    }
                }
                catch (final IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace ();
                }
            }
        }
    }

    /**
     * Returns a list of all files and directories in the given set of directory paths
     *
     * @param directoryPaths
     *            The array holding the input directory paths. It is expected that there will be only directory paths in the
     *            input and no simple file names (including symbolic links etc.,). If any of the input entries corresponds to a
     *            non directory entry (like file) it will be present in the output.
     *
     * @return Returns a List containing the names of all directories and files obtained by traversing recursively all of the
     *         input directory paths. The entries corresponding the valid elements in the input will be present in the output.
     */

    public static List<String> getListOfAllFilesInTheDirectories (final String[] directoryPaths)
    {
        final Vector<File> inputFiles = new Vector<File> ();
        final Vector<String> allFiles = new Vector<String> ();

        for (final String directoryPath : directoryPaths)
        {
            inputFiles.add (new File (directoryPath));
        }

        getListOfAllFilesInTheDirectoryInternal (inputFiles.toArray (new File[1]), allFiles);

        return (allFiles);
    }

    /**
     * A convenience method to obtain list of all files and directory names by recursively traversing the given directory path.
     *
     * @param directoryPath
     *            The input directory path. It is expected to be a directory path. If a non directory path is given, it will
     *            alone be present in the output.
     *
     * @return Returns a list of all directories and files present in the given directory tree. If the input is a valid
     *         directory path / file, it will be present in the output. If the input is not a valid directory path then the
     *         returned List will be empty. If the input is a valid non-directory entity then the output contains only the
     *         element corresponding to the input.
     */

    public static List<String> getListOfAllFilesInTheDirectory (final String directoryPath)
    {
        final Vector<String> directoryPaths = new Vector<String> ();

        if (null != directoryPath)
        {
            directoryPaths.add (directoryPath);
        }

        return (getListOfAllFilesInTheDirectories (directoryPaths.toArray (new String[1])));
    }

    private static void getListOfAllDirectoriesInTheDirectoryInternal (final File[] inputFiles, final Vector<String> allFiles)
    {
        for (final File file : inputFiles)
        {
            if (file.isDirectory ())
            {
                try
                {
                    allFiles.add (file.getCanonicalPath ());
                }
                catch (final IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace ();
                }

                final File[] filesInDirecrory = file.listFiles ();

                getListOfAllDirectoriesInTheDirectoryInternal (filesInDirecrory, allFiles);
            }
        }
    }

    /**
     * Returns a list of all directories in the given set of directory paths
     *
     * @param directoryPaths
     *            The array holding the input directory paths. It is expected that there will be only directory paths in the
     *            input and no simple file names (including symbolic links etc.,). Any non directory paths in the input will be
     *            ignored.
     *
     * @return Returns a List containing the names of all directories (only) obtained by traversing recursively all of the input
     *         directory trees. There will not be paths corresponding to any files. The valid entries corresponding to
     *         directories in the input will be present in the output.
     *
     */

    public static List<String> getListOfAllDirectoriesInTheDirectories (final String[] directoryPaths)
    {
        final Vector<File> inputFiles = new Vector<File> ();
        final Vector<String> allFiles = new Vector<String> ();

        for (final String directoryPath : directoryPaths)
        {
            final File fileForDirectoryPath = new File (directoryPath);

            if (fileForDirectoryPath.isDirectory ())
            {
                inputFiles.add (new File (directoryPath));
            }
        }

        getListOfAllDirectoriesInTheDirectoryInternal (inputFiles.toArray (new File[1]), allFiles);

        return (allFiles);
    }

    /**
     * A convenience method to obtain list of all directories in a given directory.
     *
     * @param directoryPath
     *            The input directory path. It is expected to be a directory path. If a non directory path as input will be
     *            ignored and an empty List will be returned.
     *
     * @return Returns the list of all directories (only) obtained by recursively traversing the given directory tree. If the
     *         input corresponds to a valid directory path, it will be present in the output. If the input is not a valid
     *         directory path then an empty list will be returned.
     *
     */

    public static List<String> getListOfAllDirectoriesInTheDirectory (final String directoryPath)
    {
        final Vector<String> directoryPaths = new Vector<String> ();

        if (null != directoryPath)
        {
            directoryPaths.add (directoryPath);
        }

        return (getListOfAllDirectoriesInTheDirectories (directoryPaths.toArray (new String[1])));
    }

    /**
     * Obtains and returns a list of all files ONLY by traversing the given set of input directory paths.
     *
     * @param directoryPaths
     *            An array containing the directory paths that should be recursively traversed. It is expected that these are
     *            directories. Any invalid elements will be ignored. If an element is a non -directory element and is valid, it
     *            will be present in the output.
     *
     * @return Returns a list of file Files ONLY by traversing the given set of input directory paths. There will be no
     *         directories in the output.
     */

    public static List<String> getListOfAllFilesOnlyInTheDirectories (final String[] directoryPaths)
    {
        final Vector<File> inputFiles = new Vector<File> ();
        final Vector<String> allFiles = new Vector<String> ();

        for (final String directoryPath : directoryPaths)
        {
            final File fileForDirectoryPath = new File (directoryPath);

            if (fileForDirectoryPath.isDirectory ())
            {
                inputFiles.add (new File (directoryPath));
            }
            else
            {
                allFiles.add (directoryPath);
            }
        }

        getListOfAllFilesOnlyInTheDirectoryInternal (inputFiles.toArray (new File[1]), allFiles);

        return (allFiles);
    }

    private static void getListOfAllFilesOnlyInTheDirectoryInternal (final File[] inputFiles, final Vector<String> allFiles)
    {
        for (final File file : inputFiles)
        {
            if (file.isDirectory ())
            {
                final File[] filesInDirecrory = file.listFiles ();

                getListOfAllFilesOnlyInTheDirectoryInternal (filesInDirecrory, allFiles);
            }
            else
            {
                try
                {
                    if (file.exists ())
                    {
                        allFiles.add (file.getCanonicalPath ());
                    }
                }
                catch (final IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace ();
                }
            }
        }
    }

    /**
     * A convenience method to obtain a list of files ONLY by recursively traversing the given input directory
     *
     * @param directoryPath
     *            The input directory that needs to traversed recursively. It is expected that this will be a directory. If a
     *            non-directory valid file is given then this element will alone be present in the output list.
     *
     * @return list of files ONLY by recursively traversing the given input directory. If the input is a valid directory, then
     *         the directory will be traversed recursively for further processing. If the input is a non existent file or
     *         directory, then the returned list will be empty. If the input is a valid non-directory file path, then this path
     *         alone will be present in the output.
     */

    public static List<String> getListOfAllFilesOnlyInTheDirectory (final String directoryPath)
    {
        final Vector<String> directoryPaths = new Vector<String> ();

        if (null != directoryPath)
        {
            directoryPaths.add (directoryPath);
        }

        return (getListOfAllFilesOnlyInTheDirectories (directoryPaths.toArray (new String[1])));
    }

    public static List<String> getListOfAllAvailableClassFilesInTheDirectory (final String directoryPath)
    {
        final Vector<String> listOfAllAvailableClassFilesInTheDirectory = new Vector<String> ();
        final List<String> listOfAllFilesOnlyInTheDirectory = getListOfAllFilesOnlyInTheDirectory (directoryPath);

        for (final String availableFileInTheDirectory : listOfAllFilesOnlyInTheDirectory)
        {
            if (availableFileInTheDirectory.endsWith (".class"))
            {
                listOfAllAvailableClassFilesInTheDirectory.add (availableFileInTheDirectory);
            }
        }

        return (listOfAllAvailableClassFilesInTheDirectory);
    }

    public static List<String> getListOfAllAvailableJarFiles ()
    {
        Enumeration<URL> urlEnum;
        final Vector<String> listOfAllJarFilesAvailable = new Vector<String> ();

        try
        {
            urlEnum = Thread.currentThread ().getContextClassLoader ().getResources (JarFile.MANIFEST_NAME);

            while (urlEnum.hasMoreElements ())
            {
                final URL url = urlEnum.nextElement ();

                final String urlName = url.toString ();

                final String[] urlNameParts = urlName.split (":");

                assert 3 == urlNameParts.length : "The JAR File Manifest location expected to have 3 parts when split using :";

                // Example :
                // jar:file:/home/sagar/CxWave/Wave/Java/resourcegenerator/build/lib/WaveResourceGenerator.jar!/META-INF/MANIFEST.MF

                final String manifestLocation = urlNameParts[2];

                final String[] manifestLocationParts = manifestLocation.split ("!");

                assert 2 == manifestLocationParts.length : "After splitting using : the Manifest URL is supposed to have 2 parts when split by !";

                final String jarFilePath = manifestLocationParts[0];

                listOfAllJarFilesAvailable.add (jarFilePath);
            }
        }
        catch (final IOException exception2)
        {
            exception2.printStackTrace ();
        }

        return (listOfAllJarFilesAvailable);
    }

    public static List<String> getListOfAllAvailableClassFilesFromJarFile (final String jarFilePath)
    {
        final Vector<String> listOfAllAvailableClassFromJarFile = new Vector<String> ();

        if (null != jarFilePath)
        {
            try
            {
                final JarFile jarFile = new JarFile (jarFilePath);

                final Enumeration<JarEntry> jarEntries = jarFile.entries ();

                while (jarEntries.hasMoreElements ())
                {
                    final JarEntry jarEntry = jarEntries.nextElement ();
                    final String jarEntryName = jarEntry.getName ();

                    if (jarEntryName.endsWith (".class"))
                    {
                        listOfAllAvailableClassFromJarFile.add (jarEntryName);
                    }
                }

                jarFile.close ();
            }
            catch (final IOException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace ();
            }
        }

        return (listOfAllAvailableClassFromJarFile);
    }

    public static List<String> getListOfAllAvailableClassFilesFromAllAvailableJarFiles ()
    {
        final Vector<String> listOfAllAvailableClassFilesFromAllAvailableJarFiles = new Vector<String> ();
        final List<String> allAvailableJarFiles = getListOfAllAvailableJarFiles ();

        if (null != allAvailableJarFiles)
        {
            for (final String availableJarFile : allAvailableJarFiles)
            {
                final List<String> listOfAllAvailableClassFilesFromJarFile = getListOfAllAvailableClassFilesFromJarFile (availableJarFile);

                if (null != listOfAllAvailableClassFilesFromJarFile)
                {
                    listOfAllAvailableClassFilesFromAllAvailableJarFiles.addAll (listOfAllAvailableClassFilesFromJarFile);
                }
            }
        }

        return (listOfAllAvailableClassFilesFromAllAvailableJarFiles);
    }

    public static List<String> getListOfAllAvailableClassPathDirectories ()
    {
        final Vector<String> listOfAllAvailableClassPathDirectories = new Vector<String> ();
        final List<String> classPathCommandLineArguments = EnvironmentUtils.getClassPathCommandLineArguments ();

        for (final String classPathCommandLineArgument : classPathCommandLineArguments)
        {
            if (false == (classPathCommandLineArgument.endsWith (".jar")))
            {
                final Path classPathCommandLineArgumentPath = (FileSystems.getDefault ()).getPath (classPathCommandLineArgument);

                listOfAllAvailableClassPathDirectories.add (((classPathCommandLineArgumentPath.toAbsolutePath ()).normalize ()).toString ());
            }
        }

        return (listOfAllAvailableClassPathDirectories);
    }

    public static List<String> getListOfAllAvailableClassFilesFromAllAvailableClassPathDirectories ()
    {
        final Vector<String> listOfAllAvailableClassFilesFromAllAvailableClassPathDirectories = new Vector<String> ();
        final List<String> listOfAllAvailableClassPathDirectories = getListOfAllAvailableClassPathDirectories ();

        for (final String availableClassPathDirectory : listOfAllAvailableClassPathDirectories)
        {
            final List<String> listOfAllAvailableClassFilesInTheDirectory = getListOfAllAvailableClassFilesInTheDirectory (availableClassPathDirectory);

            if (null != listOfAllAvailableClassFilesInTheDirectory)
            {
                listOfAllAvailableClassFilesFromAllAvailableClassPathDirectories.addAll (listOfAllAvailableClassFilesInTheDirectory);
            }
        }

        return (listOfAllAvailableClassFilesFromAllAvailableClassPathDirectories);
    }

    public static List<String> getListOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories ()
    {
        final Vector<String> listOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories = new Vector<String> ();
        final List<String> listOfAllAvailableClassPathDirectories = getListOfAllAvailableClassPathDirectories ();

        for (final String availableClassPathDirectory : listOfAllAvailableClassPathDirectories)
        {
            final List<String> listOfAllAvailableClassFilesInTheDirectory = getListOfAllAvailableClassFilesInTheDirectory (availableClassPathDirectory);

            if (null != listOfAllAvailableClassFilesInTheDirectory)
            {
                for (final String availableClassFileInTheDirectory : listOfAllAvailableClassFilesInTheDirectory)
                {
                    // Even if the directory hierarchy has a duplicated struture, only the first part matching the class path
                    // directory will be replaced to be functionally correct.
                    // For Example, if class path is /a/b and the class file is /a/b/c/a/b/x.class then the result should be
                    // c/a/b/x.class

                    final String availableClassFileRelativeToTheDirectory = availableClassFileInTheDirectory.replaceFirst (availableClassPathDirectory + "/", "");

                    listOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories.add (availableClassFileRelativeToTheDirectory);
                }
            }
        }

        return (listOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories);
    }

    public static List<String> getListOfAllAvailableClasses ()
    {
        final List<String> listOfAllVailableClassFilesFromAllAvailableJarFiles = getListOfAllAvailableClassFilesFromAllAvailableJarFiles ();
        final List<String> listOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories = getListOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories ();

        final Set<String> allAvailableClasses = new HashSet<String> ();

        for (final String availableClassFromJarFile : listOfAllVailableClassFilesFromAllAvailableJarFiles)
        {
            allAvailableClasses.add ((availableClassFromJarFile.replaceFirst (".class$", "")).replace ('/', '.'));
        }

        for (final String availableClassFileRelativeToClassPathDirectory : listOfAllAvailableClassFilesRelativeToAllAvailableClassPathDirectories)
        {
            allAvailableClasses.add ((availableClassFileRelativeToClassPathDirectory.replaceFirst (".class$", "")).replace ('/', '.'));
        }

        final Vector<String> allAvailableClassFileVector = new Vector<String> ();

        allAvailableClassFileVector.addAll (allAvailableClasses);

        return (allAvailableClassFileVector);
    }

    public static void initialize ()
    {
        WaveJavaSourceRepository.initialize ();

        setIsInitialized (true);
    }
}
