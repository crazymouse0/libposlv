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

#include "types/AidingSensorControl.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const AidingSensorControl AidingSensorControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AidingSensorControl::AidingSensorControl() :
    Message(22) {
}

AidingSensorControl::AidingSensorControl(const AidingSensorControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mDMIScaleFactor(other.mDMIScaleFactor),
    mRefDMIX(other.mRefDMIX),
    mRefDMIY(other.mRefDMIY),
    mRefDMIZ(other.mRefDMIZ) {
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

AidingSensorControl& AidingSensorControl::operator =
    (const AidingSensorControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mDMIScaleFactor = other.mDMIScaleFactor;
    mRefDMIX = other.mRefDMIX;
    mRefDMIY = other.mRefDMIY;
    mRefDMIZ = other.mRefDMIZ;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
  }
  return *this;
}

AidingSensorControl::~AidingSensorControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void AidingSensorControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("AidingSensorControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mDMIScaleFactor;
  stream >> mRefDMIX;
  stream >> mRefDMIY;
  stream >> mRefDMIZ;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream >> mReserved[i];
}

void AidingSensorControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mDMIScaleFactor;
  stream << mRefDMIX;
  stream << mRefDMIY;
  stream << mRefDMIZ;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream << mReserved[i];
}

void AidingSensorControl::read(std::istream& stream) {
}

void AidingSensorControl::write(std::ostream& stream) const {
}

void AidingSensorControl::read(std::ifstream& stream) {
}

void AidingSensorControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

AidingSensorControl* AidingSensorControl::clone() const {
  return new AidingSensorControl(*this);
}
