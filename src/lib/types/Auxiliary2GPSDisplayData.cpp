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

#include "types/Auxiliary2GPSDisplayData.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary2GPSDisplayData Auxiliary2GPSDisplayData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary2GPSDisplayData::Auxiliary2GPSDisplayData() :
    Group(24),
    mGPSRawData(0) {
}

Auxiliary2GPSDisplayData::Auxiliary2GPSDisplayData(const
    Auxiliary2GPSDisplayData& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
    mGPSRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSRawData, other.mGPSRawData, sizeof(mGPSRawData));
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

Auxiliary2GPSDisplayData& Auxiliary2GPSDisplayData::operator =
    (const Auxiliary2GPSDisplayData& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    mGPSRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSRawData, other.mGPSRawData, sizeof(mGPSRawData));
  }
  return *this;
}

Auxiliary2GPSDisplayData::~Auxiliary2GPSDisplayData() {
  if (mGPSRawData)
    delete []mGPSRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary2GPSDisplayData::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream >> mReserved[i];
  stream >> mVariableMsgByteCount;
  if (mGPSRawData)
    delete []mGPSRawData;
  mGPSRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mGPSRawData[i];
  size_t padSize = byteCount - mVariableMsgByteCount - 38;
  uint8_t pad;
  for (size_t i = 0; i < padSize; i++) {
    stream >> pad;
    if (pad != 0)
      throw IOException("Auxiliary2GPSDisplayData::read(): wrong pad");
  }
}

void Auxiliary2GPSDisplayData::read(std::istream& stream) {
}

void Auxiliary2GPSDisplayData::write(std::ostream& stream) const {
}

void Auxiliary2GPSDisplayData::read(std::ifstream& stream) {
}

void Auxiliary2GPSDisplayData::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  for (size_t i = 0; i < 6; i++) {
    stream << std::hex << (uint16_t)mReserved[i] << std::dec;
    stream << " ";
  }
  stream << mVariableMsgByteCount;
  stream << " ";
  for (size_t i = 0; i < mVariableMsgByteCount; i++) {
    stream << std::hex << (uint16_t)mGPSRawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Auxiliary2GPSDisplayData* Auxiliary2GPSDisplayData::clone() const {
  return new Auxiliary2GPSDisplayData(*this);
}
