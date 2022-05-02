// 15-745 Assignment 2: available.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"

using namespace llvm;

namespace
{

  class Null : public ModulePass
  {

  public:

    static char ID;
    Null() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
      // Does nothing
      outs() << "--- Null pass --- \n";
      return false;
    }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const
    {
      AU.setPreservesAll();
    }

  };

  char Null::ID = 0;
  RegisterPass<Null> null_obj("null", "Null Pass");
}
