// RUN: cgeist -O0 -w %s %stdinclude --function=alloc -S | FileCheck %s

#include <time.h>
#include <sys/time.h>
double alloc() {
  struct timeval Tp;
  gettimeofday(&Tp, NULL);
  return Tp.tv_sec + Tp.tv_usec * 1.0e-6;
}

// CHECK:   func @alloc() -> f64
// CHECK-DAG:      %cst = arith.constant 9.9999999999999995E-7 : f64
// CHECK-DAG:      %c0 = arith.constant 0 : index
// CHECK-DAG:      %c1 = arith.constant 1 : index
// CHECK-NEXT:     %alloca = memref.alloca() : memref<1x!polygeist.struct<(i64, i64)>>
// CHECK-NEXT:     %cast = memref.cast %alloca : memref<1x!polygeist.struct<(i64, i64)>> to memref<?x!polygeist.struct<(i64, i64)>>
// CHECK-NEXT:     %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!polygeist.struct<(i64, i64)>>) -> !llvm.ptr<struct<(i64, i64)>>
// CHECK-NEXT:     %1 = llvm.mlir.null : !llvm.ptr<{{.*}}>
// CHECK:          %{{.*}} = llvm.call @gettimeofday(%0, %{{.*}}) : (!llvm.ptr<struct<(i64, i64)>>, {{.*}}) -> i32
// CHECK-NEXT:     [[T3:%.*]] = "polygeist.subindex"(%cast, %c0) : (memref<?x!polygeist.struct<(i64, i64)>>, index) -> memref<?xi64>
// CHECK-NEXT:     [[T4:%.*]] = affine.load [[T3]][0] : memref<?xi64>
// CHECK-NEXT:     [[T5:%.*]] = arith.sitofp [[T4]] : i64 to f64
// CHECK-NEXT:     [[T6:%.*]] = "polygeist.subindex"(%cast, %c1) : (memref<?x!polygeist.struct<(i64, i64)>>, index) -> memref<?xi64>
// CHECK-NEXT:     [[T7:%.*]] = affine.load [[T6]][0] : memref<?xi64>
// CHECK-NEXT:     [[T8:%.*]] = arith.sitofp [[T7]] : i64 to f64
// CHECK-NEXT:     [[T9:%.*]] = arith.mulf [[T8]], %cst : f64
// CHECK-NEXT:     [[T10:%.*]] = arith.addf [[T5]], [[T9]] : f64
// CHECK-NEXT:     return [[T10]] : f64
// CHECK-NEXT:   }
