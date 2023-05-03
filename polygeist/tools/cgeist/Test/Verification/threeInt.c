// RUN: cgeist -O0 -w %s --function=struct_pass_all_same -S | FileCheck %s

typedef struct {
  int a, b, c;
} threeInt;

int struct_pass_all_same(threeInt* a) {
  return a->b;
}

// CHECK:  func @struct_pass_all_same(%arg0: memref<?x!polygeist.struct<(i32, i32, i32)>>) -> i32
// CHECK-NEXT:    %c1 = arith.constant 1 : index
// CHECK-NEXT:    %0 = "polygeist.subindex"(%arg0, %c1) : (memref<?x!polygeist.struct<(i32, i32, i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:    %1 = affine.load %0[0] : memref<?xi32>
// CHECK-NEXT:    return %1 : i32
// CHECK-NEXT:  }
