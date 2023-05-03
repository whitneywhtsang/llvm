// RUN: cgeist -O0 -w %s --function=* -S | FileCheck %s

typedef struct {
  int a, b;
} pair;

pair byval0(pair a, int x);
pair byval(pair a, int x) {
  a.b = x;
  return a;
}

int create() {
  pair p;
  p.a = 0;
  p.b = 1;
  pair p2 = byval0(p, 2);
  return p2.a;
}

// CHECK:    func.func @byval(%arg0: !polygeist.struct<(i32, i32)>, %arg1: i32) -> !polygeist.struct<(i32, i32)>
// CHECK-NEXT:    %c1 = arith.constant 1 : index 
// CHECK-NEXT:    %alloca = memref.alloca() : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %cast = memref.cast %alloca : memref<1x!polygeist.struct<(i32, i32)>> to memref<?x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    affine.store %arg0, %alloca[0] : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %0 = "polygeist.subindex"(%cast, %c1) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32> 
// CHECK-NEXT:    affine.store %arg1, %0[0] : memref<?xi32> 
// CHECK-NEXT:    %1 = affine.load %alloca[0] : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    return %1 : !polygeist.struct<(i32, i32)> 
// CHECK-NEXT:   }
// CHECK:   func @create() -> i32
// CHECK-DAG:     %c2_i32 = arith.constant 2 : i32
// CHECK-DAG:     %c1_i32 = arith.constant 1 : i32
// CHECK-DAG:     %c0_i32 = arith.constant 0 : i32
// CHECK-DAG:     %c0 = arith.constant 0 : index 
// CHECK-DAG:     %c1 = arith.constant 1 : index 
// CHECK-NEXT:    %alloca = memref.alloca() : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %cast = memref.cast %alloca : memref<1x!polygeist.struct<(i32, i32)>> to memref<?x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %alloca_0 = memref.alloca() : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %cast_1 = memref.cast %alloca_0 : memref<1x!polygeist.struct<(i32, i32)>> to memref<?x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %0 = "polygeist.subindex"(%cast_1, %c0) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32> 
// CHECK-NEXT:    affine.store %c0_i32, %0[0] : memref<?xi32> 
// CHECK-NEXT:    %1 = "polygeist.subindex"(%cast_1, %c1) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32> 
// CHECK-NEXT:    affine.store %c1_i32, %1[0] : memref<?xi32> 
// CHECK-NEXT:    %2 = affine.load %alloca_0[0] : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %3 = call @byval0(%2, %c2_i32) : (!polygeist.struct<(i32, i32)>, i32) -> !polygeist.struct<(i32, i32)>
// CHECK-NEXT:    affine.store %3, %alloca[0] : memref<1x!polygeist.struct<(i32, i32)>> 
// CHECK-NEXT:    %4 = "polygeist.subindex"(%cast, %c0) : (memref<?x!polygeist.struct<(i32, i32)>>, index) -> memref<?xi32> 
// CHECK-NEXT:    %5 = affine.load %4[0] : memref<?xi32> 
// CHECK-NEXT:    return %5 : i32 
// CHECK-NEXT:   }
