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


#if !defined(FIT_MESG_CAPABILITIES_MESG_HPP)
#define FIT_MESG_CAPABILITIES_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class MesgCapabilitiesMesg : public Mesg
{
   public:
      MesgCapabilitiesMesg(void) : Mesg(Profile::MESG_MESG_CAPABILITIES)
      {
      }

      MesgCapabilitiesMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns message_index field
      ///////////////////////////////////////////////////////////////////////
      FIT_MESSAGE_INDEX GetMessageIndex(void) const
      {
         return GetFieldUINT16Value(254, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set message_index field
      ///////////////////////////////////////////////////////////////////////
      void SetMessageIndex(FIT_MESSAGE_INDEX messageIndex)
      {
         SetFieldUINT16Value(254, messageIndex, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns file field
      ///////////////////////////////////////////////////////////////////////
      FIT_FILE GetFile(void) const
      {
         return GetFieldENUMValue(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set file field
      ///////////////////////////////////////////////////////////////////////
      void SetFile(FIT_FILE file)
      {
         SetFieldENUMValue(0, file, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns mesg_num field
      ///////////////////////////////////////////////////////////////////////
      FIT_MESG_NUM GetMesgNum(void) const
      {
         return GetFieldUINT16Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set mesg_num field
      ///////////////////////////////////////////////////////////////////////
      void SetMesgNum(FIT_MESG_NUM mesgNum)
      {
         SetFieldUINT16Value(1, mesgNum, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns count_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_MESG_COUNT GetCountType(void) const
      {
         return GetFieldENUMValue(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set count_type field
      ///////////////////////////////////////////////////////////////////////
      void SetCountType(FIT_MESG_COUNT countType)
      {
         SetFieldENUMValue(2, countType, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns count field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetCount(void) const
      {
         return GetFieldUINT16Value(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set count field
      ///////////////////////////////////////////////////////////////////////
      void SetCount(FIT_UINT16 count)
      {
         SetFieldUINT16Value(3, count, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns num_per_file field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetNumPerFile(void) const
      {
         return GetFieldUINT16Value(3, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_NUM_PER_FILE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set num_per_file field
      ///////////////////////////////////////////////////////////////////////
      void SetNumPerFile(FIT_UINT16 numPerFile)
      {
         SetFieldUINT16Value(3, numPerFile, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_NUM_PER_FILE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns max_per_file field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetMaxPerFile(void) const
      {
         return GetFieldUINT16Value(3, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_MAX_PER_FILE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set max_per_file field
      ///////////////////////////////////////////////////////////////////////
      void SetMaxPerFile(FIT_UINT16 maxPerFile)
      {
         SetFieldUINT16Value(3, maxPerFile, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_MAX_PER_FILE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns max_per_file_type field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT16 GetMaxPerFileType(void) const
      {
         return GetFieldUINT16Value(3, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_MAX_PER_FILE_TYPE);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set max_per_file_type field
      ///////////////////////////////////////////////////////////////////////
      void SetMaxPerFileType(FIT_UINT16 maxPerFileType)
      {
         SetFieldUINT16Value(3, maxPerFileType, 0, (FIT_UINT16) Profile::MESG_CAPABILITIES_MESG_COUNT_FIELD_MAX_PER_FILE_TYPE);
      }

};

} // namespace fit

#endif // !defined(FIT_MESG_CAPABILITIES_MESG_HPP)
