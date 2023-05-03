// RUN: cgeist -O0 -w %s  --function=* -S | FileCheck %s

class D {
  double a;
  double b;
};

class QStream {
  D device_;
  int id;
};

QStream ilaunch_kernel(QStream x) {
  return x;
}

// CHECK:   func @_Z14ilaunch_kernel7QStream(%arg0: memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>) -> !polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)> attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-NEXT:     %alloca = memref.alloca() : memref<1x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>
// CHECK-NEXT:     %cast = memref.cast %alloca : memref<1x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>> to memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>
// CHECK-NEXT:     call @_ZN7QStreamC1EOS_(%cast, %arg0) : (memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>) -> ()
// CHECK-NEXT:     %0 = affine.load %alloca[0] : memref<1x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>
// CHECK-NEXT:     return %0 : !polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>
// CHECK-NEXT:   }
// CHECK-NEXT:   func @_ZN7QStreamC1EOS_(%arg0: memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, %arg1: memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>) attributes {llvm.linkage = #llvm.linkage<linkonce_odr>} {
// CHECK-NEXT:     %c1 = arith.constant 1 : index 
// CHECK-NEXT:     %c0 = arith.constant 0 : index 
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, index) -> memref<?x!polygeist.struct<(f64, f64)>> 
// CHECK-NEXT:     %1 = "polygeist.subindex"(%arg1, %c0) : (memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, index) -> memref<?x!polygeist.struct<(f64, f64)>>
// CHECK-NEXT:     call @_ZN1DC1EOS_(%0, %1) : (memref<?x!polygeist.struct<(f64, f64)>>, memref<?x!polygeist.struct<(f64, f64)>>) -> ()
// CHECK-NEXT:     %2 = "polygeist.subindex"(%arg1, %c1) : (memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:     %3 = affine.load %2[0] : memref<?xi32>
// CHECK-NEXT:     %4 = "polygeist.subindex"(%arg0, %c1) : (memref<?x!polygeist.struct<(!polygeist.struct<(f64, f64)>, i32)>>, index) -> memref<?xi32>
// CHECK-NEXT:     affine.store %3, %4[0] : memref<?xi32>
// CHECK-NEXT:     return
// CHECK-NEXT:   }
// CHECK-NEXT:   func @_ZN1DC1EOS_(%arg0: memref<?x!polygeist.struct<(f64, f64)>>, %arg1: memref<?x!polygeist.struct<(f64, f64)>>)
// CHECK-NEXT:     %c1 = arith.constant 1 : index 
// CHECK-NEXT:     %c0 = arith.constant 0 : index 
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg1, %c0) : (memref<?x!polygeist.struct<(f64, f64)>>, index) -> memref<?xf64> 
// CHECK-NEXT:     %1 = affine.load %0[0] : memref<?xf64> 
// CHECK-NEXT:     %2 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(f64, f64)>>, index) -> memref<?xf64> 
// CHECK-NEXT:     affine.store %1, %2[0] : memref<?xf64> 
// CHECK-NEXT:     %3 = "polygeist.subindex"(%arg1, %c1) : (memref<?x!polygeist.struct<(f64, f64)>>, index) -> memref<?xf64> 
// CHECK-NEXT:     %4 = affine.load %3[0] : memref<?xf64> 
// CHECK-NEXT:     %5 = "polygeist.subindex"(%arg0, %c1) : (memref<?x!polygeist.struct<(f64, f64)>>, index) -> memref<?xf64> 
// CHECK-NEXT:     affine.store %4, %5[0] : memref<?xf64> 
// CHECK-NEXT:     return
// CHECK-NEXT:   }
