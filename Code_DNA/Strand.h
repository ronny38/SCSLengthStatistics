#ifndef STRAND_H
#define STRAND_H

#include <vector>
#include "Settings.h"

class Strand
{
public:
	enum Base
	{
		A = 0,
		C = 1,
		G = 2,
		T = 3
	};

	Strand();
	Strand(uint64_t value);
	~Strand() = default;

	uint64_t Value() const;
	Base& operator[](int i);
	const Base& operator[](int i) const;
	Strand& operator++();

	bool operator<(const Strand& other) const;
	bool operator<=(const Strand& other) const;
	bool operator==(const Strand& other) const;

	static Strand Reverse(const Strand& other);
	static Strand Flip(const Strand& other);
	static const Strand& Min(const Strand& s1, const Strand& s2);
	static const Strand& Min(const Strand& s1, const Strand& s2, const Strand& s3);
	static const Strand& Max(const Strand& s1, const Strand& s2);
	static const Strand& Max(const Strand& s1, const Strand& s2, const Strand& s3);
	static uint64_t MaxValue();
	static uint64_t FirstStrandMaxValue();

private:
	std::vector<Base> m_vec;
	uint64_t m_value;

	void ReEvaluate();

	static Base ShiftMod4(Base b);

};

#endif // !STRAND_H
