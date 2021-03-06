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

#include "types/PrimaryGPSStatus.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSStatus PrimaryGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSStatus::PrimaryGPSStatus() :
    Group(3),
    mChannelStatusData(0),
    mChannelNumber(0) {
}

PrimaryGPSStatus::PrimaryGPSStatus(const PrimaryGPSStatus& other) :
    Group(other),
    mReadByteCount(other.mReadByteCount),
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
    mGPSReceiverType(other.mGPSReceiverType),
    mGPSStatus(other.mGPSStatus),
    mChannelNumber(other.mChannelNumber) {
  if (mChannelNumber) {
    mChannelStatusData = new ChannelStatusData[mChannelNumber];
    memcpy(mChannelStatusData, other.mChannelStatusData,
      sizeof(mChannelStatusData));
  }
  else
    mChannelStatusData = 0;
}

PrimaryGPSStatus& PrimaryGPSStatus::operator =
    (const PrimaryGPSStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mReadByteCount = other.mReadByteCount;
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
    mGPSReceiverType = other.mGPSReceiverType;
    mGPSStatus = other.mGPSStatus;
    mChannelNumber = other.mChannelNumber;
    if (mChannelNumber) {
      mChannelStatusData = new ChannelStatusData[mChannelNumber];
      memcpy(mChannelStatusData, other.mChannelStatusData,
        sizeof(mChannelStatusData));
    }
    else
      mChannelStatusData = 0;
  }
  return *this;
}

PrimaryGPSStatus::~PrimaryGPSStatus() {
  if (mChannelStatusData != 0)
    delete []mChannelStatusData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSStatus::read(BinaryReader& stream) {
  stream >> mReadByteCount;
  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = (mReadByteCount - mByteCount) / 20;
  if (mChannelStatusData)
    delete []mChannelStatusData;
  if (mChannelNumber > 0)
    mChannelStatusData = new ChannelStatusData[mChannelNumber];
  for (size_t i = 0; i < mChannelNumber; i++)
    stream >> mChannelStatusData[i];
  stream >> mHDOP;
  stream >> mVDOP;
  stream >> mDGPSCorrectionLatency;
  stream >> mDGPSReferenceID;
  stream >> mGPSUTCWeekNumber;
  stream >> mGPSUTCTimeOffset;
  stream >> mGPSNavigationMessageLatency;
  stream >> mGeoidalSeparation;
  stream >> mGPSReceiverType;
  stream >> mGPSStatus;
}

void PrimaryGPSStatus::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mReadByteCount;
  stream << mTimeDistance;
  stream << mNavigationSolutionStatus;
  stream << mNumberOfSVTracked;
  stream << mChannelStatusByteCount;
  for (size_t i = 0; i < mChannelNumber; i++)
    stream << mChannelStatusData[i];
  stream << mHDOP;
  stream << mVDOP;
  stream << mDGPSCorrectionLatency;
  stream << mDGPSReferenceID;
  stream << mGPSUTCWeekNumber;
  stream << mGPSUTCTimeOffset;
  stream << mGPSNavigationMessageLatency;
  stream << mGeoidalSeparation;
  stream << mGPSReceiverType;
  stream << mGPSStatus;
}

void PrimaryGPSStatus::read(std::istream& stream) {
}

void PrimaryGPSStatus::write(std::ostream& stream) const {
}

void PrimaryGPSStatus::read(std::ifstream& stream) {
}

void PrimaryGPSStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << " ";
  stream << (int16_t)mNavigationSolutionStatus;
  stream << " ";
  stream << (uint16_t)mNumberOfSVTracked;
  stream << " ";
  stream << mChannelStatusByteCount;
  stream << " ";
  for (size_t i = 0; i < mChannelNumber; i++)
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
  stream << mGPSReceiverType;
  stream << " ";
  stream << mGPSStatus;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSStatus* PrimaryGPSStatus::clone() const {
  return new PrimaryGPSStatus(*this);
}
