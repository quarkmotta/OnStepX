#pragma once

#include <stdint.h>
#include <Arduino.h>


class NvDevice {
public:

  enum class IoStatus : uint8_t
  {
    Ok,
    OutOfRange,
    NotReady,
    IoError,
    ReadOnly
  };


  enum class Endurance : uint8_t
  {
    Low,
    Mid,
    High
  };


  virtual ~NvDevice() = default;


  virtual bool init()
  {
    return true;
  }


  virtual uint32_t sizeBytes() const = 0;


  virtual Endurance endurance() const
  {
    return Endurance::Low;
  }


  virtual IoStatus read(
      uint16_t addr,
      void* dst,
      uint16_t len) = 0;


  virtual IoStatus write(
      uint16_t addr,
      const void* src,
      uint16_t len) = 0;


  virtual void poll()
  {
  }


  virtual bool hasCommit() const
  {
    return false;
  }


  virtual IoStatus commit()
  {
    return IoStatus::Ok;
  }


  virtual bool commitDone() const
  {
    return true;
  }


  virtual bool supportsWriteBlock16() const
  {
    return false;
  }


  virtual IoStatus writeBlock16(
      uint16_t blockIdx,
      const void* src16)
  {
    const uint32_t addr =
        ((uint32_t)blockIdx) << 4;

    if (addr + 16u > sizeBytes())
      return IoStatus::OutOfRange;

    return write(
        (uint16_t)addr,
        src16,
        16);
  }


  virtual bool supportsReadBlock16() const
  {
    return false;
  }


  virtual IoStatus readBlock16(
      uint16_t blockIdx,
      void* dst16)
  {
    const uint32_t addr =
        ((uint32_t)blockIdx) << 4;

    if (addr + 16u > sizeBytes())
      return IoStatus::OutOfRange;

    return read(
        (uint16_t)addr,
        dst16,
        16);
  }


  virtual bool isReadable() const
  {
    return true;
  }


  virtual bool isWritable() const
  {
    return true;
  }


protected:

};
