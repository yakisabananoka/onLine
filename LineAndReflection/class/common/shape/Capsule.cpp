#include <algorithm>
#include "Capsule.h"

Capsule::Capsule() :
	radius(0)
{
}

Capsule::Capsule(Vector2Dbl pA, Vector2Dbl pB, double r) :
	posA(pA), posB(pB), radius(r)
{
}

Vector2Dbl Capsule::Vec(void)const
{
	return posB - posA;
}

bool Capsule::InShape(const Vector2Dbl& checkPos) const
{
	auto tVec = checkPos - posA;
	auto capVec = Vec();
	auto nLVec = capVec.Normalized();

	auto perQ = tVec.Dot(capVec) / capVec.SQMagnitude();
	perQ = std::clamp(perQ, 0.0, 1.0);

	auto qPos = capVec * perQ + posA;

	double sqDist = (qPos - checkPos).SQMagnitude();

	return sqDist < pow(radius, 2);
}
