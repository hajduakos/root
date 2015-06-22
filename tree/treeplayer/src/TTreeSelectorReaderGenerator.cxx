// @(#)root/treeplayer:$Id$
// Author: Akos Hajdu 22/06/2015

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers and al.        *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include "TTreeSelectorReaderGenerator.h"
#include <stdio.h>

#include "TTree.h"

namespace ROOT {

   TTreeSelectorReaderGenerator::TTreeSelectorReaderGenerator(TTree* tree,
                                            const char *classname, UInt_t maxUnrolling) : 
      fTree(tree),
      fClassname(classname),
      fMaxUnrolling(maxUnrolling)
   {
      // Constructor.
      AnalyzeTree(fTree);
      
      WriteSelector();
   }
   
   void TTreeSelectorReaderGenerator::AnalyzeTree(TTree *tree)
   {
      // Analyze tree
      TIter next(tree->GetListOfBranches());
      TBranch *branch;
      
      // Loop through branches
      while (branch = (TBranch*)next()) {
         const char *branchname = branch->GetName();
         const char *classname = branch->GetClassName();
         
         printf("Branch name: %s, class name: %s\n", branch->GetName(), branch->GetClassName());
         
      }
   }
   
   void TTreeSelectorReaderGenerator::WriteSelector()
   {
      // Generate code for selector class
   }
}
