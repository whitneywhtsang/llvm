// RUN: cgeist %s %stdinclude --function=func -S | FileCheck %s

float hload(const void* data);

struct OperandInfo {
  char dtype = 'a';

  void* data;

  bool end;
};

extern "C" {
float func(struct OperandInfo* op) {
    return hload(op->data);
}
}

// CHECK:   func @func(%arg0: memref<?x!polygeist.struct<(i8, !llvm.ptr<i8>, i8)>>) -> f32 attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-NEXT:     %[[i1:.+]] = arith.constant 1 : index
// CHECK-NEXT:     %[[i2:.+]] = "polygeist.subindex"(%arg0, %[[i1]]) : (memref<?x!polygeist.struct<(i8, !llvm.ptr<i8>, i8)>>, index) -> memref<?x!llvm.ptr<i8>>
// CHECK-NEXT:     %[[i3:.+]] = affine.load %[[i2]][0] : memref<?x!llvm.ptr<i8>>
// CHECK-NEXT:     %[[i4:.+]] = call @_Z5hloadPKv(%[[i3]]) : (!llvm.ptr<i8>) -> f32
// CHECK-NEXT:     return %[[i4]] : f32
// CHECK-NEXT:   }
