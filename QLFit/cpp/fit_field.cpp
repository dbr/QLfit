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


#include <sstream>
#include "fit_field.hpp"
#include "fit_mesg.hpp"
#include "fit_unicode.hpp"

namespace fit
{

Field::Field(void) :
   profile(NULL)
{
}

Field::Field(const Field &field) :
   profile(field.profile), profileIndex(field.profileIndex), values(field.values)
{
}

Field::Field(const Profile::MESG_INDEX mesgIndex, const FIT_UINT16 fieldIndex) :
   profile(&Profile::mesgs[mesgIndex]), profileIndex(fieldIndex)
{
}

Field::Field(const FIT_UINT16 mesgNum, const FIT_UINT8 fieldNum) :
   profile(Profile::GetMesg(mesgNum)), profileIndex(Profile::GetFieldIndex(mesgNum, fieldNum))
{
}

Field::Field(const std::string& mesgName, const std::string& fieldName) :
   profile(Profile::GetMesg(mesgName)), profileIndex(Profile::GetFieldIndex(mesgName, fieldName))
{
}

FIT_BOOL Field::IsValid(void) const
{
   return profileIndex != FIT_UINT16_INVALID;
}

FIT_UINT16 Field::GetIndex(void) const
{
   return profileIndex;
}

std::string Field::GetName(const FIT_UINT16 subFieldIndex) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return "unknown";
   else if (subFieldIndex >= profile->fields[profileIndex].numSubFields)
      return profile->fields[profileIndex].name;
   else
      return profile->fields[profileIndex].subFields[subFieldIndex].name;
}

FIT_UINT8 Field::GetNum(void) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return FIT_FIELD_NUM_INVALID;
   return profile->fields[profileIndex].num;
}

FIT_UINT8 Field::GetType(const FIT_UINT16 subFieldIndex) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return FIT_UINT8_INVALID;
   else if (subFieldIndex >= profile->fields[profileIndex].numSubFields)
      return profile->fields[profileIndex].type;
   else
      return profile->fields[profileIndex].subFields[subFieldIndex].type;
}

FIT_BOOL Field::IsSignedInteger(const FIT_UINT16 subFieldIndex) const
{
   switch (GetType(subFieldIndex)) {
      case FIT_BASE_TYPE_SINT8:
      case FIT_BASE_TYPE_SINT16:
      case FIT_BASE_TYPE_SINT32:
         return FIT_TRUE;

      default:
         return FIT_FALSE;
   }
}

std::string Field::GetUnits(const FIT_UINT16 subFieldIndex) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return "";
   else if (subFieldIndex >= profile->fields[profileIndex].numSubFields)
      return profile->fields[profileIndex].units;
   else
      return profile->fields[profileIndex].subFields[subFieldIndex].units;
}

FIT_FLOAT32 Field::GetScale(const FIT_UINT16 subFieldIndex) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 1;
   else if (subFieldIndex >= profile->fields[profileIndex].numSubFields)
      return profile->fields[profileIndex].scale;
   else
      return profile->fields[profileIndex].subFields[subFieldIndex].scale;
}

FIT_FLOAT32 Field::GetOffset(const FIT_UINT16 subFieldIndex) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 0;
   else if (subFieldIndex >= profile->fields[profileIndex].numSubFields)
      return profile->fields[profileIndex].offset;
   else
      return profile->fields[profileIndex].subFields[subFieldIndex].offset;
}

FIT_UINT16 Field::GetNumComponents(void) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 0;
   return profile->fields[profileIndex].numComponents;
}

FIT_UINT16 Field::GetNumSubFields(void) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 0;
   return profile->fields[profileIndex].numSubFields;
}

const Profile::FIELD_COMPONENT* Field::GetComponent(const FIT_UINT16 component) const
{
   if (component >= GetNumComponents())
      return NULL;
   return &profile->fields[profileIndex].components[component];
}

