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
class TLeaf;
class TTree;

namespace ROOT {
   // 0 for the general case, 1 when this a split clases inside a TClonesArray,
   // 2 when this is a split classes inside an STL container.
   enum ELocation { kOut=0, kClones, kSTL, kInsideClones, kInsideSTL };

   class TTreeReaderDescriptor : public TObject {
   public:
      enum ReaderType { kValue, kArray };
      ReaderType fType;
      TString fDataType;
      TString fName;
      TString fBranchName;
      
      TTreeReaderDescriptor(ReaderType type, TString dataType, TString name, TString branchName) : 
         fType(type),
         fDataType(dataType),
         fName(name),
         fBranchName(branchName) { }
   };

   class TBranchDescriptor : public TNamed {
   public:
      ELocation             fIsClones;
      TString               fContainerName;
      UInt_t                fSplitLevel;
      TString               fBranchName;
      TVirtualStreamerInfo *fInfo;

      TBranchDescriptor(const char *type, TVirtualStreamerInfo *info,
                             const char *branchname, ELocation isclones,
                             UInt_t splitlevel, const TString &containerName) :
         TNamed(type,type),
         fIsClones(isclones),
         fContainerName(containerName),
         fSplitLevel(splitlevel),
         fBranchName(branchname),
         fInfo(info) { }
   };

   class TTreeSelectorReaderGenerator
   {
      TTree   *fTree;          // Pointer to the tree
      TString  fClassname;     // Class name of the selector
      UInt_t   fMaxUnrolling;  // Depth of unrolling for non-split classes
      TList    fListOfHeaders; // List of included headers
      TList    fListOfReaders; // List of readers
      
      void   AddHeader(TClass *cl);
      void   AddReader(TTreeReaderDescriptor::ReaderType type, TString dataType, TString name, TString branchName);
      UInt_t AnalyzeOldBranch(TBranch *branch, UInt_t level);
      UInt_t AnalyzeOldLeaf(TLeaf *leaf, Int_t nleaves);
      
      void   AnalyzeTree(TTree *tree);
      void   WriteSelector();
   
   public:
      TTreeSelectorReaderGenerator(TTree* tree, const char *classname, UInt_t maxUnrolling);
      
   };

}

using ROOT::TTreeSelectorReaderGenerator;

#endif
