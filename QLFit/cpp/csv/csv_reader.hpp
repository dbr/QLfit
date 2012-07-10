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

#if !defined(CSV_READER_HPP)
#define CSV_READER_HPP

#include <iosfwd>
#include <string>
#include <vector>
#include "fit_mesg_definition_listener.hpp"
#include "fit_mesg_listener.hpp"

using namespace fit;

class CSVReader
{
   public:
      static FIT_BOOL Read(std::fstream& in, MesgListener& mesgListener);
      static FIT_BOOL Read(std::fstream& in, MesgListener& mesgListener, MesgDefinitionListener& mesgDefinitionListener);
   private:
      static FIT_BOOL Read(std::fstream &in, MesgListener* mesgListener, MesgDefinitionListener* mesgDefinitionListener);
      static void ReadRow(std::vector<std::string>& cells, std::fstream& in);
      static void ReadValues(std::vector<std::string>& values, const std::string& cell);
};

#endif // !defined(CSV_READER_HPP)

