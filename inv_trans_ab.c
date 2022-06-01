#include "inv_trans_ab.h"

#define COS23PI (-0.5)
#define COS43PI (-0.5)
#define SIN23PI (0.8660254)
#define SIN43PI (-0.8660254)
#define ROOT23 (0.4444444)


inv_ab_t inv_trans_ab(
	float u, 
	float v,
	float w
)
{
	inv_ab_t ret;

	ret.a = (u + (v*COS23PI) + (w*COS43PI))*ROOT23;
	ret.b = ((v*SIN23PI) + (w*SIN43PI))*ROOT23;

	return ret;
}
