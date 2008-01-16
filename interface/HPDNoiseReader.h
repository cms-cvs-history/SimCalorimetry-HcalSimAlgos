#ifndef HPDLibrary_HPDNoiseReader_h
#define HPDLibrary_HPDNoiseReader_h

// --------------------------------------------------------
// Engine to read HPD noise events from the library
// Project: HPD noise library
// Author: F.Ratnikov UMd, Jan. 15, 2008
// $Id: BasicJet.h,v 1.11 2007/09/20 21:04:43 fedor Exp $
// --------------------------------------------------------

#include <string>
#include <vector>

class TFile;
class TTree;
class HPDNoiseData;

class HPDNoiseReader {
 public:
  typedef int Handle;
  HPDNoiseReader (const std::string& fFileName);
  ~HPDNoiseReader ();

  /// all HPD instances in the library
  std::vector<std::string> allNames () const;
  /// get handle to access data for one HPD instance
  Handle getHandle (const std::string& fName);
  /// test if handle is valid
  bool valid (Handle fHandle) const {return fHandle >= 0;}
  /// noise rate for the instance
  float rate (Handle fHandle) const;
  /// total number of noise events for the HPD instance in the library
  unsigned long totalEntries (Handle fHandle) const;
  /// retrive one entry from the library
  void getEntry (Handle fHandle, unsigned long fEntry, HPDNoiseData** fData);
  
 private:
  HPDNoiseReader (const HPDNoiseReader&); // no copy
  HPDNoiseReader& operator=(const HPDNoiseReader&); // no copy
  void grabEntry (Handle fHandle, unsigned long fEntry);

  TFile* mFile;
  std::vector <TTree*> mTrees;
  std::vector <float> mRates;
  HPDNoiseData* mBuffer;
};

#endif
