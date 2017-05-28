#include "MutationOperators/AndOrReplacementMutationOperator.h"

#include "Context.h"
#include "Logger.h"
#include "MutationOperators/MutationOperatorFilter.h"
#include "MutationPoint.h"

#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/DebugInfoMetadata.h"

#include <fstream>
#include <iterator>

using namespace llvm;
using namespace mull;

const std::string AndOrReplacementMutationOperator::ID = "add_or_replacement_mutation_operator";

static int GetFunctionIndex(llvm::Function *function) {
  auto PM = function->getParent();

  auto FII = std::find_if(PM->begin(), PM->end(),
                          [function] (llvm::Function &f) {
                            return &f == function;
                          });

  assert(FII != PM->end() && "Expected function to be found in module");
  int FIndex = std::distance(PM->begin(), FII);

  return FIndex;
}

std::vector<MutationPoint *>
AndOrReplacementMutationOperator::getMutationPoints(const Context &context,
                                                    llvm::Function *function,
                                                    MutationOperatorFilter &filter) {
  int functionIndex = GetFunctionIndex(function);
  int basicBlockIndex = 0;

  std::vector<MutationPoint *> mutationPoints;

  for (auto &basicBlock : function->getBasicBlockList()) {
    int instructionIndex = 0;

    for (auto &instruction : basicBlock.getInstList()) {

      if (canBeApplied(instruction) && !filter.shouldSkipInstruction(&instruction)) {
        auto moduleID = instruction.getModule()->getModuleIdentifier();
        MullModule *module = context.moduleWithIdentifier(moduleID);

        MutationPointAddress address(functionIndex, basicBlockIndex, instructionIndex);
        auto mutationPoint = new MutationPoint(this, address, &instruction, module);
        mutationPoints.push_back(mutationPoint);
      }
      instructionIndex++;
    }
    basicBlockIndex++;
  }

  return mutationPoints;
}

bool AndOrReplacementMutationOperator::canBeApplied(Value &V) {
  BranchInst *branchInst = dyn_cast<BranchInst>(&V);

  if (branchInst == nullptr) {
    return false;
  }

  /// This filters out the cases when it is "phi" instruction that is before a
  /// branch instruction.
  if (dyn_cast<PHINode>(branchInst->getOperand(0))) {
    return false;
  }

  if (branchInst->isConditional() == false) {
    return false;
  }

  /// TODO: Discuss how to filter out irrelevant branch instructions.
  if (branchInst->hasMetadata()) {
    int debugInfoKindID = 0;

    MDNode *debug = branchInst->getMetadata(debugInfoKindID);
    DILocation *location = dyn_cast<DILocation>(debug);
    if (location) {
      if (location->getFilename().str().find("include/c++/v1") != std::string::npos) {
        return false;
      }
    }
  }

  AND_OR_MutationType possibleMutationType =
    findPossibleMutationInBranch(branchInst, nullptr);

  if (possibleMutationType != AND_OR_MutationType_None) {
    return true;
  }

  return false;
}

llvm::Value *AndOrReplacementMutationOperator::applyMutation(Module *M,
                                                             MutationPointAddress address,
                                                             Value &_V) {
  /// In the following V argument is not used. Eventually it will be removed from
  /// this method's signature because it will be not relevant
  /// when mutations will be applied on copies of original module
  llvm::Function &F = *(std::next(M->begin(), address.getFnIndex()));
  llvm::BasicBlock &B = *(std::next(F.begin(), address.getBBIndex()));
  llvm::Instruction &I = *(std::next(B.begin(), address.getIIndex()));

  BranchInst *branchInst = dyn_cast<BranchInst>(&I);
  assert(branchInst != nullptr);
  assert(branchInst->isConditional());

  BranchInst *secondBranch = nullptr;
  AND_OR_MutationType possibleMutationType =
    findPossibleMutationInBranch(branchInst,
                                 &secondBranch);

  if (possibleMutationType == AND_OR_MutationType_AND_to_OR) {
    return applyMutationANDToOR(M, branchInst, secondBranch);
  }

  if (possibleMutationType == AND_OR_MutationType_OR_to_AND) {
    return applyMutationORToAND(M, branchInst, secondBranch);
  }

  return nullptr;
}

#pragma mark - Private: Apply mutations: AND -> OR and OR -> AND

