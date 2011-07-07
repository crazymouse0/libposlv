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

#include "types/GeneralStatusFDIR.h"

#include "com/Connection.h"
#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GeneralStatusFDIR GeneralStatusFDIR::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeneralStatusFDIR::GeneralStatusFDIR() :
  Group(10) {
}

GeneralStatusFDIR::GeneralStatusFDIR(const GeneralStatusFDIR& other) :
  Group(other) {
}

GeneralStatusFDIR& GeneralStatusFDIR::operator =
  (const GeneralStatusFDIR& other) {
  this->Group::operator=(other);
  return *this;
}

GeneralStatusFDIR::~GeneralStatusFDIR() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GeneralStatusFDIR::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GeneralStatusFDIR::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mGeneralStatusA;
  stream >> mGeneralStatusB;
  stream >> mGeneralStatusC;
  stream >> mFDIRLevel1Status;
  stream >> mFDIRLevel1Failures;
  stream >> mFDIRLevel2Status;
  stream >> mFDIRLevel3Status;
  stream >> mFDIRLevel4Status;
  stream >> mFDIRLevel5Status;
  stream >> mExtendedStatus;
}

void GeneralStatusFDIR::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GeneralStatusFDIR::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mGeneralStatusA;
  stream >> mGeneralStatusB;
  stream >> mGeneralStatusC;
  stream >> mFDIRLevel1Status;
  stream >> mFDIRLevel1Failures;
  stream >> mFDIRLevel2Status;
  stream >> mFDIRLevel3Status;
  stream >> mFDIRLevel4Status;
  stream >> mFDIRLevel5Status;
  stream >> mExtendedStatus;
}


void GeneralStatusFDIR::read(std::istream& stream) {
}

void GeneralStatusFDIR::write(std::ostream& stream) const {
}

void GeneralStatusFDIR::read(std::ifstream& stream) {
}

void GeneralStatusFDIR::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << std::hex << mGeneralStatusA << std::dec;
  stream << " ";
  stream << std::hex << mGeneralStatusB << std::dec;
  stream << " ";
  stream << std::hex << mGeneralStatusC << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel1Status << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel1Failures << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel2Status << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel3Status << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel4Status << std::dec;
  stream << " ";
  stream << std::hex << mFDIRLevel5Status << std::dec;
  stream << " ";
  stream << std::hex << mExtendedStatus << std::dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GeneralStatusFDIR* GeneralStatusFDIR::clone() const {
  return new GeneralStatusFDIR(*this);
}