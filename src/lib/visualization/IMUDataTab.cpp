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

#include "visualization/IMUDataTab.h"

#include <sstream>

#include "types/TimeTaggedIMUData.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_IMUDataTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IMUDataTab::IMUDataTab() :
    mUi(new Ui_IMUDataTab()) {
  mUi->setupUi(this);
  mStatusMsg[0] = "1 bad raw IMU frame";
  mStatusMsg[1] = "2 bad raw IMU frames";
  mStatusMsg[2] = "3 bad raw IMU frames";
  mStatusMsg[3] = "OK";
}

IMUDataTab::~IMUDataTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void IMUDataTab::enableFields(bool enable) {
  mUi->typeSpinBox->setEnabled(enable);
  mUi->rateSpinBox->setEnabled(enable);
  mUi->statusText->setEnabled(enable);
}

void IMUDataTab::readPacket(std::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<TimeTaggedIMUData>()) {
      enableFields(true);
      const TimeTaggedIMUData& msg = group.typeCast<TimeTaggedIMUData>();
      mUi->typeSpinBox->setValue(msg.mIMUType);
      size_t dataRate;
      switch (msg.mIMUType) {
        case 1:case 2: case 7:
          dataRate = 200;
          break;
        case 17:
          dataRate = 100;
          break;
        default:
          break;
      }
      mUi->rateSpinBox->setValue(dataRate);
      std::stringstream status;
      if (msg.mDataStatus) {
        for (size_t i = 0; i <= 2; i++)
          if ((msg.mDataStatus >> i) & 0x01)
            status << mStatusMsg[i] << std::endl;
      }
      else
        status << mStatusMsg[3];
      mUi->statusText->setText(status.str().c_str());
    }
  }
}
