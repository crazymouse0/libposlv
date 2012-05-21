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

#include "types/SaveRestoreControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SaveRestoreControl SaveRestoreControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SaveRestoreControl::SaveRestoreControl() :
    Message(54) {
}

SaveRestoreControl::SaveRestoreControl(const SaveRestoreControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mControl(other.mControl) {
}

SaveRestoreControl& SaveRestoreControl::operator =
    (const SaveRestoreControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mControl = other.mControl;
  }
  return *this;
}

SaveRestoreControl::~SaveRestoreControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SaveRestoreControl::read(BinaryReader& stream) {
}

void SaveRestoreControl::write(BinaryWriter& stream) const {
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mControl;
  uint8_t pad = 0;
  stream << pad;
  checksum += ((pad << 8) | mControl);
  checksum = 65536 - checksum;
  stream << checksum;
}

void SaveRestoreControl::read(std::istream& stream) {
}

void SaveRestoreControl::write(std::ostream& stream) const {
}

void SaveRestoreControl::read(std::ifstream& stream) {
}

void SaveRestoreControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

SaveRestoreControl* SaveRestoreControl::clone() const {
  return new SaveRestoreControl(*this);
}
