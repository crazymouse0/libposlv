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

#include "visualization/PrimaryGPSStatusTab.h"

#include "types/PrimaryGPSStatus.h"
#include "types/PPSTimeRecoveryStatus.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_PrimaryGPSStatusTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSStatusTab::PrimaryGPSStatusTab() :
    mUi(new Ui_PrimaryGPSStatusTab()) {
  mUi->setupUi(this);
  mStatusMsg[-1] = "Unknown";
  mStatusMsg[0] = "No data from receiver";
  mStatusMsg[1] = "Horizontal C/A mode";
  mStatusMsg[2] = "3-dimension C/A mode";
  mStatusMsg[3] = "Horizontal DGPS mode";
  mStatusMsg[4] = "3-dimension DGPS mode";
  mStatusMsg[5] = "Float RTK mode";
  mStatusMsg[6] = "Integer wide lane RTK mode";
  mStatusMsg[7] = "Integer narrow lane RTK mode";
  mStatusMsg[8] = "P-code";
  mGPSTypeMsg[0] = "No receiver";
  for (size_t i = 1; i <= 7; i++)
    mGPSTypeMsg[i] = "Reserved";
  mGPSTypeMsg[8] = "Trimble BD112";
  mGPSTypeMsg[9] = "Trimble BD750";
  mGPSTypeMsg[10] = "Reserved";
  mGPSTypeMsg[11] = "Reserved";
  mGPSTypeMsg[12] = "Trimble BD132";
  mGPSTypeMsg[13] = "Trimble BD950";
  mGPSTypeMsg[14] = "Reserved";
  mGPSTypeMsg[15] = "Reserved";
  mGPSTypeMsg[16] = "Trimble BD960";
  mTimeSyncMsg[0] = "Not synchronized";
  mTimeSyncMsg[1] = "Synchronizing";
  mTimeSyncMsg[2] = "Fully synchronized";
  mTimeSyncMsg[3] = "Using old offset";
}

PrimaryGPSStatusTab::~PrimaryGPSStatusTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PrimaryGPSStatusTab::enableFields() {
  mUi->navPrimGPSText->setEnabled(true);
  mUi->satPrimGPSSpinBox->setEnabled(true);
  mUi->primGPSTypeText->setEnabled(true);
  mUi->geoidalPrimGPSSpinBox->setEnabled(true);
  mUi->hdopSpinBox->setEnabled(true);
  mUi->vdopSpinBox->setEnabled(true);
  mUi->dgpsIDSpinBox->setEnabled(true);
  mUi->corrLatencySpinBox->setEnabled(true);
  mUi->navLatencySpinBox->setEnabled(true);
  mUi->weekSpinBox->setEnabled(true);
  mUi->offsetSpinBox->setEnabled(true);
  mUi->ppsSpinBox->setEnabled(true);
  mUi->timeStatusText->setEnabled(true);
}

void PrimaryGPSStatusTab::disableFields() {
  mUi->navPrimGPSText->setEnabled(false);
  mUi->satPrimGPSSpinBox->setEnabled(false);
  mUi->primGPSTypeText->setEnabled(false);
  mUi->geoidalPrimGPSSpinBox->setEnabled(false);
  mUi->hdopSpinBox->setEnabled(false);
  mUi->vdopSpinBox->setEnabled(false);
  mUi->dgpsIDSpinBox->setEnabled(false);
  mUi->corrLatencySpinBox->setEnabled(false);
  mUi->navLatencySpinBox->setEnabled(false);
  mUi->weekSpinBox->setEnabled(false);
  mUi->offsetSpinBox->setEnabled(false);
  mUi->ppsSpinBox->setEnabled(false);
  mUi->timeStatusText->setEnabled(false);
}

void PrimaryGPSStatusTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<PrimaryGPSStatus>()) {
      enableFields();
      const PrimaryGPSStatus& msg = group.typeCast<PrimaryGPSStatus>();
      mUi->navPrimGPSText->setText(
        mStatusMsg[msg.mNavigationSolutionStatus].c_str());
      mUi->satPrimGPSSpinBox->setValue(msg.mNumberOfSVTracked);
      mUi->primGPSTypeText->setText(mGPSTypeMsg[msg.mGPSReceiverType].c_str());
      mUi->geoidalPrimGPSSpinBox->setValue(msg.mGeoidalSeparation);
      mUi->hdopSpinBox->setValue(msg.mHDOP);
      mUi->vdopSpinBox->setValue(msg.mVDOP);
      mUi->dgpsIDSpinBox->setValue(msg.mDGPSReferenceID);
      mUi->corrLatencySpinBox->setValue(msg.mDGPSCorrectionLatency);
      mUi->navLatencySpinBox->setValue(msg.mGPSNavigationMessageLatency);
      mUi->weekSpinBox->setValue(msg.mGPSUTCWeekNumber);
      mUi->offsetSpinBox->setValue(msg.mGPSUTCTimeOffset);
    }
    if (group.instanceOf<PPSTimeRecoveryStatus>()) {
      const PPSTimeRecoveryStatus& msg =
        group.typeCast<PPSTimeRecoveryStatus>();
      mUi->ppsSpinBox->setValue(msg.mPPSCount);
      mUi->timeStatusText->setText(
        mTimeSyncMsg[msg.mTimeSynchroStatus].c_str());
    }
  }
}