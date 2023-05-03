// RUN: cgeist -O0 -w %s --function=* -S --raise-scf-to-affine=false | FileCheck %s

struct AIntDivider {
    AIntDivider() : divisor(3) {}
    unsigned int divisor;
};

void kern() {
    AIntDivider sizes_[25];
}

// CHECK:   func @_Z4kernv() attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-DAG:     %c1 = arith.constant 1 : index
// CHECK-DAG:     %c0 = arith.constant 0 : index
// CHECK-DAG:     %c25 = arith.constant 25 : index
// CHECK-NEXT:    %alloca = memref.alloca() : memref<25x!polygeist.struct<(i32)>>
// CHECK-NEXT:    scf.for %arg0 = %c0 to %c25 step %c1 {
// CHECK-NEXT:      %0 = "polygeist.subindex"(%alloca, %arg0) : (memref<25x!polygeist.struct<(i32)>>, index) -> memref<?x!polygeist.struct<(i32)>>
// CHECK-NEXT:      func.call @_ZN11AIntDividerC1Ev(%0) : (memref<?x!polygeist.struct<(i32)>>) -> ()
// CHECK-NEXT:    }
// CHECK-NEXT:    return
// CHECK-NEXT:   }
// CHECK:   func.func @_ZN11AIntDividerC1Ev(%arg0: memref<?x!polygeist.struct<(i32)>>)
// CHECK-NEXT:     %c0 = arith.constant 0 : index
// CHECK-NEXT:     %c3_i32 = arith.constant 3 : i32
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:     affine.store %c3_i32, %0[0] : memref<?xi32>
// CHECK-NEXT:     return
// CHECK-NEXT:   }
