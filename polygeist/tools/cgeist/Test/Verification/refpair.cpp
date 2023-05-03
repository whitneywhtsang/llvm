// RUN: cgeist -O0 -w %s --function=* -S | FileCheck %s

extern "C" {

struct pair {
    int x, y;
};
void sub0(pair& a);
void sub(pair& a) {
    a.x++;
}

void kernel_deriche() {
    pair a;
    a.x = 32;;
    pair &b = a;
    sub0(b);
}

}

// CHECK:   func @sub(%arg0: memref<?x!polygeist.struct<(i32, i32)>>)
// CHECK-NEXT:     %c1_i32 = arith.constant 1 : i32
// CHECK-NEXT:     %c0 = arith.constant 0 : index
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:     %1 = affine.load %0[0] : memref<?xi32>
// CHECK-NEXT:     %2 = arith.addi %1, %c1_i32 : i32
// CHECK-NEXT:     affine.store %2, %0[0] : memref<?xi32>
// CHECK-NEXT:     return
// CHECK-NEXT:   }

// CHECK:   func @kernel_deriche()
// CHECK-DAG:      %c32_i32 = arith.constant 32 : i32
// CHECK-DAG:      %c0 = arith.constant 0 : index
// CHECK-NEXT:     %alloca = memref.alloca() : memref<1x!polygeist.struct<(i32, i32)>>
// CHECK-NEXT:     %cast = memref.cast %alloca : memref<1x!polygeist.struct<(i32, i32)>> to memref<?x!polygeist.struct<(i32, i32)>>
// CHECK-NEXT:     %0 = "polygeist.subindex"(%cast, %c0) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:     affine.store %c32_i32, %0[0] : memref<?xi32>
// CHECK-NEXT:     call @sub0(%cast) : (memref<?x!polygeist.struct<(i32, i32)>>) -> ()
// CHECK-NEXT:     return
// CHECK-NEXT:   }
