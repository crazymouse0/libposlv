#include "Auxiliary1GPSDataStream.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const Auxiliary1GPSDataStream Auxiliary1GPSDataStream::mProto;

Auxiliary1GPSDataStream::Auxiliary1GPSDataStream() : Group(10007) {
}

Auxiliary1GPSDataStream::
  Auxiliary1GPSDataStream(const Auxiliary1GPSDataStream &other)
  : Group(other) {
}

Auxiliary1GPSDataStream::~Auxiliary1GPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

void Auxiliary1GPSDataStream::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mu16VariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mu16VariableMsgByteCount];
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];
  uint32_t u32PadSize = u16ByteCount - 26 - 6 - 2 -
    mu16VariableMsgByteCount - 2 - 2;

  uint8_t u8Pad;
  for (uint32_t i = 0; i < u32PadSize; i++)
    stream >> u8Pad;
}

void Auxiliary1GPSDataStream::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 6; i++) {
    stream << mau8Reserved[i];
    stream << " ";
  }
  stream << mu16VariableMsgByteCount;
  stream << " ";
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
    stream << mau8GPSReceiverRawData[i];
    stream << " ";
  }
}

Auxiliary1GPSDataStream* Auxiliary1GPSDataStream::clone() const {
  return new Auxiliary1GPSDataStream(*this);
}
