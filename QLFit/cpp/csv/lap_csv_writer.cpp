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

#include "lap_csv_writer.hpp"

using namespace fit;

LapCSVWriter::LapCSVWriter(std::string fileName)
: csv(fileName)
{
}

void LapCSVWriter::Close()
{
   csv.Close();
}

void LapCSVWriter::OnMesg(LapMesg& mesg)
{
   if (mesg.GetTimestamp() != FIT_DATE_TIME_INVALID)
      csv.SetInt("Timestamp [s]", mesg.GetTimestamp());
   if (mesg.GetMessageIndex() != FIT_MESSAGE_INDEX_INVALID)
      csv.SetInt("Lap #", mesg.GetMessageIndex() + 1);
   if (mesg.GetLapTrigger() != FIT_LAP_TRIGGER_INVALID)
      csv.SetInt("Lap Trigger", mesg.GetLapTrigger());
   if (mesg.GetSport() != FIT_SPORT_INVALID)
      csv.SetInt("Sport", mesg.GetSport());
   if (mesg.GetStartTime() != FIT_DATE_TIME_INVALID)
      csv.SetInt("Start Time [s]", mesg.GetStartTime());
   if (mesg.GetTotalTimerTime() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Total Timer Time [s]", mesg.GetTotalTimerTime());
   if (mesg.GetTotalElapsedTime() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Total Elapsed Time [s]", mesg.GetTotalElapsedTime());
   if (mesg.GetStartPositionLat() != FIT_SINT32_INVALID)
      csv.SetInt("Start Latitude [semicircles]", mesg.GetStartPositionLat());
   if (mesg.GetStartPositionLong() != FIT_SINT32_INVALID)
      csv.SetInt("Start Longitude [semicircles]", mesg.GetStartPositionLong());
   if (mesg.GetEndPositionLat() != FIT_SINT32_INVALID)
      csv.SetInt("End Latitude [semicircles]", mesg.GetEndPositionLat());
   if (mesg.GetEndPositionLong() != FIT_SINT32_INVALID)
      csv.SetInt("End Longitude [semicircles]", mesg.GetEndPositionLong());
   if (mesg.GetTotalDistance() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Total Distance [m]", mesg.GetTotalDistance());
   if (mesg.GetTotalCycles() != FIT_UINT32_INVALID)
      csv.SetInt("Total Cycles [cycles]", mesg.GetTotalCycles());
   if (mesg.GetTotalCalories() != FIT_UINT16_INVALID)
      csv.SetInt("Total Calories [calories]", mesg.GetTotalCalories());
   if (mesg.GetTotalAscent() != FIT_UINT16_INVALID)
      csv.SetInt("Total Ascent [m]", mesg.GetTotalAscent());
   if (mesg.GetTotalDescent() != FIT_UINT16_INVALID)
      csv.SetInt("Total Descent [m]", mesg.GetTotalDescent());
   if (mesg.GetAvgSpeed() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Avg Speed [m/s]", mesg.GetAvgSpeed());
   if (mesg.GetMaxSpeed() != FIT_FLOAT32_INVALID)
      csv.SetDouble("Max Speed [m/s]", mesg.GetMaxSpeed());
   if (mesg.GetAvgHeartRate() != FIT_UINT8_INVALID)
      csv.SetInt("Avg Heart Rate [bpm]", mesg.GetAvgHeartRate());
   if (mesg.GetMaxHeartRate() != FIT_UINT8_INVALID)
      csv.SetInt("Max Heart Rate [bpm]", mesg.GetMaxHeartRate());
   if (mesg.GetAvgCadence() != FIT_UINT8_INVALID)
      csv.SetInt("Avg Cadence [rpm]", mesg.GetAvgCadence());
   if (mesg.GetMaxCadence() != FIT_UINT8_INVALID)
      csv.SetInt("Max Cadence [rpm]", mesg.GetMaxCadence());
   if (mesg.GetAvgPower() != FIT_UINT16_INVALID)
      csv.SetInt("Avg Power [watts]", mesg.GetAvgPower());
   if (mesg.GetMaxPower() != FIT_UINT16_INVALID)
      csv.SetInt("Max Power [watts]", mesg.GetMaxPower());

   csv.Writeln();
}
