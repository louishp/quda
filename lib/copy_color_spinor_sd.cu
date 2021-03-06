#include <copy_color_spinor.cuh>

namespace quda {
  
  void copyGenericColorSpinorSD(ColorSpinorField &dst, const ColorSpinorField &src, 
				QudaFieldLocation location, void *Dst, void *Src, 
				void *dstNorm, void *srcNorm) {
    CopyGenericColorSpinor<3>(dst, src, location, (float*)Dst, (double*)Src);
  }  

} // namespace quda
