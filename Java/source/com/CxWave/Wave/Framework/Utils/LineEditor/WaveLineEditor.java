/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.LineEditor;

import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Vector;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.System.WaveSystemUtils;

public class WaveLineEditor
{
    private final Vector<String>           m_validCommands     = new Vector<String> ();
    private final Vector<String>           m_commandHistory    = new Vector<String> ();
    private final char[]                   m_inputRead         = new char[256];
    private int                            m_numberOfCharsRead = 0;
    private int                            m_currentIndex      = 0;
    private static final InputStreamReader m_inputStreamReader = new InputStreamReader (System.in);

    public WaveLineEditor ()
    {
    }

    public WaveLineEditor (final Vector<String> validCommands)
    {
        m_validCommands.addAll (validCommands);
    }

    public void addValidCommand (final String validCommand)
    {
        m_validCommands.add (validCommand);
    }

    private void readInput ()
    {
        if (m_currentIndex < m_numberOfCharsRead)
        {
            return;
        }

        m_numberOfCharsRead = 0;
        m_currentIndex = 0;

        try
        {
            if (m_inputStreamReader.ready ())
            {
                m_numberOfCharsRead = m_inputStreamReader.read (m_inputRead);
            }
        }
        catch (final IOException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace ();
        }
    }

    private char getchar ()
    {
        if (0 < m_numberOfCharsRead)
        {
            final char c = m_inputRead[m_currentIndex];

            m_currentIndex++;

            return (c);
        }

        else
        {
            WaveAssertUtils.waveAssert ();
        }

        return ('\0');
    }

    private int getNumberOfCharactersAvailableToRead ()
    {
        readInput ();

        return (m_numberOfCharsRead - m_currentIndex);
    }

