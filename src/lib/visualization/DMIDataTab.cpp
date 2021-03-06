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

#include "visualization/DMIDataTab.h"

#include "types/TimeTaggedDMIData.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_DMIDataTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DMIDataTab::DMIDataTab() :
    mUi(new Ui_DMIDataTab()) {
  mUi->setupUi(this);
  mStatusMsg[0] = "Invalid";
  mStatusMsg[1] = "Valid";
  mStatusMsg[2] = "Scale factor change";
  mTypeMsg[0] = "None";
  mTypeMsg[1] = "Pulse and direction";
  mTypeMsg[2] = "Quadrature";
}

DMIDataTab::~DMIDataTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void DMIDataTab::enableFields(bool enable) {
  mUi->signedSpinBox->setEnabled(enable);
  mUi->unsignedSpinBox->setEnabled(enable);
  mUi->scaleSpinBox->setEnabled(enable);
  mUi->rateSpinBox->setEnabled(enable);
  mUi->statusText->setEnabled(enable);
  mUi->typeText->setEnabled(enable);
}

void DMIDataTab::readPacket(std::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<TimeTaggedDMIData>()) {
      enableFields(true);
      const TimeTaggedDMIData& msg = group.typeCast<TimeTaggedDMIData>();
      mUi->signedSpinBox->setValue(msg.mSignedDistanceTraveled);
      mUi->unsignedSpinBox->setValue(msg.mUnsignedDistanceTraveled);
      mUi->scaleSpinBox->setValue(msg.mDMIScaleFactor);
      mUi->rateSpinBox->setValue(msg.mDMIDataRate);
      mUi->statusText->setText(mStatusMsg[msg.mDataStatus].c_str());
      mUi->typeText->setText(mTypeMsg[msg.mDMIType].c_str());
    }
  }
}
