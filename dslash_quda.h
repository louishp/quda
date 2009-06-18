#ifndef _QUDA_DSLASH_H
#define _QUDA_DSLASH_H

#include <cuComplex.h>

#include <quda.h>

#define gaugeSiteSize 18 // real numbers per link
#define spinorSiteSize 24 // real numbers per spinor
#define cloverSiteSize 72 // real numbers per block-diagonal clover matrix

#define BLOCK_DIM (64) // threads per block
#define GRID_DIM (Nh/BLOCK_DIM) // there are Nh threads in total

#define PACKED12_GAUGE_BYTES (4*Nh*12*sizeof(float))
#define PACKED8_GAUGE_BYTES (4*Nh*8*sizeof(float))

#define CLOVER_BYTES (Nh*cloverSiteSize*sizeof(float))

#ifdef __cplusplus
extern "C" {
#endif

  extern FullGauge cudaGaugePrecise;
  extern FullGauge cudaGaugeSloppy;

  extern QudaGaugeParam *gauge_param;
  extern QudaInvertParam *invert_param;

  extern FullClover cudaClover;

  extern ParitySpinor hSpinor1;
  extern ParitySpinor hSpinor2;

// ---------- dslash_quda.cu ----------

  int dslashCudaSharedBytes();
  void setCudaGaugeParam();
  void bindGaugeTex(FullGauge gauge, int oddBit);

  // Double precision routines
  void dslashDCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor,
		   int oddBit, int daggerBit);
  void dslashXpayDCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor, 
		       int oddBit, int daggerBit, ParitySpinor x, double a);

  // Single precision routines
  void dslashSCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor,
		   int oddBit, int daggerBit);
  void dslashXpaySCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor, 
		       int oddBit, int daggerBit, ParitySpinor x, double a);

  // Half precision dslash routines
  void dslashHCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor,
		   int oddBit, int daggerBit);
  void dslashXpayHCuda(ParitySpinor res, FullGauge gauge, ParitySpinor spinor, 
		       int oddBit, int daggerBit, ParitySpinor x, double a);

  // wrapper to above
  void dslashCuda(ParitySpinor out, FullGauge gauge, ParitySpinor in, int parity, int dagger);
  void dslashXpayCuda(ParitySpinor out, FullGauge gauge, ParitySpinor in, int parity, int dagger,
		      ParitySpinor x, double a);

  // Full Wilson matrix
  void MatCuda(FullSpinor out, FullGauge gauge, FullSpinor in, double kappa);
  void MatDagCuda(FullSpinor out, FullGauge gauge, FullSpinor in, double kappa);

  void MatPCCuda(ParitySpinor outEven, FullGauge gauge, ParitySpinor inEven, 
		 double kappa, ParitySpinor tmp, MatPCType matpc_type);
  void MatPCDagCuda(ParitySpinor outEven, FullGauge gauge, ParitySpinor inEven, 
		    double kappa, ParitySpinor tmp, MatPCType matpc_type);
  void MatPCDagMatPCCuda(ParitySpinor outEven, FullGauge gauge, ParitySpinor inEven,
			 double kappa, ParitySpinor tmp, MatPCType matpc_type);
  
  /*QudaSumComplex MatPCcDotWXCuda(ParitySpinor outEven, FullGauge gauge, ParitySpinor inEven, 
				 float kappa, ParitySpinor tmp, ParitySpinor d, MatPCType matpc_type);
  QudaSumComplex MatPCDagcDotWXCuda(ParitySpinor outEven, FullGauge gauge, ParitySpinor inEven, 
  float kappa, ParitySpinor tmp, ParitySpinor d, MatPCType matpc_type);*/
  
  // -- inv_cg_cuda.cpp
  void invertCgCuda(ParitySpinor x, ParitySpinor b, FullGauge gauge, 
		    ParitySpinor tmp, QudaInvertParam *param);
  
  // -- inv_bicgstab_cuda.cpp
  void invertBiCGstabCuda(ParitySpinor x, ParitySpinor b, FullGauge gaugeSloppy, 
			  FullGauge gaugePrecise, ParitySpinor tmp, 
			  QudaInvertParam *param, DagType dag_type);
  
#ifdef __cplusplus
}
#endif

#endif // _QUDA_DLASH_H
