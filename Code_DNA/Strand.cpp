#include <tgmath.h>
#include "Strand.h"

Strand& Strand::operator++()
{
	m_value++;

	auto i = 0;
	while (m_vec[i] == T)
	{
		m_vec[i] = A;
		i++;
		if (i == N)
		{
			return *this;
		}
	}
	m_vec[i] = static_cast<Strand::Base>(static_cast<uint8_t>(m_vec[i]) + 1);

	return *this;
}

const Strand& Strand::Min(const Strand& s1, const Strand& s2)
{
	return (s1.Value() <= s2.Value() ? s1 : s2);
}

const Strand& Strand::Min(const Strand& s1, const Strand& s2, const Strand& s3)
{
	return Strand::Min(Strand::Min(s1, s2), s3);
}

const Strand& Strand::Max(const Strand& s1, const Strand& s2)
{
	return (s1.Value() >= s2.Value() ? s1 : s2);
}

const Strand& Strand::Max(const Strand& s1, const Strand& s2, const Strand& s3)
{
	return Strand::Max(Strand::Max(s1, s2), s3);
}

inline Strand::Base& Strand::operator[](int i)
{
	return m_vec[i];
}

inline uint64_t Strand::Value() const
{
	return m_value;
}

inline const Strand::Base& Strand::operator[](int i) const
{
	return m_vec[i];
}

Strand Strand::Flip(const Strand& other)
{
	Strand res;
	for (auto i = 0; i < N; ++i)
	{
		res[i] = ShiftMod4(other[i]);
	}
	res.ReEvaluate();
	return res;
}

uint64_t Strand::MaxValue()
{
	static uint64_t max = 0;

	// Calculate only on first call
	if (max != 0)
	{
		return max;
	}
	
	Strand MaxStrand;
	for (auto i = 0; i < N; ++i)
	{
		MaxStrand.m_vec[i] = T;
	}
	MaxStrand.ReEvaluate();
	max = MaxStrand.Value() + 1;
	return max;
}

uint64_t Strand::FirstStrandMaxValue()
{
	static uint64_t max = 0;

	// Calculate only on first call
	if (max != 0)
	{
		return max;
	}

	Strand MaxStrand;
	for (auto i = 0; i < N - 1; ++i)
		// S1's MSB is always 'A'.
	{
		MaxStrand.m_vec[i] = T;
	}
	MaxStrand.ReEvaluate();
	max = MaxStrand.Value() + 1;
	return max;
}

Strand::Strand() : m_vec(N, A), m_value(0) {}

Strand::Strand(uint64_t value) : m_vec(N, A), m_value(value)
{
	for (auto i = 0; value != 0; ++i, value /= 4)
	{
		m_vec[i] = static_cast<Base>(static_cast<uint8_t>(value % 4));
	}
}

bool Strand::operator<(const Strand& other) const
{
	return m_value < other.Value();
}

bool Strand::operator<=(const Strand& other) const
{
	return m_value <= other.Value();
}

bool Strand::operator==(const Strand& other) const
{
	return m_value == other.Value();
}

void Strand::ReEvaluate()
{
	m_value = 0;
	for (uint64_t i = 0; i < N; ++i)
	{
		m_value += (static_cast<uint64_t>(pow(4, i)) * static_cast<uint64_t>(m_vec[i]));
	}
}

inline Strand::Base Strand::ShiftMod4(Strand::Base base)
{
	auto temp = static_cast<uint64_t>(base);
	temp = (temp + 1) % 4;
	return static_cast<Base>(temp);
}

Strand Strand::Reverse(const Strand& other)
{
	Strand res;
	for (auto i = 0; i < N; ++i)
	{
		res[N - i - 1] = other[i];
	}
	res.ReEvaluate();
	return res;
}
