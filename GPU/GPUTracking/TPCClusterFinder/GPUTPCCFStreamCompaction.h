// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file StreamCompaction.h
/// \author Felix Weiglhofer

#ifndef O2_GPU_STREAM_COMPACTION_H
#define O2_GPU_STREAM_COMPACTION_H

#include "clusterFinderDefs.h"
#include "GPUGeneralKernels.h"
#include "GPUConstantMem.h"
#include "GPUTPCClusterFinder.h"

namespace GPUCA_NAMESPACE
{
namespace gpu
{

class GPUTPCCFStreamCompaction
{

 public:
  class GPUTPCSharedMemory : public GPUKernelTemplate::GPUTPCSharedMemoryScan64<int, GPUCA_THREAD_COUNT_SCAN>
  {
  };

  enum K {
    nativeScanUpStart,
    nativeScanUp,
    nativeScanTop,
    nativeScanDown,
    compactDigit,
  };

  static GPUd() void nativeScanUpStartImpl(int, int, int, int, GPUTPCSharedMemory&,
                                           const uchar*, int*, int*,
                                           int);

  static GPUd() void nativeScanUpImpl(int, int, int, int, GPUTPCSharedMemory&,
                                      int*, int*, int);

  static GPUd() void nativeScanTopImpl(int, int, int, int, GPUTPCSharedMemory&,
                                       int*, int);

  static GPUd() void nativeScanDownImpl(int, int, int, int, GPUTPCSharedMemory&,
                                        int*, const int*, unsigned int, int);

  static GPUd() void compactDigitImpl(int, int, int, int, GPUTPCSharedMemory&,
                                      const deprecated::Digit*, deprecated::Digit*,
                                      const uchar*, int*, const int*,
                                      int);

#ifdef HAVE_O2HEADERS
  typedef GPUTPCClusterFinder processorType;
  GPUhdi() static processorType* Processor(GPUConstantMem& processors)
  {
    return processors.tpcClusterer;
  }
#endif

  GPUhdi() CONSTEXPR static GPUDataTypes::RecoStep GetRecoStep()
  {
    return GPUDataTypes::RecoStep::TPCClusterFinding;
  }

  template <int iKernel = 0, typename... Args>
  GPUd() static void Thread(int nBlocks, int nThreads, int iBlock, int iThread, GPUTPCSharedMemory& smem, processorType& clusterer, Args... args);

 private:
  GPUd() static int compactionElems(processorType& clusterer, int stage);
};

} // namespace gpu
} // namespace GPUCA_NAMESPACE

#endif