const Profile::SUBFIELD* Field::GetSubField(const FIT_UINT16 subFieldIndex) const
{
   if (subFieldIndex >= GetNumSubFields())
      return NULL;
   return &profile->fields[profileIndex].subFields[subFieldIndex];
}

FIT_UINT8 Field::GetSize(void) const
{
   FIT_UINT8 size = 0;

	if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 0;

   for (FIT_UINT8 valueIndex = 0; valueIndex < values.size(); valueIndex++)
      size += values[valueIndex].size();

   return size;
}

FIT_UINT8 Field::GetNumValues(void) const
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return 0;

   return (FIT_UINT8) values.size();
}

FIT_UINT32 Field::GetBitsValue(const FIT_UINT16 offset, const FIT_UINT8 bits) const
{
   FIT_UINT32 value = 0;
   FIT_UINT8 bitsInValue = 0;
   FIT_SINT16 bitsInData;
   FIT_UINT8 index = 0;
   FIT_UINT8 data;
   FIT_UINT8 mask;
   FIT_UINT16 newOffset = offset;

   if (values.size() == 0)
      return FIT_UINT32_INVALID;

   while (bitsInValue < bits)
   {
      if (index >= values.size())
         return FIT_UINT32_INVALID;

      data = GetUINT8Value(index++);
      data >>= newOffset;
      bitsInData = 8 - newOffset;
      newOffset -= 8;

      if (bitsInData > 0)
      {
         newOffset = 0;

         if (bitsInData > (bits - bitsInValue))
            bitsInData = bits - bitsInValue;

         mask = (1 << bitsInData) - 1;
         value |= (FIT_UINT32)(data & mask) << bitsInValue;
         bitsInValue += bitsInData;
      }
   }

   return value;
}

FIT_SINT32 Field::GetBitsSignedValue(const FIT_UINT16 offset, const FIT_UINT8 bits) const
{
   FIT_UINT32 value;
   FIT_SINT32 signedValue;

   value = GetBitsValue(offset, bits);

   if (value == FIT_UINT32_INVALID)
      return FIT_SINT32_INVALID;

   signedValue = (1L << (bits - 1));

   if ((value & signedValue) != 0) // sign bit set
      signedValue = -signedValue + (value & (signedValue - 1));
   else
      signedValue = value;

   return signedValue;
}

FIT_ENUM Field::GetENUMValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_ENUM)))
      return FIT_ENUM_INVALID;

   return values[fieldArrayIndex][0];
}

FIT_BYTE Field::GetBYTEValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_BYTE)))
      return FIT_BYTE_INVALID;

   return values[fieldArrayIndex][0];
}

FIT_SINT8 Field::GetSINT8Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_SINT8)))
      return FIT_SINT8_INVALID;

   return values[fieldArrayIndex][0];
}

FIT_UINT8 Field::GetUINT8Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT8)))
      return FIT_UINT8_INVALID;

   return values[fieldArrayIndex][0];
}

FIT_UINT8Z Field::GetUINT8ZValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT8Z)))
      return FIT_UINT8Z_INVALID;

   return values[fieldArrayIndex][0];
}

FIT_SINT16 Field::GetSINT16Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_SINT16)))
      return FIT_SINT16_INVALID;

   return ((FIT_SINT16) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_UINT16 Field::GetUINT16Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT16)))
      return FIT_UINT16_INVALID;

   return ((FIT_UINT16) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_UINT16Z Field::GetUINT16ZValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT16Z)))
      return FIT_UINT16Z_INVALID;

   return ((FIT_UINT16Z) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_SINT32 Field::GetSINT32Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_SINT32)))
      return FIT_SINT32_INVALID;

   return ((FIT_SINT32) values[fieldArrayIndex][3] << 24) | ((FIT_SINT32) values[fieldArrayIndex][2] << 16) | ((FIT_SINT32) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_UINT32 Field::GetUINT32Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT32)))
      return FIT_UINT32_INVALID;

   return ((FIT_UINT32) values[fieldArrayIndex][3] << 24) | ((FIT_UINT32) values[fieldArrayIndex][2] << 16) | ((FIT_UINT32) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_UINT32Z Field::GetUINT32ZValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_UINT32Z)))
      return FIT_UINT32Z_INVALID;

   return ((FIT_UINT32Z) values[fieldArrayIndex][3] << 24) | ((FIT_UINT32Z) values[fieldArrayIndex][2] << 16) | ((FIT_UINT32Z) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
}

