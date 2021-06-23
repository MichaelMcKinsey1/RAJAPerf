//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2017-21, Lawrence Livermore National Security, LLC
// and RAJA Performance Suite project contributors.
// See the RAJAPerf/COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include "SORTPAIRS.hpp"

#include "RAJA/RAJA.hpp"

#include "common/DataUtils.hpp"

namespace rajaperf
{
namespace algorithm
{


SORTPAIRS::SORTPAIRS(const RunParams& params)
  : KernelBase(rajaperf::Algorithm_SORTPAIRS, params)
{
  setDefaultSize(1000000);
  setDefaultReps(20);

  setUsesFeature(Sort);

  setVariantDefined( Base_Seq );
  setVariantDefined( RAJA_Seq );

  setVariantDefined( RAJA_OpenMP );

  setVariantDefined( RAJA_CUDA );

  setVariantDefined( RAJA_HIP );
}

SORTPAIRS::~SORTPAIRS()
{
}

size_t SORTPAIRS::getBytesPerRep() const
{
  return (2*sizeof(Index_type) + 2*sizeof(Index_type)) * getRunSize() ; // touched data size, not actual number of stores and loads
}

void SORTPAIRS::setUp(VariantID vid)
{
  allocAndInitDataRandValue(m_x, getRunSize()*getRunReps(), vid);
  allocAndInitDataRandValue(m_i, getRunSize()*getRunReps(), vid);
}

void SORTPAIRS::updateChecksum(VariantID vid)
{
  checksum[vid] += calcChecksum(m_x, getRunSize()*getRunReps());
  checksum[vid] += calcChecksum(m_i, getRunSize()*getRunReps());
}

void SORTPAIRS::tearDown(VariantID vid)
{
  (void) vid;
  deallocData(m_x);
  deallocData(m_i);
}

} // end namespace algorithm
} // end namespace rajaperf
