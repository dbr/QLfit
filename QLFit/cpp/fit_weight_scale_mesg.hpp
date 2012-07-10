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


#if !defined(FIT_WEIGHT_SCALE_MESG_HPP)
#define FIT_WEIGHT_SCALE_MESG_HPP

#include "fit_mesg.hpp"

namespace fit
{

class WeightScaleMesg : public Mesg
{
   public:
      WeightScaleMesg(void) : Mesg(Profile::MESG_WEIGHT_SCALE)
      {
      }

      WeightScaleMesg(const Mesg &mesg) : Mesg(mesg)
      {
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns timestamp field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      FIT_DATE_TIME GetTimestamp(void) const
      {
         return GetFieldUINT32Value(253, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set timestamp field
      // Units: s
      ///////////////////////////////////////////////////////////////////////
      void SetTimestamp(FIT_DATE_TIME timestamp)
      {
         SetFieldUINT32Value(253, timestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns weight field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetWeight(void) const
      {
         return GetFieldFLOAT32Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set weight field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      void SetWeight(FIT_FLOAT32 weight)
      {
         SetFieldFLOAT32Value(0, weight, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns percent_fat field
      // Units: %
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetPercentFat(void) const
      {
         return GetFieldFLOAT32Value(1, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set percent_fat field
      // Units: %
      ///////////////////////////////////////////////////////////////////////
      void SetPercentFat(FIT_FLOAT32 percentFat)
      {
         SetFieldFLOAT32Value(1, percentFat, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns percent_hydration field
      // Units: %
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetPercentHydration(void) const
      {
         return GetFieldFLOAT32Value(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set percent_hydration field
      // Units: %
      ///////////////////////////////////////////////////////////////////////
      void SetPercentHydration(FIT_FLOAT32 percentHydration)
      {
         SetFieldFLOAT32Value(2, percentHydration, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns visceral_fat_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetVisceralFatMass(void) const
      {
         return GetFieldFLOAT32Value(3, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set visceral_fat_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      void SetVisceralFatMass(FIT_FLOAT32 visceralFatMass)
      {
         SetFieldFLOAT32Value(3, visceralFatMass, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns bone_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetBoneMass(void) const
      {
         return GetFieldFLOAT32Value(4, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set bone_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      void SetBoneMass(FIT_FLOAT32 boneMass)
      {
         SetFieldFLOAT32Value(4, boneMass, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns muscle_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetMuscleMass(void) const
      {
         return GetFieldFLOAT32Value(5, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set muscle_mass field
      // Units: kg
      ///////////////////////////////////////////////////////////////////////
      void SetMuscleMass(FIT_FLOAT32 muscleMass)
      {
         SetFieldFLOAT32Value(5, muscleMass, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns basal_met field
      // Units: kcal/day
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetBasalMet(void) const
      {
         return GetFieldFLOAT32Value(7, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set basal_met field
      // Units: kcal/day
      ///////////////////////////////////////////////////////////////////////
      void SetBasalMet(FIT_FLOAT32 basalMet)
      {
         SetFieldFLOAT32Value(7, basalMet, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns physique_rating field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetPhysiqueRating(void) const
      {
         return GetFieldUINT8Value(8, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set physique_rating field
      ///////////////////////////////////////////////////////////////////////
      void SetPhysiqueRating(FIT_UINT8 physiqueRating)
      {
         SetFieldUINT8Value(8, physiqueRating, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns active_met field
      // Units: kcal/day
      // Comment: ~4kJ per kcal, 0.25 allows max 16384 kcal
      ///////////////////////////////////////////////////////////////////////
      FIT_FLOAT32 GetActiveMet(void) const
      {
         return GetFieldFLOAT32Value(9, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set active_met field
      // Units: kcal/day
      // Comment: ~4kJ per kcal, 0.25 allows max 16384 kcal
      ///////////////////////////////////////////////////////////////////////
      void SetActiveMet(FIT_FLOAT32 activeMet)
      {
         SetFieldFLOAT32Value(9, activeMet, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns metabolic_age field
      // Units: years
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetMetabolicAge(void) const
      {
         return GetFieldUINT8Value(10, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set metabolic_age field
      // Units: years
      ///////////////////////////////////////////////////////////////////////
      void SetMetabolicAge(FIT_UINT8 metabolicAge)
      {
         SetFieldUINT8Value(10, metabolicAge, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns visceral_fat_rating field
      ///////////////////////////////////////////////////////////////////////
      FIT_UINT8 GetVisceralFatRating(void) const
      {
         return GetFieldUINT8Value(11, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set visceral_fat_rating field
      ///////////////////////////////////////////////////////////////////////
      void SetVisceralFatRating(FIT_UINT8 visceralFatRating)
      {
         SetFieldUINT8Value(11, visceralFatRating, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Returns user_profile_index field
      // Comment: Associates this weight scale message to a user.  This corresponds to the index of the user profile message in the weight scale file.
      ///////////////////////////////////////////////////////////////////////
      FIT_MESSAGE_INDEX GetUserProfileIndex(void) const
      {
         return GetFieldUINT16Value(12, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

      ///////////////////////////////////////////////////////////////////////
      // Set user_profile_index field
      // Comment: Associates this weight scale message to a user.  This corresponds to the index of the user profile message in the weight scale file.
      ///////////////////////////////////////////////////////////////////////
      void SetUserProfileIndex(FIT_MESSAGE_INDEX userProfileIndex)
      {
         SetFieldUINT16Value(12, userProfileIndex, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
      }

};

} // namespace fit

#endif // !defined(FIT_WEIGHT_SCALE_MESG_HPP)
