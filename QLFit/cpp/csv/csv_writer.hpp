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

#if !defined(CSV_WRITER_HPP)
#define CSV_WRITER_HPP

#include <fstream>
#include <string>
#include <vector>

class CSVWriter
{
   public:
      CSVWriter(std::string fileName);
      void Open(void);
      void Close(void);
      void Clear();
      void SetString(std::string header, std::string value);
      void SetDouble(std::string header, double value, unsigned precision = 9);
      void SetInt(std::string header, long int value);
      void Writeln(void);

   private:
      std::string fileName;
      std::fstream file;
      std::vector<std::string> headers;
      std::vector<std::string> values;
};

#endif // !defined(CSV_WRITER_HPP)

