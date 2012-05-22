/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "types/Auxiliary1GPSStatus.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary1GPSStatus Auxiliary1GPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary1GPSStatus::Auxiliary1GPSStatus() :
    Group(12),
    mChannelStatusData(0) {
}

Auxiliary1GPSStatus::Auxiliary1GPSStatus(const Auxiliary1GPSStatus& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mNavigationSolutionStatus(other.mNavigationSolutionStatus),
    mNumberOfSVTracked(other.mNumberOfSVTracked),
    mChannelStatusByteCount(other.mChannelStatusByteCount),
    mHDOP(other.mHDOP),
    mVDOP(other.mVDOP),
    mDGPSCorrectionLatency(other.mDGPSCorrectionLatency),
    mDGPSReferenceID(other.mDGPSReferenceID),
    mGPSUTCWeekNumber(other.mGPSUTCWeekNumber),
    mGPSUTCTimeOffset(other.mGPSUTCTimeOffset),
    mGPSNavigationMessageLatency(other.mGPSNavigationMessageLatency),
    mGeoidalSeparation(other.mGeoidalSeparation),
    mNMEAMessageReceived(other.mNMEAMessageReceived),
    mAux12InUse(other.mAux12InUse),
    mChannelNumber(other.mChannelNumber) {
  mChannelStatusData = new ChannelStatusData[other.mChannelNumber];
  memcpy(mChannelStatusData, other.mChannelStatusData,
    sizeof(mChannelStatusData));
}

Auxiliary1GPSStatus& Auxiliary1GPSStatus::operator =
    (const Auxiliary1GPSStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mNavigationSolutionStatus = other.mNavigationSolutionStatus;
    mNumberOfSVTracked = other.mNumberOfSVTracked;
    mChannelStatusByteCount = other.mChannelStatusByteCount;
    mHDOP = other.mHDOP;
    mVDOP = other.mVDOP;
    mDGPSCorrectionLatency = other.mDGPSCorrectionLatency;
    mDGPSReferenceID = other.mDGPSReferenceID;
    mGPSUTCWeekNumber = other.mGPSUTCWeekNumber;
    mGPSUTCTimeOffset = other.mGPSUTCTimeOffset;
    mGPSNavigationMessageLatency = other.mGPSNavigationMessageLatency;
    mGeoidalSeparation = other.mGeoidalSeparation;
    mNMEAMessageReceived = other.mNMEAMessageReceived;
    mAux12InUse = other.mAux12InUse;
    mChannelNumber = other.mChannelNumber;
    mChannelStatusData = new ChannelStatusData[other.mChannelNumber];
    memcpy(mChannelStatusData, other.mChannelStatusData,
      sizeof(mChannelStatusData));
  }
  return *this;
}

Auxiliary1GPSStatus::~Auxiliary1GPSStatus() {
  if (mChannelStatusData != 0)
    delete []mChannelStatusData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary1GPSStatus::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = (byteCount - mByteCount) / mChannelStatusByteCount;
  if (mChannelStatusData)
    delete []mChannelStatusData;
  if (mChannelNumber > 0)
    mChannelStatusData = new ChannelStatusData[mChannelNumber];
  for (size_t i = 0; i < mChannelNumber; ++i)
    stream >> mChannelStatusData[i];
  stream >> mHDOP;
  stream >> mVDOP;
  stream >> mDGPSCorrectionLatency;
  stream >> mDGPSReferenceID;
  stream >> mGPSUTCWeekNumber;
  stream >> mGPSUTCTimeOffset;
  stream >> mGPSNavigationMessageLatency;
  stream >> mGeoidalSeparation;
  stream >> mNMEAMessageReceived;
  stream >> mAux12InUse;
}

void Auxiliary1GPSStatus::read(std::istream& stream) {
}

void Auxiliary1GPSStatus::write(std::ostream& stream) const {
}

void Auxiliary1GPSStatus::read(std::ifstream& stream) {
}

void Auxiliary1GPSStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << (int16_t)mNavigationSolutionStatus;
  stream << " ";
  stream << (uint16_t)mNumberOfSVTracked;
  stream << " ";
  stream << mChannelStatusByteCount;
  stream << " ";
  stream << mChannelNumber << " ";
  for (size_t i = 0; i < mChannelNumber; ++i)
    stream << mChannelStatusData[i];
  stream << mHDOP;
  stream << " ";
  stream << mVDOP;
  stream << " ";
  stream << mDGPSCorrectionLatency;
  stream << " ";
  stream << mDGPSReferenceID;
  stream << " ";
  stream << mGPSUTCWeekNumber;
  stream << " ";
  stream << mGPSUTCTimeOffset;
  stream << " ";
  stream << mGPSNavigationMessageLatency;
  stream << " ";
  stream << mGeoidalSeparation;
  stream << " ";
  stream << mNMEAMessageReceived;
  stream << " ";
  stream << (uint16_t)mAux12InUse;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Auxiliary1GPSStatus* Auxiliary1GPSStatus::clone() const {
  return new Auxiliary1GPSStatus(*this);
}
