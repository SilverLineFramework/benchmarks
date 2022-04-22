// 15-745 S16 Assignment 1: FunctionWeight.cpp
// Group: Arjun Ramesh (arjunr2) and Nishanth Subramanian (nsubram2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/ValueMap.h"

#include "Dataflow.h"
#include "support.h"
#include <iostream>

using namespace llvm;

namespace {
  std::map<Function*, uint32_t> fn_straight_line_weight;
  std::map<Function*, bool> processed_fns;
  LoopInfo* LI;


  uint32_t getInstructionWeight(Instruction* I) {
    uint32_t weight = 0;
    unsigned opcode = I->getOpcode();
    Type* type = I->getType();
    switch(opcode) {
      /* Integer Arithmetic */
      case Instruction::Add:
      case Instruction::Sub: weight = 1; break;

      case Instruction::Mul: weight = 4; break;

      case Instruction::UDiv:
      case Instruction::SDiv:
      case Instruction::URem:
      case Instruction::SRem: weight = 25; break;

      /* FP Arithmetic */
      case Instruction::FAdd:
      case Instruction::FSub: weight = 3; break;

      case Instruction::FMul: weight = 4; break;

      case Instruction::FDiv:
      case Instruction::FRem: weight = 25; break; 

      /* Logical Arithmetic */
      case Instruction::Shl:
      case Instruction::LShr:
      case Instruction::AShr: weight = 1; break;

      case Instruction::And:
      case Instruction::Or:
      case Instruction::Xor: weight = 1; break;

      /* Memory Operators */
      //case Alloca:
      case Instruction::Load:
      case Instruction::Store: weight = 3; break;

      case Instruction::AtomicRMW:
      case Instruction::AtomicCmpXchg: weight = 7; break;

      //case Fence
      case Instruction::GetElementPtr: weight = 2; break;


      /* Control-flow operations */
      case Instruction::Ret:
      case Instruction::Br:
      case Instruction::IndirectBr:
      case Instruction::CallBr:
      case Instruction::Invoke: weight = 2; break;


      /* Others */
      case Instruction::ICmp:
      case Instruction::FCmp: weight = 1; break;
      case Instruction::Call: {
        if (CallInst *CI = dyn_cast<CallInst>(I)) {
          Function* fun = CI->getCalledFunction();
          // External function: Const val
          if (fun->isDeclaration()) {
            weight = 10000;
          } else {
            // Direct call: Lookup map
            if (fun) {
              weight = fn_straight_line_weight[fun];
            }
            // Indirect call: Const val
            else {
              weight = 10000;
            }
          }
        }
        break;
      }

      default: weight = 0;
    }

    return weight;
  }




  class FunctionWeight : public FunctionPass {
  public:
    static char ID;
    FunctionWeight() : FunctionPass(ID) { }
    ~FunctionWeight() { }


    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      AU.addRequiredTransitive<LoopInfoWrapperPass>();
    }


    static uint32_t transfer_fn(Value *V, uint32_t in)
    {
      BasicBlock *B = dyn_cast<BasicBlock>(V);
      // Ignore blocks in Loop (null for blocks_)
      if (LI->getLoopFor(B)) {
        //outs() << "Gets in here!: " << *B << "\n";
        return in;
      }
      // Compute straight-line weight
      else {
        uint32_t weight = 0;
        for (auto &I : *B) {
          // Weight instructions appropriately...
          weight += getInstructionWeight(&I);
        }
        return in + weight;
      }
    }

    // Here, Meet is Union operator (OR)
    static uint32_t meet(std::vector<uint32_t> ins)
    {
      uint32_t max = *std::max_element(ins.begin(), ins.end());
      return max;
    }

    // Do some initialization
    bool doInitialization(Module &M) override {
      errs() << "15745 Function Information Pass (straight line code)\n\n"; 
      return false;
    }

    bool doFinalization(Module &M) override {
      errs() << "End of Function Pass\n";
      for (auto const& it : fn_straight_line_weight) {
        outs() << "Found fn: " << it.first->getName() << "  Weight: " << it.second << "\n";
      }
      return false;
    }

    // Print output for each function
    bool runOnFunction(Function &F) override {
      // outs() << "name" << ",\t" << "args" << ",\t" << "calls" << ",\t" << "bbs" << ",\t" << "insts" << "\n";
      DataflowAnalysis<uint32_t> problem;
      LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
      if (!F.isDeclaration()) {
        fn_straight_line_weight[&F] = 0;

        // Run dataflow
        uint32_t top = 0;
        uint32_t entry = 0;
        problem.set(&transfer_fn, &meet, entry, top);
        problem.run_iterations(F, FORWARDS, BASIC_BLOCKS);

        std::vector<uint32_t> exit_blocks_weight;
        for (auto &BB : F) {
          Instruction* I = BB.getTerminator();
          if (ReturnInst *RI = dyn_cast<ReturnInst>(I)) {
            uint32_t bw = problem.get_outs(&BB, BASIC_BLOCKS);
            exit_blocks_weight.push_back(bw);
          }
        }

        uint32_t out_weight = *std::max_element(exit_blocks_weight.begin(), exit_blocks_weight.end());
        fn_straight_line_weight[&F] = out_weight;

      } 
      // Declaration (external-function): set some constant weight
      else {
        outs() << "Declaration of " << F.getName() << "\n";
      }

      return false;
    }
  };
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionWeight::ID = 0;
static RegisterPass<FunctionWeight> function_weight("function-weight", "15745: Function Weight Information(excluding loops)", false, false);
