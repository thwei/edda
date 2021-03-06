// Copyright 2015 The Edda Authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

// Distribution:
// Define generic functions, which can be overriden by specific template classes

#include <iostream>
#include <typeinfo>

#include "common.h"
#include "edda_export.h"

namespace edda {
namespace dist {

// a dummy distribution for illustration
// The purpose of this file is to define the interface of a new distribution.
// class Real: this is only used for data storage type, which is float as default
//    to reduce so size.  Otherwise in general the input/output types should
//    be double

template <typename Real = float>
class EDDA_EXPORT Distribution {
public:
    typedef Real real_type;
    // get probability, either pdf (continuous) or pmf (discrete)
    inline Real getProb(const Real x) const { return 0; }
    inline Real getMean() const { return 0; }
    inline Real getStd() const { return 0; }
    // Get variance
    inline Real getVar() const { return 0; }
    inline Real getSample() const { return 0; }

    // random variable +=
    inline Distribution& operator+=(const Distribution& rhs) { return *this; }
    // random variable -=
    inline Distribution& operator-=(const Distribution& rhs) { return *this; }
    // // random variable +=
    inline Distribution& operator+=(const double r) { return *this;  }
    // random variable *=
    inline Distribution& operator*=(const double r) { return *this; }
};

// Here are generic functions that can be reused by new distributions if not
// implemented.

// random variable +
template<class T>
inline T operator+(const T& lhs, const T& rhs) {
    T h(lhs);
    return h += rhs;
}

// random variable -
template<class T>
inline T operator-(const T& lhs, const T& rhs) {
    T h(lhs);
    return h -= rhs;
}

// random variable *
template<class T>
inline T operator*(const T& lhs, const double x) {
    T h(lhs);
    return h *= x;
}

// cdf
template <class T>
inline double cdf(const T& dist, double x)
{
    std::cerr << "Generic computation of cdf: Not implemented" << std::endl;
    throw NotImplementedException();
    return 0;
}

#if 0
// Random variable interpolation:  d1*(1-alpha) + d2*alpha
// Assume correlation of d1 and d2 is 0
template <class T>
T lerp(const T& d1, const T& d2, double alpha )
{
    return d1*(1-alpha) + d2*alpha;
}
#endif


}  // namespace dist
}  // namespace edda

#endif // DISTRIBUTION_H_
