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

#include "csv_writer.hpp"

CSVWriter::CSVWriter(std::string fileName)
: fileName(fileName)
{
}

void CSVWriter::Open(void) 
{
   std::string tmpFileName = fileName;
   tmpFileName += ".tmp";
   
   if (file.is_open())
      Close();

   file.open(tmpFileName.c_str(), std::ios::out);
}

void CSVWriter::Close(void) 
{
   std::string tmpFileName = fileName;
   std::fstream tmpFile;
   
   tmpFileName += ".tmp";

   if (!file.is_open())
      return;
   
   file.close();
   file.open(fileName.c_str(), std::ios::out);
   
   // Write header line.
   for (int i = 0; i < (int)headers.size(); i++)
   {
      file.write(headers[i].c_str(), (int)headers[i].size());
      file.write(",", 1);
   }
   file.write("\n", 1);

   // Append temporary file.
   tmpFile.open(tmpFileName.c_str(), std::ios::in);
   while (1)
   {
      std::fstream::int_type ch = tmpFile.get();

      if (!tmpFile.good())
         break;

      file.put(ch);
   }

   tmpFile.close();
   file.close();
   remove(tmpFileName.c_str());
}

void CSVWriter::Clear(void) 
{
   for (int i = 0; i < (int)values.size(); i++)
      values[i] = "";
}

void CSVWriter::SetString(std::string header, std::string value)
{
   if (header.compare("") == 0)
      header = "null";
   
   for (int i = 0; i < (int)headers.size(); i++)
   {
      if (headers[i].compare(header) == 0)
      {
         values[i] = value;
         return;
      }
   }

   headers.push_back(header);
   values.push_back(value);
}

void CSVWriter::SetDouble(std::string header, double value, unsigned precision) 
{
   std::ostringstream valueStream;
   valueStream.setf(std::ios_base::fixed | std::ios_base::showpoint);
   valueStream.precision(precision);
   valueStream << value;
   this->SetString(header, valueStream.str());
}

void CSVWriter::SetInt(std::string header, long int value) 
{
   std::ostringstream valueStream;
   valueStream.setf(std::ios_base::fixed);
   valueStream << value;
   this->SetString(header, valueStream.str());
}

void CSVWriter::Writeln(void) 
{
   if (!file.is_open())
      Open();

   for (int i = 0; i < (int)values.size(); i++)
   {
      file.write(values[i].c_str(), (int)values[i].size());
      file.write(",", 1);
   }

   file.write("\n", 1);
}