FIT_FLOAT32 Field::GetFLOAT32Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   FIT_FLOAT32 float32Value;

   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return FIT_FLOAT32_INVALID;

   switch (GetType()) { // Note: This checks the type of the MAIN field since data is aligned according to that type
      case FIT_BASE_TYPE_BYTE:
         {
            FIT_BYTE byteValue = GetBYTEValue(fieldArrayIndex, subFieldIndex);

            if (byteValue == FIT_BYTE_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = byteValue;
            break;
         }

      case FIT_BASE_TYPE_ENUM:
         {
            FIT_ENUM enumValue = GetENUMValue(fieldArrayIndex, subFieldIndex);

            if (enumValue == FIT_ENUM_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = enumValue;
            break;
         }

      case FIT_BASE_TYPE_SINT8:
         {
            FIT_SINT8 sint8Value = GetSINT8Value(fieldArrayIndex, subFieldIndex);

            if (sint8Value == FIT_SINT8_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = sint8Value;
            break;
         }

      case FIT_BASE_TYPE_UINT8:
         {
            FIT_UINT8 uint8Value = GetUINT8Value(fieldArrayIndex, subFieldIndex);

            if (uint8Value == FIT_UINT8_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = uint8Value;
            break;
         }

      case FIT_BASE_TYPE_UINT8Z:
         {
            FIT_UINT8Z uint8zValue = GetUINT8ZValue(fieldArrayIndex, subFieldIndex);

            if (uint8zValue == FIT_UINT8Z_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = uint8zValue;
            break;
         }

      case FIT_BASE_TYPE_SINT16:
         {
            FIT_SINT16 sint16Value = GetSINT16Value(fieldArrayIndex, subFieldIndex);

            if (sint16Value == FIT_SINT16_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = sint16Value;
            break;
         }

      case FIT_BASE_TYPE_UINT16:
         {
            FIT_UINT16 uint16Value = GetUINT16Value(fieldArrayIndex, subFieldIndex);

            if (uint16Value == FIT_UINT16_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = uint16Value;
            break;
         }

      case FIT_BASE_TYPE_UINT16Z:
         {
            FIT_UINT16Z uint16zValue = GetUINT16ZValue(fieldArrayIndex, subFieldIndex);

            if (uint16zValue == FIT_UINT16Z_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = uint16zValue;
            break;
         }

      case FIT_BASE_TYPE_SINT32:
         {
            FIT_SINT32 sint32Value = GetSINT32Value(fieldArrayIndex, subFieldIndex);

            if (sint32Value == FIT_SINT32_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = (FIT_FLOAT32) sint32Value;
            break;
         }

      case FIT_BASE_TYPE_UINT32:
         {
            FIT_UINT32 uint32Value = GetUINT32Value(fieldArrayIndex, subFieldIndex);

            if (uint32Value == FIT_UINT32_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = (FIT_FLOAT32) uint32Value;
            break;
         }

      case FIT_BASE_TYPE_UINT32Z:
         {
            FIT_UINT32Z uint32zValue = GetUINT32ZValue(fieldArrayIndex, subFieldIndex);

            if (uint32zValue == FIT_UINT32Z_INVALID)
               return FIT_FLOAT32_INVALID;

            float32Value = (FIT_FLOAT32) uint32zValue;
            break;
         }

      case FIT_BASE_TYPE_FLOAT32:
         {
            FIT_SINT32 sint32Value = GetSINT32Value(fieldArrayIndex, subFieldIndex);

            if (sint32Value == FIT_SINT32_INVALID)
               return FIT_FLOAT32_INVALID;

            memcpy(&float32Value, &sint32Value, sizeof(FIT_FLOAT32));
            break;
         }

      case FIT_BASE_TYPE_FLOAT64:
         return (FIT_FLOAT32) GetFLOAT32Value(fieldArrayIndex, subFieldIndex);
         break;

      default:
         return FIT_FLOAT32_INVALID;
   }

   return float32Value / GetScale(subFieldIndex) - GetOffset(subFieldIndex);
}

FIT_FLOAT64 Field::GetFLOAT64Value(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   FIT_FLOAT64 float64Value;

   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return FIT_FLOAT64_INVALID;

   switch (GetType()) { // Note: This checks the type of the MAIN field since data is aligned according to that type
      case FIT_BASE_TYPE_BYTE:
         {
            FIT_BYTE byteValue = GetBYTEValue(fieldArrayIndex, subFieldIndex);

            if (byteValue == FIT_BYTE_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = byteValue;
            break;
         }

      case FIT_BASE_TYPE_ENUM:
         {
            FIT_ENUM enumValue = GetENUMValue(fieldArrayIndex, subFieldIndex);

            if (enumValue == FIT_ENUM_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = enumValue;
            break;
         }

      case FIT_BASE_TYPE_SINT8:
         {
            FIT_SINT8 sint8Value = GetSINT8Value(fieldArrayIndex, subFieldIndex);

            if (sint8Value == FIT_SINT8_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = sint8Value;
            break;
         }

      case FIT_BASE_TYPE_UINT8:
         {
            FIT_UINT8 uint8Value = GetUINT8Value(fieldArrayIndex, subFieldIndex);

            if (uint8Value == FIT_UINT8_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint8Value;
            break;
         }

      case FIT_BASE_TYPE_UINT8Z:
         {
            FIT_UINT8Z uint8zValue = GetUINT8ZValue(fieldArrayIndex, subFieldIndex);

            if (uint8zValue == FIT_UINT8Z_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint8zValue;
            break;
         }

      case FIT_BASE_TYPE_SINT16:
         {
            FIT_SINT16 sint16Value = GetSINT16Value(fieldArrayIndex, subFieldIndex);

            if (sint16Value == FIT_SINT16_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = sint16Value;
            break;
         }

      case FIT_BASE_TYPE_UINT16:
         {
            FIT_UINT16 uint16Value = GetUINT16Value(fieldArrayIndex, subFieldIndex);

            if (uint16Value == FIT_UINT16_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint16Value;
            break;
         }

      case FIT_BASE_TYPE_UINT16Z:
         {
            FIT_UINT16Z uint16zValue = GetUINT16ZValue(fieldArrayIndex, subFieldIndex);

            if (uint16zValue == FIT_UINT16Z_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint16zValue;
            break;
         }

      case FIT_BASE_TYPE_SINT32:
         {
            FIT_SINT32 sint32Value = GetSINT32Value(fieldArrayIndex, subFieldIndex);

            if (sint32Value == FIT_SINT32_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = sint32Value;
            break;
         }

      case FIT_BASE_TYPE_UINT32:
         {
            FIT_UINT32 uint32Value = GetUINT32Value(fieldArrayIndex, subFieldIndex);

            if (uint32Value == FIT_UINT32_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint32Value;
            break;
         }

      case FIT_BASE_TYPE_UINT32Z:
         {
            FIT_UINT32Z uint32zValue = GetUINT32ZValue(fieldArrayIndex, subFieldIndex);

            if (uint32zValue == FIT_UINT32Z_INVALID)
               return FIT_FLOAT64_INVALID;

            float64Value = uint32zValue;
            break;
         }

      case FIT_BASE_TYPE_FLOAT32:
         return (FIT_FLOAT64) GetFLOAT32Value(fieldArrayIndex, subFieldIndex);
         break;

      case FIT_BASE_TYPE_FLOAT64:
         {
            unsigned long long uint64Value;

            if ((fieldArrayIndex >= values.size()) || (values[fieldArrayIndex].size() < sizeof(FIT_FLOAT64)))
               return FIT_FLOAT64_INVALID;

            uint64Value = ((unsigned long long) values[fieldArrayIndex][7] << 56) | ((unsigned long long) values[fieldArrayIndex][6] << 48) | ((unsigned long long) values[fieldArrayIndex][5] << 40)
                  | ((unsigned long long) values[fieldArrayIndex][4] << 32) | ((unsigned long long) values[fieldArrayIndex][3] << 24) | ((unsigned long long) values[fieldArrayIndex][2] << 16)
                  | ((unsigned long long) values[fieldArrayIndex][1] << 8) | values[fieldArrayIndex][0];
            memcpy(&float64Value, &uint64Value, sizeof(FIT_FLOAT64));
            break;
         }

      default:
         return FIT_FLOAT64_INVALID;
   }

   return float64Value / GetScale(subFieldIndex) - GetOffset(subFieldIndex);
}

FIT_WSTRING Field::GetSTRINGValue(const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex) const
{
   Unicode::UTF8_STRING value;

   if ((profile == NULL) || (profileIndex >= profile->numFields) || (fieldArrayIndex >= values.size()))
      return FIT_WSTRING_INVALID;

   if (GetType() == FIT_BASE_TYPE_STRING) // Note: This checks the type of the MAIN field since data is aligned according to that type
   {
      FIT_UINT8 i = 0;

      while ((i < values[fieldArrayIndex].size()) && (values[fieldArrayIndex][i] != 0))
      {
         value += static_cast<Unicode::UTF8_STRING::value_type>(values[fieldArrayIndex][i]);
         i++;
      }
   }
   else
   {
      FIT_FLOAT64 floatValue = GetFLOAT64Value(fieldArrayIndex, subFieldIndex);

      if (floatValue != FIT_FLOAT64_INVALID)
      {
         Unicode::UTF8_OSSTREAM valueStream;
         valueStream.setf(std::ios_base::fixed);
         valueStream.precision(9);
         valueStream << floatValue;
         value = valueStream.str();

         if ((value.find('.') != Unicode::UTF8_STRING::npos) && (value[value.length() - 1] == '0'))
         {
            Unicode::UTF8_STRING::size_type lastZeroIndex = value.length() - 1;

            while (value[lastZeroIndex - 1] == '0')
               lastZeroIndex--;

            if (value[lastZeroIndex - 1] == '.')
               value.erase(lastZeroIndex - 1);
            else
               value.erase(lastZeroIndex);
         }
      }
      else
      {
         value = "";
      }
   }

   return Unicode::Encode_UTF8ToBase(value);
}

void Field::SetENUMValue(const FIT_ENUM value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT8Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetBYTEValue(const FIT_BYTE value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT8Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetSINT8Value(const FIT_SINT8 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT8Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetUINT8Value(const FIT_UINT8 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   while (values.size() <= fieldArrayIndex)
   {
      std::vector<FIT_BYTE> newValueBytes;
      values.push_back(newValueBytes);
   }

   values[fieldArrayIndex].clear();
   values[fieldArrayIndex].push_back((FIT_BYTE) value);
}

void Field::SetUINT8ZValue(const FIT_UINT8 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT8Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetSINT16Value(const FIT_SINT16 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT16Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetUINT16Value(const FIT_UINT16 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   while (values.size() <= fieldArrayIndex)
   {
      std::vector<FIT_BYTE> newValueBytes;
      values.push_back(newValueBytes);
   }

   values[fieldArrayIndex].clear();
   values[fieldArrayIndex].push_back((FIT_BYTE) value);
   values[fieldArrayIndex].push_back((FIT_BYTE)(value >> 8));
}

void Field::SetUINT16ZValue(const FIT_UINT16Z value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT16Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetSINT32Value(const FIT_SINT32 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT32Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetUINT32Value(const FIT_UINT32 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   while (values.size() <= fieldArrayIndex)
   {
      std::vector<FIT_BYTE> newValueBytes;
      values.push_back(newValueBytes);
   }

   values[fieldArrayIndex].clear();
   values[fieldArrayIndex].push_back((FIT_BYTE) value);
   values[fieldArrayIndex].push_back((FIT_BYTE)(value >> 8));
   values[fieldArrayIndex].push_back((FIT_BYTE)(value >> 16));
   values[fieldArrayIndex].push_back((FIT_BYTE)(value >> 24));
}

void Field::SetUINT32ZValue(const FIT_UINT32Z value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetUINT32Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetFLOAT32Value(const FIT_FLOAT32 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   SetFLOAT64Value(value, fieldArrayIndex, subFieldIndex);
}

void Field::SetFLOAT64Value(const FIT_FLOAT64 value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return;

   FIT_FLOAT64 recalculatedValue = (value + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);

   switch (GetType()) { // Note: This checks the type of the MAIN field since data is aligned according to that type
      case FIT_BASE_TYPE_BYTE:
      case FIT_BASE_TYPE_ENUM:
      case FIT_BASE_TYPE_SINT8:
      case FIT_BASE_TYPE_UINT8:
      case FIT_BASE_TYPE_UINT8Z:
         SetUINT8Value((FIT_UINT8) recalculatedValue, fieldArrayIndex, subFieldIndex);
         break;

      case FIT_BASE_TYPE_SINT16:
      case FIT_BASE_TYPE_UINT16:
      case FIT_BASE_TYPE_UINT16Z:
         SetUINT16Value((FIT_UINT16) recalculatedValue, fieldArrayIndex, subFieldIndex);
         break;

      case FIT_BASE_TYPE_SINT32:
      case FIT_BASE_TYPE_UINT32:
      case FIT_BASE_TYPE_UINT32Z:
         SetUINT32Value((FIT_UINT32) recalculatedValue, fieldArrayIndex, subFieldIndex);
         break;

      case FIT_BASE_TYPE_FLOAT32:
         {
            FIT_FLOAT32 float32Value = (FIT_FLOAT32)recalculatedValue;
            FIT_UINT32 uint32Value;
            memcpy(&uint32Value, &float32Value, sizeof(FIT_FLOAT32));
            SetUINT32Value(uint32Value, fieldArrayIndex, subFieldIndex);
            break;
         }

      case FIT_BASE_TYPE_FLOAT64:
         while (values.size() <= fieldArrayIndex)
         {
            std::vector<FIT_BYTE> newValueBytes;
            values.push_back(newValueBytes);
         }

         values[fieldArrayIndex].clear();
         values[fieldArrayIndex].push_back(*((FIT_BYTE *) &recalculatedValue));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 1));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 2));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 3));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 4));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 5));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 6));
         values[fieldArrayIndex].push_back(*(((FIT_BYTE *) &recalculatedValue) + 7));
         break;

      default:
         break;
   }
}

void Field::SetSTRINGValue(const FIT_WSTRING& value, const FIT_UINT8 fieldArrayIndex, const FIT_UINT16 subFieldIndex)
{
   if ((profile == NULL) || (profileIndex >= profile->numFields))
      return;

   while (values.size() <= fieldArrayIndex)
   {
      std::vector<FIT_BYTE> newValueBytes;
      values.push_back(newValueBytes);
   }

   Unicode::UTF8_STRING stringValue = Unicode::Encode_BaseToUTF8(value);

   switch (GetType()) { // Note: This checks the type of the MAIN field since data is aligned according to that type
      case FIT_BASE_TYPE_STRING:
         values[fieldArrayIndex].clear();

         for (int i = 0; i < (int) stringValue.length(); i++)
            values[fieldArrayIndex].push_back(static_cast<FIT_BYTE>(stringValue[i]));

         values[fieldArrayIndex].push_back(0); // null terminate
         break;

      case FIT_BASE_TYPE_BYTE:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 byteValueAsFloat64;
            ss << stringValue;
            ss >> byteValueAsFloat64;

            if (ss.fail())
            {
               SetBYTEValue(FIT_BYTE_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               byteValueAsFloat64 = (byteValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               byteValueAsFloat64 += ((byteValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetBYTEValue(static_cast<FIT_BYTE>(byteValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_ENUM:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 enumValueAsFloat64;
            ss << stringValue;
            ss >> enumValueAsFloat64;

            if (ss.fail())
            {
               SetENUMValue(FIT_ENUM_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               enumValueAsFloat64 = (enumValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               enumValueAsFloat64 += ((enumValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetENUMValue(static_cast<FIT_ENUM>(enumValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_SINT8:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 sint8ValueAsFloat64;
            ss << stringValue;
            ss >> sint8ValueAsFloat64;

            if (ss.fail())
            {
               SetSINT8Value(FIT_SINT8_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               sint8ValueAsFloat64 = (sint8ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               sint8ValueAsFloat64 += ((sint8ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetSINT8Value(static_cast<FIT_SINT8>(sint8ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT8:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint8ValueAsFloat64;
            ss << stringValue;
            ss >> uint8ValueAsFloat64;

            if (ss.fail())
            {
               SetUINT8Value(FIT_UINT8_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint8ValueAsFloat64 = (uint8ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint8ValueAsFloat64 += ((uint8ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT8Value(static_cast<FIT_UINT8>(uint8ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT8Z:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint8zValueAsFloat64;
            ss << stringValue;
            ss >> uint8zValueAsFloat64;

            if (ss.fail())
            {
               SetUINT8ZValue(FIT_UINT8Z_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint8zValueAsFloat64 = (uint8zValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint8zValueAsFloat64 += ((uint8zValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT8ZValue(static_cast<FIT_UINT8Z>(uint8zValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_SINT16:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 sint16ValueAsFloat64;
            ss << stringValue;
            ss >> sint16ValueAsFloat64;

            if (ss.fail())
            {
               SetSINT16Value(FIT_SINT16_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               sint16ValueAsFloat64 = (sint16ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               sint16ValueAsFloat64 += ((sint16ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetSINT16Value(static_cast<FIT_SINT16>(sint16ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT16:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint16ValueAsFloat64;
            ss << stringValue;
            ss >> uint16ValueAsFloat64;

            if (ss.fail())
            {
               SetUINT16Value(FIT_UINT16_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint16ValueAsFloat64 = (uint16ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint16ValueAsFloat64 += ((uint16ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT16Value(static_cast<FIT_UINT16>(uint16ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT16Z:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint16zValueAsFloat64;
            ss << stringValue;
            ss >> uint16zValueAsFloat64;

            if (ss.fail())
            {
               SetUINT16ZValue(FIT_UINT16Z_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint16zValueAsFloat64 = (uint16zValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint16zValueAsFloat64 += ((uint16zValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT16ZValue(static_cast<FIT_UINT16Z>(uint16zValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_SINT32:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 sint32ValueAsFloat64;
            ss << stringValue;
            ss >> sint32ValueAsFloat64;

            if (ss.fail())
            {
               SetSINT32Value(FIT_SINT32_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               sint32ValueAsFloat64 = (sint32ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               sint32ValueAsFloat64 += ((sint32ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetSINT32Value(static_cast<FIT_SINT32>(sint32ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT32:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint32ValueAsFloat64;
            ss << stringValue;
            ss >> uint32ValueAsFloat64;

            if (ss.fail())
            {
               SetUINT32Value(FIT_UINT32_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint32ValueAsFloat64 = (uint32ValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint32ValueAsFloat64 += ((uint32ValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT32Value(static_cast<FIT_UINT32>(uint32ValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_UINT32Z:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 uint32zValueAsFloat64;
            ss << stringValue;
            ss >> uint32zValueAsFloat64;

            if (ss.fail())
            {
               SetUINT32ZValue(FIT_UINT32Z_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               uint32zValueAsFloat64 = (uint32zValueAsFloat64 + GetOffset(subFieldIndex)) * GetScale(subFieldIndex);
               uint32zValueAsFloat64 += ((uint32zValueAsFloat64 >= 0.0) ? (0.5) : (-0.5));
               SetUINT32ZValue(static_cast<FIT_UINT32Z>(uint32zValueAsFloat64), fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      case FIT_BASE_TYPE_FLOAT32:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT32 float32Value;
            ss << stringValue;
            ss >> float32Value;

            if (ss.fail())
            {
               SetFLOAT32Value(FIT_FLOAT32_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               SetFLOAT32Value(float32Value, fieldArrayIndex, subFieldIndex);
            }
            break;
         }
         break;

      case FIT_BASE_TYPE_FLOAT64:
         {
            Unicode::UTF8_SSTREAM ss;
            FIT_FLOAT64 float64Value;
            ss << stringValue;
            ss >> float64Value;

            if (ss.fail())
            {
               SetFLOAT64Value(FIT_FLOAT64_INVALID, fieldArrayIndex, subFieldIndex);
            }
            else
            {
               SetFLOAT64Value(float64Value, fieldArrayIndex, subFieldIndex);
            }
            break;
         }

      default:
         break;
   }
}

FIT_BOOL Field::Read(const void *data, const FIT_UINT8 size)
{
   int bytesLeft = size;
   FIT_UINT8 typeSize = baseTypeSizes[profile->fields[profileIndex].type & FIT_BASE_TYPE_NUM_MASK];
   FIT_BYTE *byteData = (FIT_BYTE *) data;

   values.clear();
   
   switch (profile->fields[profileIndex].type)
   {
      case FIT_BASE_TYPE_STRING:
      {
         std::vector<FIT_BYTE> value;
         int emptyStrings = 0;

         while (bytesLeft-- > 0)
         {
            FIT_BYTE byte = *byteData++;

            if (byte == 0)
            {
               if (value.size() > 0)
               {
                  while (emptyStrings > 0)
                  {
                     values.push_back(std::vector<FIT_BYTE>(1, (FIT_BYTE)0));   // Add empty (null-terminated) string.
                     emptyStrings--;
                  }

                  value.push_back(0);  // Null-terminate.
                  values.push_back(value);
               }
               else
               {
                  emptyStrings++;
               }

               value.clear();
            }
            else
            {
               value.push_back(byte);
            }
         }

         if (value.size() > 0)
         {
            while (emptyStrings > 0)
            {
               values.push_back(std::vector<FIT_BYTE>(1, (FIT_BYTE)0));   // Add empty (null-terminated) string.
               emptyStrings--;
            }

            value.push_back(0);  // Null-terminate.
            values.push_back(value);
         }
      }
      break;

      default:
      {
         FIT_BOOL invalid = FIT_TRUE;

         while (bytesLeft > 0)
         {
            std::vector<FIT_BYTE> value;

            if (memcmp(byteData, baseTypeInvalids[profile->fields[profileIndex].type & FIT_BASE_TYPE_NUM_MASK], typeSize) != 0)
               invalid = FIT_FALSE;

            for (int i = 0; i < typeSize; i++)
               value.push_back(*byteData++);

            values.push_back(value);

            bytesLeft -= typeSize;
         }

         if (invalid)
            values.clear();
      }
      break;
   }

   return FIT_TRUE;
}

FIT_UINT8 Field::Write(std::ostream &file) const
{
   for (FIT_UINT8 valueIndex = 0; valueIndex < values.size(); valueIndex++)
   {
      for (FIT_UINT8 valueOffset = 0; valueOffset < values[valueIndex].size(); valueOffset++)
         file.put(values[valueIndex][valueOffset]);
   }

   return GetSize();
}

} // namespace fit