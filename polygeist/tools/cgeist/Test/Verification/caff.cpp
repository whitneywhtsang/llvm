// RUN: cgeist %s --function=* -S | FileCheck %s

struct AOperandInfo {
  void* data;

  bool is_output;

  bool is_read_write;
};


/// This is all the non-templated stuff common to all SmallVectors.

/// This is the part of SmallVectorTemplateBase which does not depend on whether
/// the type T is a POD. The extra dummy template argument is used by ArrayRef
/// to avoid unnecessarily requiring T to be complete.
template <typename T>
class ASmallVectorTemplateCommon {
 public:
  void *BeginX, *EndX;

  // forward iterator creation methods.
  const T* begin() const {
    return (const T*)this->BeginX;
  }
};

unsigned long long int div_kernel_cuda(ASmallVectorTemplateCommon<AOperandInfo> &operands) {
  return (const AOperandInfo*)operands.EndX - operands.begin();
}


// CHECK:   func @_Z15div_kernel_cudaR26ASmallVectorTemplateCommonI12AOperandInfoE(%arg0: memref<?x!polygeist.struct<(!llvm.ptr<i8>, !llvm.ptr<i8>)>>) -> i64 attributes {llvm.linkage = #llvm.linkage<external>} {
// CHECK-DAG:      %c16_i64 = arith.constant 16 : i64
// CHECK-DAG:      %c1 = arith.constant 1 : index 
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c1) : (memref<?x!polygeist.struct<(!llvm.ptr<i8>, !llvm.ptr<i8>)>>, index) -> memref<?x!llvm.ptr<i8>> 
// CHECK-NEXT:     %1 = affine.load %0[0] : memref<?x!llvm.ptr<i8>> 
// CHECK-NEXT:     %2 = call @_ZNK26ASmallVectorTemplateCommonI12AOperandInfoE5beginEv(%arg0) : (memref<?x!polygeist.struct<(!llvm.ptr<i8>, !llvm.ptr<i8>)>>) -> memref<?x!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>>
// CHECK-NEXT:     %3 = llvm.bitcast %1 : !llvm.ptr<i8> to !llvm.ptr<!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>>
// CHECK-DAG:     %[[i4:.+]] = llvm.ptrtoint %3 : !llvm.ptr<!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>> to i64
// CHECK-DAG:     %[[i5:.+]] = "polygeist.memref2pointer"(%2) : (memref<?x!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>>) -> !llvm.ptr<!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>>
// CHECK-DAG:     %[[i6:.+]] = llvm.ptrtoint %[[i5]] : !llvm.ptr<!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>> to i64
// CHECK-DAG:     %[[i7:.+]] = arith.subi %[[i4]], %[[i6]] : i64
// CHECK-NEXT:    %[[i8:.+]] = arith.divsi %[[i7]], %c16_i64 : i64
// CHECK-NEXT:     return %[[i8]] : i64
// CHECK-NEXT:   }
// CHECK:   func @_ZNK26ASmallVectorTemplateCommonI12AOperandInfoE5beginEv(%arg0: memref<?x!polygeist.struct<(!llvm.ptr<i8>, !llvm.ptr<i8>)>>) -> memref<?x!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>> attributes {llvm.linkage = #llvm.linkage<linkonce_odr>} {
// CHECK-NEXT:     %c0 = arith.constant 0 : index 
// CHECK-NEXT:     %0 = "polygeist.subindex"(%arg0, %c0) : (memref<?x!polygeist.struct<(!llvm.ptr<i8>, !llvm.ptr<i8>)>>, index) -> memref<?x!llvm.ptr<i8>> 
// CHECK-NEXT:     %1 = affine.load %0[0] : memref<?x!llvm.ptr<i8>> 
// CHECK-NEXT:     %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr<i8>) -> memref<?x!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>> 
// CHECK-NEXT:     return %2 : memref<?x!polygeist.struct<(!llvm.ptr<i8>, i8, i8)>>
// CHECK-NEXT:   }
