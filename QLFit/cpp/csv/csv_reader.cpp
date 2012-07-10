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

#include <cstdlib>
#include <fstream>
#include "csv_reader.hpp"
#include "fit_field.hpp"
#include "fit_field_definition.hpp"
#include "fit_mesg.hpp"
#include "fit_mesg_definition.hpp"
#include "fit_unicode.hpp"

FIT_BOOL CSVReader::Read(std::fstream& in, MesgListener& mesgListener)
{
   return Read(in, &mesgListener, FIT_NULL);
}

FIT_BOOL CSVReader::Read(std::fstream& in, MesgListener& mesgListener, MesgDefinitionListener& mesgDefinitionListener)
{
   return Read(in, &mesgListener, &mesgDefinitionListener);
}

FIT_BOOL CSVReader::Read(std::fstream& in, MesgListener* mesgListener, MesgDefinitionListener* mesgDefinitionListener)
{
   std::vector<std::string> cells;
   int typeCol = -1;
   int localNumCol = -1;
   int mesgCol = -1;
   int fieldCol = -1;
   int lineNum = 1;

   ReadRow(cells, in); // Get columns in header.

   for (int col = 0; col < (int)cells.size(); col++)
   {
      if (cells[col].compare("Type") == 0) {
         typeCol = col;
      }
      else if (cells[col].compare("Local Number") == 0) {
         localNumCol = col;
      }
      else if (cells[col].compare("Message") == 0) {
         mesgCol = col;
      }
      else if (cells[col].compare("Field 1") == 0) {
         fieldCol = col;
         break;
      }
   }

   if (mesgCol < 0)
   {
      printf("CSVReader.read(): Error on line %d - Missing \"Message\" column.\n", lineNum);
      return FIT_FALSE;
   }

   while (!in.eof())
   {
      Mesg mesg;
      MesgDefinition mesgDef;
      FIT_BOOL isMesgDef;

      ReadRow(cells, in);
      lineNum++;

      if (((typeCol >= 0) && ((int)cells.size() <= typeCol)) || ((localNumCol >= 0) && ((int)cells.size() <= localNumCol)) || ((int)cells.size() <= mesgCol) || (cells[mesgCol].compare("") == 0))
         continue;   // Ignore empty lines

      mesg = Mesg(cells[mesgCol]);

      if (localNumCol >= 0)
         mesg.SetLocalNum((FIT_UINT8)atoi(cells[localNumCol].c_str()));

      if ((typeCol >= 0) && (cells[typeCol].compare("Definition") == 0)) {
         mesgDef = MesgDefinition(mesg);
         isMesgDef = FIT_TRUE;
      }
      else {
         isMesgDef = FIT_FALSE;
      }

      if (mesg.GetNum() == FIT_MESG_NUM_INVALID) {
         printf("CSVReader.read(): Error on line %d - Unknown message \"%s\".\n", lineNum, cells[mesgCol].c_str());
         return FIT_FALSE;
      }

      if (fieldCol >= 0)
      {
         int cellIndex = fieldCol;

         while ((cellIndex + 2) <= (int)cells.size()) {
            std::string fieldOrSubFieldName = cells[cellIndex++];
            Field field(mesg.GetName(), fieldOrSubFieldName);
            FieldDefinition fieldDef;
            std::vector<std::string> values;

            ReadValues(values, cells[cellIndex++]);
            cellIndex++; // ignore units

            if (fieldOrSubFieldName == "")
               break; // Blank cell.

            if (field.GetNum() == FIT_FIELD_NUM_INVALID) {
               printf("CSVReader.read(): Error on line %d - Unknown field \"%s\" in message \"%s\".\n", lineNum, fieldOrSubFieldName.c_str(), mesg.GetName().c_str());
               return FIT_FALSE;
            }

            if (values.size() == 0)
               break;

            if (isMesgDef)
               fieldDef = FieldDefinition(field);

            for (int i = 0; i < (int)values.size(); i++) {
               field.SetSTRINGValue(Unicode::Encode_UTF8ToBase(Unicode::Copy_StdToUTF8(values[i])), i, Profile::GetSubFieldIndex(mesg.GetName(), field.GetName(FIT_SUBFIELD_INDEX_MAIN_FIELD), fieldOrSubFieldName));

               if (isMesgDef)
                  fieldDef.SetSize((FIT_UINT8)atoi(values[i].c_str()) * baseTypeSizes[fieldDef.GetType() & FIT_BASE_TYPE_NUM_MASK]);
            }

            mesg.AddField(field);

            if (isMesgDef)
               mesgDef.AddField(fieldDef);
         }
      }

      if (isMesgDef) {
         if (mesgDefinitionListener)
            mesgDefinitionListener->OnMesgDefinition(mesgDef);
      }
      else {
         if (mesgListener)
            mesgListener->OnMesg(mesg);
      }
   }

   return FIT_TRUE;
}

void CSVReader::ReadRow(std::vector<std::string>& cells, std::fstream& in)
{
   std::string cell = "";
   bool inQuotes = false;
   char c;

   cells.clear();

   while ((c = in.get()) != EOF)
   {
      switch (c)
      {
         case '\r':
            break;
         
         case '\n':
            cells.push_back(cell);
            return;

         case '"':
            inQuotes = !inQuotes;
            break;

         case ',':
            if (inQuotes)
            {
               cell += c;
            }
            else
            {
               cells.push_back(cell);
               cell = "";
            }
            break;

         default:
            cell += c;
            break;
      }
   }

   cells.push_back(cell);
}

void CSVReader::ReadValues(std::vector<std::string>& values, const std::string& cell)
{
   std::string value = "";
   int i = 0;

   values.clear();

   while (i < (int)cell.length())
   {
      if (cell[i] == '|')
      {
         values.push_back(value);
         value = "";
      }
      else
      {
         value += cell[i];
      }
      
      i++;
   }

   if (value.length() > 0)
      values.push_back(value);
}
