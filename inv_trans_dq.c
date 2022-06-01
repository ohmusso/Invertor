#include "math.h"
#include "inv_trans_dq.h"

#define COS23PI (-0.5)
#define COS43PI (-0.5)
#define SIN23PI (0.8660254)
#define SIN43PI (-0.8660254)
#define ROOT23 (0.4444444)


inv_dq_t inv_trans_dq(
	float a,
	float b,
	float rad
)
{
	inv_dq_t ret;

	ret.d = (a*cos(rad)) + (b*sin(rad));
	ret.q = -(a*sin(rad)) + (b*cos(rad));

	return ret;
}
