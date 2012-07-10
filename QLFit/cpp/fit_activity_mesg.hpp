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
// ****WARNING****  This file is auto-generated!  Do NOT edit this file.
// Profile Version = 3.10Release
// Tag = $Name: AKW3_100 $
////////////////////////////////////////////////////////////////////////////////


#if !defined(FIT_ACTIVITY_MESG_HPP)
#define FIT_ACTIVITY_MESG_HPP

#include "fit_mesg.hpp"
#include "fit_mesg_with_event.hpp"

namespace fit
{

class ActivityMesg : public Mesg, public MesgWithEvent
{
   public:
      ActivityMesg(void) : Mesg(Profile::MESG_ACTIVITY)
      {
      }

      ActivityMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns timestamp field
      ///////////////////////////////////////////////////////////////////////
      FIT_DATE_TIME GetTimestamp(void) const
      {
         return GetFieldUINT32Value(253, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set timestamp field
      ///////////////////////////////////////////////////////////////////////
      void SetTimestamp(FIT_DATE_TIME timestamp)
      {
         SetFieldUINT32Value(253, timestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns total_timer_time field
      // Units: s
      // Comment: Exclude pauses
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetTotalTimerTime(void) const
      {
         return GetFieldFLOAT32Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set total_timer_time field
      // Units: s
      // Comment: Exclude pauses
      ///////////////////////////////////////////////////////////////////////
      void SetTotalTimerTime(FIT_FLOAT32 totalTimerTime)
      {
         SetFieldFLOAT32Value(0, totalTimerTime, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns num_sessions field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetNumSessions(void) const
      {
         return GetFieldUINT16Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set num_sessions field
      ///////////////////////////////////////////////////////////////////////
      void SetNumSessions(FIT_UINT16 numSessions)
      {
         SetFieldUINT16Value(1, numSessions, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns type field
      ///////////////////////////////////////////////////////////////////////
      FIT_ACTIVITY GetType(void) const
      {
         return GetFieldENUMValue(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set type field
      ///////////////////////////////////////////////////////////////////////
      void SetType(FIT_ACTIVITY type)
      {
         SetFieldENUMValue(2, type, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns event field
      ///////////////////////////////////////////////////////////////////////
      FIT_EVENT GetEvent(void) const
      {
         return GetFieldENUMValue(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set event field
      ///////////////////////////////////////////////////////////////////////
      void SetEvent(FIT_EVENT event)
      {
         SetFieldENUMValue(3, event, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns event_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_EVENT_TYPE GetEventType(void) const
      {
         return GetFieldENUMValue(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set event_type field
      ///////////////////////////////////////////////////////////////////////
      void SetEventType(FIT_EVENT_TYPE eventType)
      {
         SetFieldENUMValue(4, eventType, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns local_timestamp field
      // Comment: Use to convert activity timestamps to local time if device does not support time zone and daylight savings time correction.
      ///////////////////////////////////////////////////////////////////////
      FIT_LOCAL_DATE_TIME GetLocalTimestamp(void) const
      {
         return GetFieldUINT32Value(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set local_timestamp field
      // Comment: Use to convert activity timestamps to local time if device does not support time zone and daylight savings time correction.
      ///////////////////////////////////////////////////////////////////////
      void SetLocalTimestamp(FIT_LOCAL_DATE_TIME localTimestamp)
      {
         SetFieldUINT32Value(5, localTimestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns event_group field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetEventGroup(void) const
      {
         return GetFieldUINT8Value(6, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set event_group field
      ///////////////////////////////////////////////////////////////////////
      void SetEventGroup(FIT_UINT8 eventGroup)
      {
         SetFieldUINT8Value(6, eventGroup, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_ACTIVITY_MESG_HPP)
