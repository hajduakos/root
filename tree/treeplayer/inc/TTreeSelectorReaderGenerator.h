// @(#)root/treeplayer:$Id$
// Author: Akos Hajdu 22/06/2015

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers and al.        *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TTreeSelectorReaderGenerator
#define ROOT_TTreeSelectorReaderGenerator

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TTreeSelectorReaderGenerator                                         //
//                                                                      //
// Generate a Selector using TTreeReaderValues and TTreeReaderArrays to //
// access the data in the tree.                                         //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_Tlist
#include "TList.h"
#endif
#ifndef ROOT_TString
#include "TString.h"
#endif
#ifndef ROOT_TNamed
#include "TNamed.h"
#endif


class TBranch;
class TBranchElement;
class TLeaf;
class TTree;

namespace ROOT {
   // 0 for the general case, 1 when this a split clases inside a TClonesArray,
   // 2 when this is a split classes inside an STL container.
   enum ELocation { kOut=0, kClones, kSTL, kInsideClones, kInsideSTL };

   class TTreeReaderDescriptor : public TObject {
   public:
      enum ReaderType { kValue, kArray };
      ReaderType fType;    // Type of the reader: Value or Array
      TString fDataType;   // Data type of reader
      TString fName;       // Reader name
      TString fBranchName; // Branch corresponding to the reader
      
      TTreeReaderDescriptor(ReaderType type, TString dataType, TString name, TString branchName) : 
         fType(type),
         fDataType(dataType),
         fName(name),
         fBranchName(branchName) { }
   };

   class TBranchDescriptor : public TNamed {
   public:
      ELocation             fIsClones;       // Type of container
      TString               fContainerName;  // Name of the container
      TString               fBranchName;     // Short name of the branch
      TString               fFullBranchName; // Full name of the branch
      TVirtualStreamerInfo *fInfo;           // Streamer info

      TBranchDescriptor(const char *type, TVirtualStreamerInfo *info,
                        const char *branchname, ELocation isclones,
                        const TString &containerName, const char *prefix = 0) :
         TNamed(type,type),
         fIsClones(isclones),
         fContainerName(containerName),
         fBranchName(branchname),
         fFullBranchName(branchname),
         fInfo(info)
         {
            // If there is a prefix, append to the beginning
            if (prefix) {
               fFullBranchName.Form("%s_%s", prefix, branchname);
            }
         }

      Bool_t IsClones() const { return fIsClones==kClones || fIsClones==kInsideClones; }

      Bool_t IsSTL() const { return fIsClones==kSTL || fIsClones==kInsideSTL; }
   };

   class TTreeSelectorReaderGenerator
   {
      TTree   *fTree;          // Pointer to the tree
      TString  fClassname;     // Class name of the selector
      TList    fListOfHeaders; // List of included headers
      TList    fListOfReaders; // List of readers
      
      void   AddHeader(TClass *cl);
      void   AddReader(TTreeReaderDescriptor::ReaderType type, TString dataType, TString name, TString branchName);
      UInt_t AnalyzeBranches(TBranchDescriptor *desc, TBranchElement *branch, TVirtualStreamerInfo *info);
      UInt_t AnalyzeBranches(TBranchDescriptor *desc, TIter &branches, TVirtualStreamerInfo *info);
      UInt_t AnalyzeOldBranch(TBranch *branch);
      UInt_t AnalyzeOldLeaf(TLeaf *leaf, Int_t nleaves);
      
      void   AnalyzeTree(TTree *tree);
      void   WriteSelector();
   
   public:
      TTreeSelectorReaderGenerator(TTree* tree, const char *classname);
      
   };

}

using ROOT::TTreeSelectorReaderGenerator;

#endif
