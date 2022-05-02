// 15-745 Assignment 2: available.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"

#include "Dataflow.h"
#include "Global.h"
#include "support.h"

using namespace llvm;
using namespace std;

namespace
{

  std::vector<Value *> universal_insns;
  std::map<BasicBlock*, bool> processed_blocks;

  class Checkpoint : public LoopPass
  {
    Loop* current_loop;
    unsigned current_loop_depth;
    Module* current_module;

  public:

    static char ID;
    Checkpoint() : LoopPass(ID) {}

    DataflowAnalysis<BitVector> problem;
    
    static BitVector transfer_fn(Value *V, BitVector in)
    {
      return in;
    }

    // Here, Meet is Union operator (OR)
    static BitVector meet(std::vector<BitVector> ins)
    {
      BitVector res = ins.front();
      for (auto &vec : ins)
      {
        res |= vec;
      }
      return res;
    }


    virtual bool doInitialization(Loop* L, LPPassManager &LPM) {
      //outs() << "-------------------\n";
      //outs() << getPassName().str() << " : " << L << "\n";
      //outs() << "-------------------\n";

      current_loop = L;
      current_loop_depth = L->getLoopDepth();
      current_module = L->getHeader()->getModule();

      universal_insns.clear();

      for (auto &BB : L->blocks()) {
        // If block has not been processed, add
        if (processed_blocks.find(BB) == processed_blocks.end()) {
          processed_blocks[BB] = true;
          for (auto &I : *BB) {
            universal_insns.push_back(&I);
          }
        }
      }


      return false;
    }

    virtual bool runOnLoop(Loop* L, LPPassManager &LPM)
    {
      Type* int64_type = Type::getInt64Ty(current_module->getContext());
      GlobalVariable* global_cnt = 
          create_int_global(int64_type, "runtime_ctr", current_module);

      if (global_cnt == nullptr) {
        errs() << "Global already exists!\n";
      }
      Constant* one = ConstantInt::get(int64_type, 1);
      
      Instruction* Inst = L->getHeader()->getFirstNonPHI();
      IRBuilder<> Builder(Inst);
      LoadInst* li = Builder.CreateLoad(int64_type, global_cnt, true, ".prof.ld");
      Value* inc = Builder.CreateAdd(li, one, ".prof.add");
      StoreInst* si = Builder.CreateStore(inc, global_cnt);

      // Modifies the incoming Function.
      return true;
    }

    virtual bool doFinalization() {
      outs() << "Completed Pass!\n";
      outs() << "-------------------\n";
      return false;
    }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const
    {
      AU.setPreservesAll();
    }

    const DataflowAnalysis<BitVector> &getCheckpointResult() const { return problem; }
    DataflowAnalysis<BitVector> &getCheckpointResult() { return problem; }

  };

  char Checkpoint::ID = 0;
  RegisterPass<Checkpoint> checkpoint("checkpoint",
                                       "Loop Checkpointing Pass");
}