    public String getUserInputLine (final String linePrompt)
    {
        int i = 0;
        int j = 0;
        char c = '\0';
        char c1 = '\0';
        char c2 = '\0';
        char c3 = '\0';
        char c4 = '\0';
        char c5 = '\0';
        char c6 = '\0';
        int numberOfCharactersAvailableToRead = 0;
        String command = new String ();
        String currentlyTypingCommand = new String ();
        int globalIndex = m_commandHistory.size ();
        int currentCommandSize = 0;
        int currentPosition = command.length ();
        final int commandPromptSize = linePrompt.length ();
        final Vector<String> matchingCommands = new Vector<String> ();

        final String[] cmds =
            {
                            "/bin/sh",
                            "-c",
                            "stty raw -echo isig </dev/tty"
            };
        WaveSystemUtils.runSystemCommand (cmds);

        System.out.printf ("%c%s>", 13, linePrompt);
        System.out.flush ();

        while (true)
        {
            try
            {
                Thread.sleep (50);
            }
            catch (final InterruptedException e)
            {
                WaveAssertUtils.waveAssert ();
            }

            if (0 != (numberOfCharactersAvailableToRead = (getNumberOfCharactersAvailableToRead ())))
            {
                // System.out.printf ("%d\r\n", numberOfCharactersAvailableToRead);

                if (6 <= numberOfCharactersAvailableToRead)
                {
                    c1 = getchar ();
                    c2 = getchar ();
                    c3 = getchar ();
                    c4 = getchar ();
                    c5 = getchar ();
                    c6 = getchar ();

                    // CTRL + RIGHT ARROW

                    if ((27 == c1) && (91 == c2) && (49 == c3) && (59 == c4) && (53 == c5) && (67 == c6))
                    {
                        final int commandLength = command.length ();

                        if (commandLength > currentPosition)
                        {
                            currentPosition++;
                        }

                        while ((commandLength - 1) > currentPosition)
                        {
                            final char currentChar = command.charAt (currentPosition);
                            final char nextChar = command.charAt (currentPosition + 1);

                            if ((' ' != currentChar) && (' ' == nextChar))
                            {
                                break;
                            }

                            currentPosition++;
                        }

                        if ((commandLength - 1) == currentPosition)
                        {
                            if (' ' == (command.charAt (currentPosition)))
                            {
                                currentPosition = command.length ();
                            }
                        }

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();
                    }

                    // CTRL + LEFT ARROW

                    if ((27 == c1) && (91 == c2) && (49 == c3) && (59 == c4) && (53 == c5) && (68 == c6))
                    {
                        if (0 < currentPosition)
                        {
                            currentPosition--;
                        }

                        while (1 < currentPosition)
                        {
                            final char currentChar = command.charAt (currentPosition);
                            final char previousChar = command.charAt (currentPosition - 1);

                            if ((' ' != currentChar) && (' ' == previousChar))
                            {
                                break;
                            }

                            currentPosition--;
                        }

                        if (1 == currentPosition)
                        {
                            if ((' ' != (command.charAt (currentPosition))) && (' ' == (command.charAt (currentPosition - 1))))
                            {
                            }
                            else
                            {
                                currentPosition = 0;
                            }
                        }

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();
                    }

                    continue;
                }

                if (3 <= numberOfCharactersAvailableToRead)
                {
                    c1 = getchar ();
                    c2 = getchar ();
                    c3 = getchar ();

                    // System.out.printf ("-->%d,%d,%d\r\n", (int) c1, (int) c2, (int) c3);

                    if ((27 == c1) && (91 == c2) && (65 == c3))
                    {
                        if (0 < globalIndex)
                        {
                            currentCommandSize = command.length ();

                            System.out.printf ("%c", 13);

                            for (i = 0; i < (currentCommandSize + commandPromptSize + 1); i++)
                            {
                                System.out.printf (" ");
                            }

                            globalIndex--;
                            command = m_commandHistory.get (globalIndex);
                            currentPosition = command.length ();
                            System.out.printf ("%c%s>%s", 13, linePrompt, command);
                            System.out.flush ();
                        }
                    }

                    if ((27 == c1) && (91 == c2) && (66 == c3))
                    {
                        if (globalIndex < (m_commandHistory.size ()))
                        {
                            currentCommandSize = command.length ();

                            System.out.printf ("%c", 13);

                            for (i = 0; i < (currentCommandSize + commandPromptSize + 1); i++)
                            {
                                System.out.printf (" ");
                            }

                            if (globalIndex < ((m_commandHistory.size ()) - 1))
                            {
                                globalIndex++;
                                command = m_commandHistory.get (globalIndex);
                            }
                            else
                            {
                                globalIndex++;
                                command = currentlyTypingCommand;
                            }

                            currentPosition = command.length ();

                            System.out.printf ("%c%s>%s", 13, linePrompt, command);
                            System.out.flush ();
                        }
                    }

                    if ((27 == c1) && (91 == c2) && (67 == c3))
                    {
                        if (currentPosition < (command.length ()))
                        {
                            currentPosition++;
                            System.out.printf ("%c", command.charAt (currentPosition - 1));
                            System.out.flush ();
                        }
                    }

                    if ((27 == c1) && (91 == c2) && (68 == c3))
                    {
                        if (0 < currentPosition)
                        {
                            currentPosition--;
                            System.out.printf ("\b");
                            System.out.flush ();
                        }
                    }

                    continue;
                }

                for (i = 0; i < numberOfCharactersAvailableToRead; i++)
                {
                    c = getchar ();

                    // System.out.printf ("-->%d\r\n", (int) c);

                    if (1 == c)
                    {
                        currentPosition = 0;

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();

                        continue;
                    }

                    if (5 == c)
                    {
                        currentPosition = command.length ();

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();

                        continue;
                    }

                    if (4 == c)
                    {
                        final String[] resetCommands =
                            {
                                            "/bin/sh",
                                            "-c",
                                            "stty cooked echo </dev/tty"
                            };

                        WaveSystemUtils.runSystemCommand (resetCommands);
                        System.exit (0);
                    }

                    if ((Character.isAlphabetic (c)) || (Character.isDigit (c)) || (' ' == c) || ('_' == c) || ('-' == c) || (':' == c) || ('.' == c) || ('=' == c) || ('/' == c) || ('\\' == c) || ('<' == c) || ('>' == c) || ('{' == c) || ('}' == c) || ('[' == c) || (']' == c) || ('"' == c) || (',' == c) || ('#' == c) || ('?' == c) || ('@' == c) || ('%' == c))
                    {
                        final StringBuffer commandBuffer = new StringBuffer (command);

                        commandBuffer.insert (currentPosition, c);
                        command = commandBuffer.toString ();
                        currentPosition++;

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();
                    }
                    else if ('\t' == c)
                    {
                        if ("" == command)
                        {
                            for (j = 0; j < m_validCommands.size (); j++)
                            {
                                System.out.printf ("\n\r  %s", m_validCommands.get (j));
                            }

                            System.out.printf ("\n\r");
                        }
                        else
                        {
                            matchingCommands.clear ();

                            for (j = 0; j < m_validCommands.size (); j++)
                            {
                                if ((m_validCommands.get (j)).startsWith (command))
                                {
                                    matchingCommands.add (m_validCommands.get (j));
                                }
                            }

                            if (1 == (matchingCommands.size ()))
                            {
                                command = matchingCommands.get (0);

                                currentPosition = command.length ();
                            }
                            else
                            {
                                for (j = 0; j < matchingCommands.size (); j++)
                                {
                                    System.out.printf ("\n\r  %s", matchingCommands.get (j));
                                }

                                System.out.printf ("\n\r");
                            }
                        }

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();
                    }
                    else if ('?' == c)
                    {
                        if ("" == command)
                        {
                            for (j = 0; j < m_validCommands.size (); j++)
                            {
                                System.out.printf ("\n\r  %s", m_validCommands.get (j));
                            }

                            System.out.printf ("\n\r");
                        }
                        else
                        {
                            matchingCommands.clear ();

                            for (j = 0; j < m_validCommands.size (); j++)
                            {
                                if ((m_validCommands.get (j)).startsWith (command))
                                {
                                    matchingCommands.add (m_validCommands.get (j));
                                }
                            }

                            for (j = 0; j < matchingCommands.size (); j++)
                            {
                                System.out.printf ("\n\r  %s", matchingCommands.get (j));
                            }

                            System.out.printf ("\n\r");
                        }

                        System.out.printf ("%c%s>%s", 13, linePrompt, command);

                        for (j = 0; j < ((command.length ()) - currentPosition); j++)
                        {
                            System.out.printf ("\b");
                        }

                        System.out.flush ();
                    }
                    else
                    {
                        if ((8 == c) || (127 == c))
                        {
                            if (0 < currentPosition)
                            {
                                System.out.printf ("%c", 13);

                                for (j = 0; j < (command.length () + commandPromptSize + 1); j++)
                                {
                                    System.out.printf (" ");
                                }

                                final StringBuffer commandBuffer = new StringBuffer (command);

                                commandBuffer.deleteCharAt (currentPosition - 1);

                                command = commandBuffer.toString ();

                                currentPosition--;

                                System.out.printf ("%c%s>%s", 13, linePrompt, command);

                                for (j = 0; j < ((command.length ()) - currentPosition); j++)
                                {
                                    System.out.printf ("\b");
                                }

                                System.out.flush ();
                            }
                        }
                    }
                }

                if (c == 13)
                {
                    System.out.printf ("\n\r");
                    System.out.flush ();

                    if (0 != (command.length ()))
                    {
                        m_commandHistory.add (command);
                    }

                    final String[] resetCommands =
                        {
                                        "/bin/sh",
                                        "-c",
                                        "stty cooked echo </dev/tty"
                        };

                    WaveSystemUtils.runSystemCommand (resetCommands);
                    return (command);
                }

                currentlyTypingCommand = command;
            }
        }
    }
}
