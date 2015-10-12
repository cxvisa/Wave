/***************************************************************************
 *   Copyright (C) 2015-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

package com.CxWave.Wave.Framework.Trace;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class WaveTraceFile
{
    private String         m_traceFilePath;
    private File           m_traceFile;
    private FileWriter     m_traceFileWriter;
    private BufferedWriter m_traceFileBufferedWriter;
    private PrintWriter    m_traceFileBufferedPrintWriter;

    public WaveTraceFile ()
    {
    }

    public WaveTraceFile (final String traceFilePath)
    {
        setNewFilePath (traceFilePath);
    }

    public boolean isOpen ()
    {
        if (null != m_traceFilePath)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    public void close ()
    {
        if (isOpen ())
        {
            if (null != m_traceFileBufferedPrintWriter)
            {
                m_traceFileBufferedPrintWriter.close ();
            }

            if (null != m_traceFileBufferedWriter)
            {
                try
                {
                    m_traceFileBufferedWriter.close ();
                }
                catch (IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }

            if (null != m_traceFileWriter)
            {
                try
                {
                    m_traceFileWriter.close ();
                }
                catch (IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }

    public void flush ()
    {
        if (isOpen ())
        {
            if (null != m_traceFileBufferedWriter)
            {
                try
                {
                    m_traceFileBufferedWriter.flush ();
                }
                catch (IOException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }

    public void setNewFilePath (final String traceFilePath)
    {
        if (isOpen ())
        {
            WaveAssertUtils.waveAssert ();
            return;
        }

        m_traceFilePath = new String (traceFilePath);
        m_traceFile     = new File (traceFilePath);

        try
        {
            m_traceFileWriter = new FileWriter (m_traceFile, true);
        }
        catch (IOException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();

            WaveAssertUtils.waveAssert ();
        }

        m_traceFileBufferedWriter      = new BufferedWriter (m_traceFileWriter);
        m_traceFileBufferedPrintWriter = new PrintWriter (m_traceFileBufferedWriter);
    }

    public void resetUsingNewFilePath (final String traceFilePath)
    {
        close ();
        setNewFilePath (traceFilePath);
    }

    public void printf (final String format, final Object... objects)
    {
        if (isOpen ())
        {
            if (null != m_traceFileBufferedPrintWriter)
            {
                m_traceFileBufferedPrintWriter.printf (format, objects);
            }
        }
    }
}
