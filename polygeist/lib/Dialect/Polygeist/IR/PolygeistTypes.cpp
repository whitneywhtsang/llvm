//===--- PolygeistTypes.cpp -----------------------------------------------===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "mlir/Dialect/Polygeist/IR/PolygeistTypes.h"
#include "mlir/IR/DialectImplementation.h"

using namespace mlir;
using namespace mlir::polygeist;

Type StructType::parse(AsmParser &parser) {
  if (failed(parser.parseLess()))
    return nullptr;

  std::string name;
  if (succeeded(parser.parseOptionalString(&name))) {
    if (failed(parser.parseComma()))
      return nullptr;
  }

  if (failed(parser.parseLParen()))
    return nullptr;

  SmallVector<Type> body;
  do {
    Type Type;
    if (failed(parser.parseType(Type))) {
      return nullptr;
    }
    body.push_back(Type);
  } while (succeeded(parser.parseOptionalComma()));

  if (failed(parser.parseRParen()) || failed(parser.parseGreater()))
    return nullptr;

  return get(parser.getContext(), body, name);
}

void StructType::print(AsmPrinter &os) const {
  os << "<";
  if (!getName().empty())
    os << "\"" << getName() << "\", ";
  os << "(" << getBody() << ")>";
}
