//=== PolygeistTypes.td - Polygeist dialect type definitions *- tablegen -*===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This is the definition file for Polygeist dialect types.
//
//===----------------------------------------------------------------------===//

#ifndef POLYGEIST_TYPES
#define POLYGEIST_TYPES

include "mlir/Dialect/LLVMIR/LLVMInterfaces.td"
include "mlir/Dialect/Polygeist/IR/PolygeistBase.td"
include "mlir/IR/BuiltinTypes.td"

class Polygeist_Type<string name, string typeMnemonic, list<Trait> traits = []>
    : TypeDef<Polygeist_Dialect, name,
              !listconcat([MemRefElementTypeInterface,
                           LLVM_PointerElementTypeInterface],
                               traits)> {
  let mnemonic = typeMnemonic;
}

def Polygeist_StructType :
    Polygeist_Type<"Struct", "struct"> {
  let parameters = (ins ArrayRefParameter<"mlir::Type">:$body,
                        StringRefParameter<"name">:$name);
  let builders = [
    TypeBuilder<(ins "llvm::ArrayRef<mlir::Type>":$body),[{
      return $_get($_ctxt, body, "");
    }]>
  ];
  let extraClassDeclaration = [{
    LogicalResult setBody(llvm::ArrayRef<mlir::Type>);
  }]; 
  let hasCustomAssemblyFormat = 1;
}

#endif // POLYGEIST_TYPES
