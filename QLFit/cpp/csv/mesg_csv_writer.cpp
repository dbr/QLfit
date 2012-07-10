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

#include <sstream>
#include "fit.hpp"
#include "fit_field_definition.hpp"
#include "fit_unicode.hpp"
#include "mesg_csv_writer.hpp"

using namespace fit;

MesgCSVWriter::MesgCSVWriter(std::string fileName)
: csv(fileName)
{
}

void MesgCSVWriter::Close(void)
{
   csv.Close();
}

void MesgCSVWriter::OnMesg(Mesg& mesg)
{
   csv.Clear();
   csv.SetString("Type", "Data");
   csv.SetInt("Local Number", mesg.GetLocalNum());
   csv.SetString("Message", mesg.GetName());
   for (int i = 0; i < mesg.GetNumFields(); i++)
   {
      Field* field = mesg.GetFieldByIndex(i);
      int subFieldIndex = mesg.GetActiveSubFieldIndex(field->GetNum());
      std::ostringstream headerNum;

      headerNum << i + 1;
      csv.SetString("Field " + headerNum.str(), field->GetName(subFieldIndex));

      std::string value = Unicode::Copy_UTF8ToStd(Unicode::Encode_BaseToUTF8(field->GetSTRINGValue(0, subFieldIndex)));

      for (int fieldElement = 1; fieldElement < field->GetNumValues(); fieldElement++)
         value += "|" + Unicode::Copy_UTF8ToStd(Unicode::Encode_BaseToUTF8(field->GetSTRINGValue(fieldElement, subFieldIndex)));

      csv.SetString("Value " + headerNum.str(), value);
      csv.SetString("Units " + headerNum.str(), field->GetUnits(subFieldIndex));
   }

   csv.Writeln();
}

void MesgCSVWriter::OnMesgDefinition(MesgDefinition& mesgDef)
{
   Mesg mesg(mesgDef.GetNum());

   csv.Clear();
   csv.SetString("Type", "Definition");
   csv.SetInt("Local Number", mesgDef.GetLocalNum());
   csv.SetString("Message", mesg.GetName());

   for (int i = 0; i < mesgDef.GetNumFields(); i++)
   {
      FieldDefinition* fieldDef = mesgDef.GetFieldByIndex(i);
      Field field(mesgDef.GetNum(), fieldDef->GetNum());
      std::ostringstream headerNum;

      headerNum << i + 1;
      csv.SetString("Field " + headerNum.str(), field.GetName(FIT_SUBFIELD_INDEX_MAIN_FIELD));
      csv.SetInt("Value " + headerNum.str(), fieldDef->GetSize() / baseTypeSizes[(fieldDef->GetType() & FIT_BASE_TYPE_NUM_MASK)]);
      csv.SetString("Units " + headerNum.str(), "");
   }

   csv.Writeln();
}
