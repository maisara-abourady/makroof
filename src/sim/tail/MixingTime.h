#pragma once

// Mixing time of the hybrid IR, per emitter (phase-04 spec, scope 2).
//
// t_mix,e is the smallest t >= t_dir,e + max(20 ms, sqrt(V) ms) at which the Hann window
// [t_dir,e + 2.5 ms, t] has an expected energy-weighted effective number of arrivals k_eff >= 19:
//
//     k_eff = (4 pi c^3 / V) (int w dt)^2 / int w(t)^2 / t^2 dt,
//
// w the Hann taper over the window, t measured from emission, c = 343 m/s, V in m^3. This is
// (sum x)^2 / sum x^2 of the arrivals' weights x_i = w(t_i) / t_i^2 (energy 1/r^2) under Cremer's
// reflection density dN/dt = 4 pi c^3 t^2 / V (Blauert Ch. 3 §3.3; Vorlaender Eqs. 11.8, 11.20,
// 11.50), and k_eff >= 19 is a level estimate with sigma <= 4.34 / sqrt(19) = 1 dB (Vorlaender
// Eqs. 11.9 / 11.17). The corpus gives no rule for the transition time (Vorlaender §11.7); this one
// is chosen for accuracy (PRD NFR-1) and a well-conditioned level estimate, and the Expert may revise
// it. The lower bound keeps the widely used estimate of the perceptual mixing time, sqrt(V) ms
// (Rubak & Johansen 1999, "Artificial reverberation based on a pseudo-random impulse response II",
// AES 106th Convention; also Lindau, Kosanke & Weinzierl 2012, JAES 60(11)) and 20 ms, counted from
// the emitter's own direct sound. For t_dir,e -> 0 the k_eff criterion alone gives roughly
// 6.8 V^(1/3) ms.
namespace sim::tail {

inline constexpr double kMixingMinAfterDirectS = 0.020;         // 20 ms
inline constexpr double kMatchWindowStartAfterDirectS = 0.0025; // window starts 2.5 ms after t_dir
inline constexpr double kMixingMinKeff = 19.0;
inline constexpr double kCrossfadeHalfS = 0.0025; // ISM -> tail crossfade [t_mix - 2.5 ms, t_mix + 2.5 ms]

// Expected energy-weighted k_eff of the Hann window [startS, endS] (times from emission, s) in a
// room of volume V (formula above). 0 for an empty window.
double expectedKeff(double startS, double endS, double volumeM3) noexcept;

// sigma_dB = 4.34 / sqrt(k_eff) (10 / ln 10 / sqrt(k_eff)): the expected precision of a level
// estimated from k_eff Poisson-like arrivals (Vorlaender Eqs. 11.9 / 11.17).
double expectedSigmaDb(double keff) noexcept;

struct MixingTime
{
    double directS = 0.0;      // t_dir,e: the emitter's direct arrival from emission (before AX1)
    double lowerBoundS = 0.0;  // t_dir,e + max(20 ms, sqrt(V) ms)
    double windowStartS = 0.0; // t_dir,e + 2.5 ms
    double mixS = 0.0;         // t_mix,e (the window ends here)
    double expectedKeff = 0.0; // k_eff of [windowStartS, mixS], >= 19
};

// t_mix,e for an emitter whose direct sound arrives at directS (from emission) in a room of volume
// V. Deterministic: bisection to a fixed number of iterations.
MixingTime mixingTime(double directS, double volumeM3);

} // namespace sim::tail
