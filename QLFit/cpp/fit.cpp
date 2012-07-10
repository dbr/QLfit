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


#include "fit.hpp"

///////////////////////////////////////////////////////////////////////
// Private Definitions
///////////////////////////////////////////////////////////////////////

namespace fit
{

///////////////////////////////////////////////////////////////////////
// Public Constants
///////////////////////////////////////////////////////////////////////

const FIT_UINT8 baseTypeSizes[FIT_BASE_TYPES] =
{
   sizeof(FIT_ENUM),
   sizeof(FIT_SINT8),
   sizeof(FIT_UINT8),
   sizeof(FIT_SINT16),
   sizeof(FIT_UINT16),
   sizeof(FIT_SINT32),
   sizeof(FIT_UINT32),
   sizeof(FIT_STRING),
   sizeof(FIT_FLOAT32),
   sizeof(FIT_FLOAT64),
   sizeof(FIT_UINT8Z),
   sizeof(FIT_UINT16Z),
   sizeof(FIT_UINT32Z),
   sizeof(FIT_BYTE),
};

const FIT_ENUM enumInvalid = FIT_ENUM_INVALID;
const FIT_SINT8 sint8Invalid = FIT_SINT8_INVALID;
const FIT_UINT8 uint8Invalid = FIT_UINT8_INVALID;
const FIT_SINT16 sint16Invalid = FIT_SINT16_INVALID;
const FIT_UINT16 uint16Invalid = FIT_UINT16_INVALID;
const FIT_SINT32 sint32Invalid = FIT_SINT32_INVALID;
const FIT_UINT32 uint32Invalid = FIT_UINT32_INVALID;
const FIT_STRING stringInvalid = FIT_STRING_INVALID;
const FIT_FLOAT32 float32Invalid = FIT_FLOAT32_INVALID;
const FIT_FLOAT64 float64Invalid = FIT_FLOAT64_INVALID;
const FIT_UINT8Z uint8zInvalid = FIT_UINT8Z_INVALID;
const FIT_UINT16Z uint16zInvalid = FIT_UINT16Z_INVALID;
const FIT_UINT32Z uint32zInvalid = FIT_UINT32Z_INVALID;
const FIT_BYTE byteInvalid = FIT_BYTE_INVALID;

const FIT_UINT8 *baseTypeInvalids[FIT_BASE_TYPES] =
{
   (FIT_UINT8 *)&enumInvalid,
   (FIT_UINT8 *)&sint8Invalid,
   (FIT_UINT8 *)&uint8Invalid,
   (FIT_UINT8 *)&sint16Invalid,
   (FIT_UINT8 *)&uint16Invalid,
   (FIT_UINT8 *)&sint32Invalid,
   (FIT_UINT8 *)&uint32Invalid,
   (FIT_UINT8 *)&stringInvalid,
   (FIT_UINT8 *)&float32Invalid,
   (FIT_UINT8 *)&float64Invalid,
   (FIT_UINT8 *)&uint8zInvalid,
   (FIT_UINT8 *)&uint16zInvalid,
   (FIT_UINT8 *)&uint32zInvalid,
   (FIT_UINT8 *)&byteInvalid,
};


///////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////

FIT_UINT8 GetArch(void)
{
   const FIT_UINT16 arch = 0x0100;
   return (*(FIT_UINT8 *)&arch);
}

} // namespace fit

