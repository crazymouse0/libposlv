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

#include "types/ChannelStatusData.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ChannelStatusData::ChannelStatusData() {
}

ChannelStatusData::ChannelStatusData(const ChannelStatusData& other) :
    mSVPRN(other.mSVPRN),
    mChannelTrackingStatus(other.mChannelTrackingStatus),
    mSVAzimuth(other.mSVAzimuth),
    mSVElevation(other.mSVElevation),
    mSVL1SNR(other.mSVL1SNR),
    mSVL2SNR(other.mSVL2SNR) {
}

ChannelStatusData& ChannelStatusData::operator =
    (const ChannelStatusData& other) {
  if (this != &other) {
    mSVPRN = other.mSVPRN;
    mChannelTrackingStatus = other.mChannelTrackingStatus;
    mSVAzimuth = other.mSVAzimuth;
    mSVElevation = other.mSVElevation;
    mSVL1SNR = other.mSVL1SNR;
    mSVL2SNR = other.mSVL2SNR;
  }
  return *this;
}

ChannelStatusData::~ChannelStatusData() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/
void ChannelStatusData::read(BinaryReader& stream) {
  stream >> mSVPRN;
  stream >> mChannelTrackingStatus;
  stream >> mSVAzimuth;
  stream >> mSVElevation;
  stream >> mSVL1SNR;
  stream >> mSVL2SNR;
}

void ChannelStatusData::write(BinaryWriter& stream) const {
  stream << mSVPRN;
  stream << mChannelTrackingStatus;
  stream << mSVAzimuth;
  stream << mSVElevation;
  stream << mSVL1SNR;
  stream << mSVL2SNR;
}

void ChannelStatusData::read(std::istream& stream) {
}

void ChannelStatusData::write(std::ostream& stream) const {
}

void ChannelStatusData::read(std::ifstream& stream) {
}

void ChannelStatusData::write(std::ofstream& stream) const {
  stream << mSVPRN;
  stream << " ";
  stream << mChannelTrackingStatus;
  stream << " ";
  stream << mSVAzimuth;
  stream << " ";
  stream << mSVElevation;
  stream << " ";
  stream << mSVL1SNR;
  stream << " ";
  stream << mSVL2SNR;
}

BinaryReader& operator >> (BinaryReader& stream, ChannelStatusData& obj) {
  obj.read(stream);
  return stream;
}

BinaryWriter& operator << (BinaryWriter& stream, const ChannelStatusData& obj) {
  obj.write(stream);
  return stream;
}
