#ifndef __VSN_MATHDEFS_H
#define __VSN_MATHDEFS_H

#include <cstdlib>
#include <cmath>
#include <limits>

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

static const unsigned M_MIN_UNSIGNED = 0x00000000;
static const unsigned M_MAX_UNSIGNED = 0xffffffff;

VSN_END_NAMESPACE

template <typename T>
inline T vAbs(const T &t) { return t >= 0 ? t : -t; }

template <typename T>
inline const T& vMin(const T& a, const T& b) { return (a < b) ? a : b; }
template <typename T>
inline const T& vMax(const T& a, const T& b) { return (a < b) ? b : a; }

inline int vRound(double d) { return d >= 0.0 ? int(d + 0.5) : int(d - double(int(d - 1)) + 0.5) + int(d - 1); }
inline int vRound(float d) { return d >= 0.0f ? int(d + 0.5f) : int(d - float(int(d - 1)) + 0.5f) + int(d - 1); }
inline int64 vRound64(double d) { return d >= 0.0 ? int64(d + 0.5) : int64(d - double(int64(d - 1)) + 0.5) + int64(d - 1); }
inline int64 vRound64(float d) { return d >= 0.0f ? int64(d + 0.5f) : int64(d - float(int64(d - 1)) + 0.5f) + int64(d - 1); }

static inline bool IsEqual(double p1, double p2) { return (vAbs(p1 - p2) * 1000000000000. <= vMin(vAbs(p1), vAbs(p2))); }
static inline bool IsEqual(double d) { return vAbs(d) <= 0.000000000001; }
static inline bool IsEqual(float p1, float p2) { return (vAbs(p1 - p2) * 100000.f <= vMin(vAbs(p1), vAbs(p2))); }
static inline bool IsEqualNull(double d) { return vAbs(d) <= 0.000000000001; }
static inline bool IsEqualNull(float d) { return vAbs(d) <= PARAM_REGION; }

#endif /* __VSN_MATHDEFS_H */
