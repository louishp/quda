#ifndef _WILSON_DSLASH_REFERENCE_H
#define _WILSON_DSLASH_REFERENCE_H

#include <enum_quda.h>

#ifdef __cplusplus
extern "C" {
#endif

  extern int Z[4];
  extern int Vh;
  extern int V;

  void setDims(int *);

  void wil_dslash(void *res, void **gauge, void *spinorField, int oddBit,
		  int daggerBit, QudaPrecision precision);
  
  void wil_mat(void *out, void **gauge, void *in, double kappa, int daggerBit,
	       QudaPrecision precision);

  void wil_matpc(void *out, void **gauge, void *in, double kappa,
		 QudaMatPCType matpc_type,  int daggerBit, QudaPrecision precision);

  void tm_dslash(void *res, void **gauge, void *spinorField, double kappa,
		 double mu, QudaTwistFlavorType flavor, int oddBit,
		 int daggerBit, QudaPrecision sprecision);
  
  void tm_mat(void *out, void **gauge, void *in, double kappa, double mu,
	      QudaTwistFlavorType flavor, int daggerBit, QudaPrecision precision);

  void tm_matpc(void *out, void **gauge, void *in, double kappa, double mu,
		QudaTwistFlavorType flavor, QudaMatPCType matpc_type,  
		int daggerBit, QudaPrecision precision);

#ifdef __cplusplus
}
#endif

#endif // _WILSON_DSLASH_REFERENCE_H
