////////////////////////////////////////////////////////////////////////////////
// The following FIT Protocol software provided may be used with FIT protocol
// devices only and remains the copyrighted property of Dynastream Innovations Inc.
// The software is being provided on an "as-is" basis and as an accommodation,
// and therefore all warranties, representations, or guarantees of any kind
// (whether express, implied or statutory) including, without limitation,
// warranties of merchantability, non-infringement, or fitness for a particular
// purpose, are specifically disclaimed.
//
// Copyright 2008 Dynastream Innovations Inc.
////////////////////////////////////////////////////////////////////////////////

#include "record_csv_writer.hpp"

using namespace fit;

RecordCSVWriter::RecordCSVWriter(std::string fileName)
: csv(fileName)
{
}

void RecordCSVWriter::Close(void)
{
   csv.Close();
}

void RecordCSVWriter::OnMesg(MesgWithEvent& mesg)
{
   if (mesg.GetTimestamp() != FIT_DATE_TIME_INVALID)
      csv.SetInt("Timestamp [s]", mesg.GetTimestamp());

   if (mesg.GetEvent() != FIT_EVENT_INVALID)
   {
      csv.SetInt("Event", mesg.GetEvent());
   }
   else
   {
      csv.SetString("Event", "");
   }

   if (mesg.GetEventType() != FIT_EVENT_TYPE_INVALID)
   {
      csv.SetInt("Event Type", mesg.GetEventType());
   }
   else
   {
      csv.SetString("Event Type", "");
   }

   if (mesg.GetEventGroup() != FIT_UINT8_INVALID)
   {
      csv.SetInt("Event Group", mesg.GetEventGroup());
   }
   else
   {
      csv.SetString("Event Group", "");
   }

   csv.Writeln();
}

void RecordCSVWriter::OnMesg(RecordMesg& mesg)
{
   if (mesg.GetTimestamp() != FIT_DATE_TIME_INVALID)
      csv.SetInt("Timestamp [s]", mesg.GetTimestamp());

   // Clear event.
   csv.SetString("Event", "");
   csv.SetString("Event Type", "");
   csv.SetString("Event Data", "");
   csv.SetString("Event Group", "");

   if (mesg.GetHeartRate() != FIT_UINT8_INVALID)
      csv.SetInt("Heart Rate [bpm]", mesg.GetHeartRate());

   if (mesg.GetCadence() != FIT_UINT8_INVALID)
      csv.SetInt("Cadence [rpm]", mesg.GetCadence());

   if (mesg.GetSpeed() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Speed [m/s]", mesg.GetSpeed());

   if (mesg.GetDistance() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Distance [m]", mesg.GetDistance());

   if (mesg.GetPower() != FIT_UINT16_INVALID)
      csv.SetInt("Power [watts]", mesg.GetPower());

   if (mesg.GetPositionLat() != FIT_SINT32_INVALID)
      csv.SetInt("Latitude [semicircles]", mesg.GetPositionLat());

   if (mesg.GetPositionLong() != FIT_SINT32_INVALID)
      csv.SetInt("Longitude [semicircles]", mesg.GetPositionLong());

   if (mesg.GetAltitude() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Altitude [m]", mesg.GetAltitude());

   if (mesg.GetGrade() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Grade [%]", mesg.GetGrade());

   if (mesg.GetResistance() != FIT_UINT8_INVALID)
      csv.SetInt("Resistance", mesg.GetResistance());

   csv.Writeln();
}

