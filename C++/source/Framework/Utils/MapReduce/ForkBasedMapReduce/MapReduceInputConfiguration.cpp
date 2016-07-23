/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/MapReduce/ForkBasedMapReduce/MapReduceInputConfiguration.h"

namespace WaveNs
{

MapReduceInputConfiguration::MapReduceInputConfiguration ()
    : m_maximumNumberOfPartitions (0)
{
}

MapReduceInputConfiguration::MapReduceInputConfiguration (const MapReduceInputConfiguration &mapReduceInputConfiguration)
    : m_maximumNumberOfPartitions (mapReduceInputConfiguration.m_maximumNumberOfPartitions)
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

}

