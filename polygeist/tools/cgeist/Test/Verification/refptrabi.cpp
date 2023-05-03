// RUN: cgeist -O0 -w %s  --function=ll -S | FileCheck %s

struct alignas(2) Half {
  unsigned short x;

  Half() = default;
};

extern "C" {

float thing(Half);

float ll(void* data) {
    return thing(*(Half*)data);
}

}

// CHECK:   func @ll(%arg0: !llvm.ptr<i8>) -> f32 attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-NEXT:     %alloca = memref.alloca() : memref<1x!polygeist.struct<(i16)>>
// CHECK-NEXT:     %cast = memref.cast %alloca : memref<1x!polygeist.struct<(i16)>> to memref<?x!polygeist.struct<(i16)>>
// CHECK-NEXT:     %0 = "polygeist.pointer2memref"(%arg0) : (!llvm.ptr<i8>) -> memref<?x!polygeist.struct<(i16)>>
// CHECK-NEXT:     call @_ZN4HalfC1ERKS_(%cast, %0) : (memref<?x!polygeist.struct<(i16)>>, memref<?x!polygeist.struct<(i16)>>) -> ()
// CHECK-NEXT:     %1 = affine.load %alloca[0] : memref<1x!polygeist.struct<(i16)>>
// CHECK-NEXT:     %2 = call @thing(%1) : (!polygeist.struct<(i16)>) -> f32
// CHECK-NEXT:     return %2 : f32
// CHECK-NEXT:   }
