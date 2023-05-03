// RUN: cgeist %s --function=* -S | FileCheck %s

struct meta {
    long long a;
    char dtype;
};

struct fin {
    struct meta f;
    char dtype;
} __attribute__((packed)) ;

long long run(struct meta m, char c);

void compute(struct fin f) {
    run(f.f, f.dtype);
}

// CHECK:   func @compute(%arg0: memref<?x!polygeist.struct<(!polygeist.struct<(i64, i8)>, i8)>>) attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-NEXT:     %c1 = arith.constant 1 : index
// CHECK-NEXT:     %c0 = arith.constant 0 : index
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(!polygeist.struct<(i64, i8)>, i8)>>, index) -> memref<?x!polygeist.struct<(i64, i8)>>
// CHECK-NEXT:     %1 = affine.load %0[0] : memref<?x!polygeist.struct<(i64, i8)>>
// CHECK-NEXT:     %2 = "polygeist.subindex"(%arg0, %c1) : (memref<?x!polygeist.struct<(!polygeist.struct<(i64, i8)>, i8)>>, index) -> memref<?xi8>
// CHECK-NEXT:     %3 = affine.load %2[0] : memref<?xi8>
// CHECK-NEXT:     %4 = call @run(%1, %3) : (!polygeist.struct<(i64, i8)>, i8) -> i64
// CHECK-NEXT:     return
// CHECK-NEXT:   }