llvm::Value *
AndOrReplacementMutationOperator::applyMutationANDToOR(Module *M,
                                                       BranchInst *firstBranch,
                                                       BranchInst *secondBranch) {
  assert(firstBranch != nullptr);
  assert(firstBranch->isConditional());

  assert(secondBranch != nullptr);
  assert(secondBranch->isConditional());

  /// Operand #0 is a comparison instruction.
  Instruction *sourceInst = (dyn_cast<Instruction>(firstBranch->getOperand(0)));
  assert(sourceInst);

  /// Left branch value is somehow operand #2, right is #1.
  BasicBlock *firstBranchLeftBB  = dyn_cast<BasicBlock>(firstBranch->getOperand(2));
  BasicBlock *firstBranchRightBB = dyn_cast<BasicBlock>(firstBranch->getOperand(1));
  assert(firstBranchLeftBB);
  assert(firstBranchRightBB);

  BasicBlock *secondBranchLeftBB = dyn_cast<BasicBlock>(secondBranch->getOperand(2));

  BranchInst *replacement = BranchInst::Create(secondBranchLeftBB,
                                               firstBranchLeftBB,
                                               sourceInst);

  /// If I add a named instruction, and the name already exist
  /// in a basic block, then LLVM will make another unique name of it
  /// To prevent this name change we need to 'drop' the existing old name
  firstBranch->setName("");

  replacement->insertAfter(firstBranch);
  firstBranch->replaceAllUsesWith(replacement);
  firstBranch->eraseFromParent();
  assert(firstBranch->getParent() == nullptr);
  
  return replacement;
}

llvm::Value *
AndOrReplacementMutationOperator::applyMutationORToAND(Module *M,
                                                       BranchInst *firstBranch,
                                                       BranchInst *secondBranch) {

  assert(firstBranch != nullptr);
  assert(firstBranch->isConditional());

  assert(secondBranch != nullptr);
  assert(secondBranch->isConditional());

  /// Operand #0 is a comparison instruction.
  Instruction *sourceInst = (dyn_cast<Instruction>(firstBranch->getOperand(0)));
  assert(sourceInst);

  /// Left branch value is somehow operand #2, right is #1.
  BasicBlock *firstBranchRightBB = dyn_cast<BasicBlock>(firstBranch->getOperand(1));
  assert(firstBranchRightBB);

  BasicBlock *secondBranchRightBB = dyn_cast<BasicBlock>(secondBranch->getOperand(1));

  BranchInst *replacement = BranchInst::Create(firstBranchRightBB,
                                               secondBranchRightBB,
                                               sourceInst);

  /// If I add a named instruction, and the name already exist
  /// in a basic block, then LLVM will make another unique name of it
  /// To prevent this name change we need to 'drop' the existing old name
  firstBranch->setName("");

  replacement->insertAfter(firstBranch);
  firstBranch->replaceAllUsesWith(replacement);
  firstBranch->eraseFromParent();
  assert(firstBranch->getParent() == nullptr);

  return replacement;
}

#pragma mark - Private: Finding possible mutations

AND_OR_MutationType
AndOrReplacementMutationOperator::findPossibleMutationInBranch(BranchInst *branchInst,
                                                               BranchInst **secondBranchInst) {

  /// This filters out the cases when it is "phi" instruction that is before a
  /// branch instruction.
  if (dyn_cast<PHINode>(branchInst->getOperand(0))) {
    return AND_OR_MutationType_None;
  }

  if (branchInst->isConditional() == false) {
    return AND_OR_MutationType_None;
  }

  BasicBlock *leftBB = dyn_cast<BasicBlock>(branchInst->getOperand(2));
  BasicBlock *rightBB = dyn_cast<BasicBlock>(branchInst->getOperand(1));

  bool passedBranchInst = false;
  for (BasicBlock &bb: *branchInst->getFunction()) {
    for (Instruction &instruction: bb) {
      /// PHINodes have implicit dependencies between themselves and their
      /// incoming basic blocks.
      /// Currently if we don't skip PHINodes Mull's auto-test suites crashes
      /// on PHINode->getIncomingBlock... function. Looks like some additional
      /// replacements have to be made when we mutate the branch instruction.
      if (dyn_cast<PHINode>(&instruction)) {
        // return AND_OR_MutationType_None;
      }

      BranchInst *candidateBranchInst = dyn_cast<BranchInst>(&instruction);

      if (candidateBranchInst == nullptr ||
          candidateBranchInst->isConditional() == false) {
        continue;
      }

      if (candidateBranchInst == branchInst) {
        passedBranchInst = true;
        continue;
      }

      if (passedBranchInst == false) {
        continue;
      }

      auto candidateBranchInst_leftBB  = candidateBranchInst->getOperand(2);
      auto candidateBranchInst_rightBB = candidateBranchInst->getOperand(1);

      if (candidateBranchInst_rightBB == rightBB) {
        if (secondBranchInst) {
          *secondBranchInst = candidateBranchInst;
        }

        return AND_OR_MutationType_AND_to_OR;
      }

      else if (candidateBranchInst_leftBB == leftBB) {
        if (secondBranchInst) {
          *secondBranchInst = candidateBranchInst;
        }

        return AND_OR_MutationType_OR_to_AND;
      }
    }
  }

  return AND_OR_MutationType_None;
}
