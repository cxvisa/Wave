/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"

namespace WaveNs
{

MapReduceInputConfiguration::MapReduceInputConfiguration ()
    : m_maximumNumberOfPartitions (0),
      m_timeoutInMilliSecondsForManager (10000)
{
}

MapReduceInputConfiguration::MapReduceInputConfiguration (const UI32 &maximumNumberOfPartitions)
    : m_maximumNumberOfPartitions (maximumNumberOfPartitions),
      m_timeoutInMilliSecondsForManager (10000)
{
}

MapReduceInputConfiguration::MapReduceInputConfiguration (const MapReduceInputConfiguration &mapReduceInputConfiguration)
    : m_maximumNumberOfPartitions       (mapReduceInputConfiguration.m_maximumNumberOfPartitions),
      m_timeoutInMilliSecondsForManager (mapReduceInputConfiguration.m_timeoutInMilliSecondsForManager)
{
}

MapReduceInputConfiguration::~MapReduceInputConfiguration ()
{
}

MapReduceInputConfiguration &MapReduceInputConfiguration::operator = (const MapReduceInputConfiguration &mapReduceInputConfiguration)
{
    m_maximumNumberOfPartitions = mapReduceInputConfiguration.m_maximumNumberOfPartitions;

    return (*this);
}

UI32 MapReduceInputConfiguration::getMaximumNumberOfPartitions () const
{
    return (m_maximumNumberOfPartitions);
}

void MapReduceInputConfiguration::setMaximumNumberOfPartitions (const UI32 &maximumNumberOfPartitions)
{
    m_maximumNumberOfPartitions = maximumNumberOfPartitions;
}

UI32 MapReduceInputConfiguration::getAdjustedMaximumNumberOfPartitionsRequired () const
{
    const UI32 computedMaximumNumberOfParitionsRequired = computeMaximumNumberOfPartitionsRequired ();

    return (computedMaximumNumberOfParitionsRequired < m_maximumNumberOfPartitions ? computedMaximumNumberOfParitionsRequired : computedMaximumNumberOfParitionsRequired);
}

UI32 MapReduceInputConfiguration::getTimeoutInMilliSecondsForManager () const
{
    return (m_timeoutInMilliSecondsForManager);
}

void MapReduceInputConfiguration::setTimeoutInMilliSecondsForManager (const UI32 &timeoutInMilliSecondsForManager)
{
    m_timeoutInMilliSecondsForManager = timeoutInMilliSecondsForManager;
}

}

