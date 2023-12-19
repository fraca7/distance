
#ifndef _FRACA7_DISTANCE_HPP
#define _FRACA7_DISTANCE_HPP

#include <ratio>
#include <cstdint>
#include <type_traits>

namespace fraca7
{
  template <typename _Rep, typename _Prec=std::ratio<1>> struct distance;

  template <intmax_t N, intmax_t D> struct static_pgcd : static_pgcd<D, N % D>
  {
    static_assert(D > 0, "Denominator must be > 0");
    static_assert(N >= 0, "Numerator must be >= 0");
  };
  template <intmax_t N> struct static_pgcd<N, 0>
  {
    static constexpr intmax_t value = N;
  };
}

namespace std
{
  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> struct common_type<fraca7::distance<_Rep1, _Prec1>, fraca7::distance<_Rep2, _Prec2>>
  {
  private:
    static constexpr intmax_t __p = fraca7::static_pgcd<_Prec1::num, _Prec2::num>::value;
    static constexpr intmax_t __q = fraca7::static_pgcd<_Prec1::den, _Prec2::den>::value;
    static constexpr intmax_t __d1 = _Prec1::den / __q;
    static constexpr intmax_t __d2 = _Prec2::den / __q;

  public:
    typedef fraca7::distance<typename common_type<_Rep1, _Rep2>::type, typename ratio<__p, __q * __d1 * __d2>::type> type;
  };
}

namespace fraca7
{
  template <typename _T> struct __is_distance : public std::false_type {
  };
  template<typename _Rep, typename _Prec> struct __is_distance<distance<_Rep, _Prec>> : public std::true_type {
  };

  template <typename _To, typename _From, typename=typename std::enable_if<__is_distance<_To>::value && __is_distance<_From>::value>::type> inline _To distance_cast(const _From& d) {
    typedef typename std::ratio_divide<typename _From::precision, typename _To::precision>::type __r;

    return _To(d.count()) * __r::num / __r::den;
  }

  template <typename _Rep, typename _Prec> struct distance
  {
  public:
    typedef _Rep rep;
    typedef _Prec precision;

    template <typename _Rep2> using as = distance<_Rep2, _Prec>;

    constexpr distance()
      : m_count() {
    }

    constexpr distance(const distance&) = default;

    template <typename _Rep2, typename=typename std::enable_if<std::is_convertible<_Rep2, _Rep>::value && !(std::is_floating_point<_Rep2>::value && !std::is_floating_point<_Rep>::value)>::type> constexpr explicit distance(_Rep2 d)
      : m_count(static_cast<_Rep>(d)) {
    }

    template <typename _Rep2, typename _Prec2, typename=typename std::enable_if<std::is_floating_point<_Rep>::value || ((std::ratio_divide<_Prec2, _Prec>::type::den == 1) && !std::is_floating_point<_Rep2>::value)>::type> constexpr distance(const distance<_Rep2, _Prec2>& d)
      : m_count(distance_cast<distance<_Rep, _Prec>>(d).count()) {
    }

    distance& operator=(const distance&) = default;

    // Accessors

    constexpr _Rep count() const {
      return m_count;
    }

    constexpr intmax_t num() const {
      return _Prec::num;
    }

    constexpr intmax_t den() const {
      return _Prec::den;
    }

    // Arithmetic

    constexpr distance operator+() const {
      return *this;
    }

    constexpr distance operator-() const {
      return distance(-m_count);
    }

    distance& operator++() {
      ++m_count;
      return *this;
    }

    distance operator++(int) {
      return distance(m_count++);
    }

    distance& operator--() {
      --m_count;
      return *this;
    }

    distance operator--(int) {
      return distance(m_count--);
    }

    distance& operator+=(const distance& d) {
      m_count += d.count();
      return *this;
    }

    distance& operator-=(const distance& d) {
      m_count -= d.count();
      return *this;
    }

    distance& operator*=(_Rep v) {
      m_count *= v;
      return *this;
    }

    distance& operator/=(_Rep v) {
      m_count /= v;
      return *this;
    }

    template <typename _Rep2=_Rep, typename=typename std::enable_if<!std::is_floating_point<_Rep2>::value>::type> distance& operator%=(_Rep v) {
      m_count %= v;
      return *this;
    }

    template<typename _Rep2=_Rep, typename=typename std::enable_if<!std::is_floating_point<_Rep2>::value>::type> distance& operator%=(const distance& d) {
      m_count %= d.count();
      return *this;
    }

  private:
    _Rep m_count;
  };

  // Arithmetic, part 2

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type operator+(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1) += d2;
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type operator-(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1) -= d2;
  }

  template <typename _Rep, typename _Prec, typename _Rep2> inline distance<typename std::common_type<_Rep, _Rep2>::type, _Prec> operator*(const distance<_Rep, _Prec>& d, const _Rep2& v) {
    return distance<typename std::common_type<_Rep, _Rep2>::type, _Prec>(d) *= v;
  }

  template <typename _Rep, typename _Prec, typename _Rep2> inline distance<typename std::common_type<_Rep, _Rep2>::type, _Prec> operator*(const _Rep2& v, const distance<_Rep, _Prec>& d) {
    return d * v;
  }

  template <typename _Rep, typename _Prec, typename _Rep2> inline distance<typename std::common_type<_Rep, _Rep2>::type, _Prec> operator/(const distance<_Rep, _Prec>& d, const _Rep2& v) {
    typedef typename std::common_type<_Rep, _Rep2>::type __ct;
    return distance<__ct, _Prec>(__ct(d.count()) / v);
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline typename std::common_type<_Rep1, _Rep2>::type operator/(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1).count() / __ct(d2).count();
  }

  template <typename _Rep, typename _Prec, typename _Rep2> inline distance<typename std::common_type<_Rep, _Rep2>::type, _Prec> operator%(const distance<_Rep, _Prec>& d, const _Rep2& v) {
    return distance<typename std::common_type<_Rep, _Rep2>::type, _Prec>(d) %= v;
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type operator%(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1) %= __ct(d2);
  }

  // Comparisons

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator==(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1).count() == __ct(d2).count();
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator!=(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    return !(d1 == d2);
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator<(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    typedef typename std::common_type<distance<_Rep1, _Prec1>, distance<_Rep2, _Prec2>>::type __ct;
    return __ct(d1).count() < __ct(d2).count();
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator<=(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    return !(d2 > d1);
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator>(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    return d2 < d1;
  }

  template <typename _Rep1, typename _Prec1, typename _Rep2, typename _Prec2> inline bool operator>=(const distance<_Rep1, _Prec1>& d1, const distance<_Rep2, _Prec2>& d2) {
    return !(d1 < d2);
  }

  // SI units
  typedef distance<intmax_t, std::nano> nanometers;
  typedef distance<intmax_t, std::micro> micrometers;
  typedef distance<intmax_t, std::milli> millimeters;
  typedef distance<intmax_t, std::centi> centimeters;
  typedef distance<intmax_t, std::deci> decimeters;
  typedef distance<intmax_t> meters;
  typedef distance<intmax_t, std::deca> decameters;
  typedef distance<intmax_t, std::hecto> hectometers;
  typedef distance<intmax_t, std::kilo> kilometers;

  // Generally accepted aliases
  using microns = micrometers;
  typedef distance<intmax_t, std::ratio<1, 10000000000>> angstrom;

  // MURICA
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<1, 17280>>> twips;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<1, 12000>>> thous;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<1, 36>>> barleycorns;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<1, 12>>> inches;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<1, 3>>> hands;
  typedef distance<intmax_t, std::ratio<3048, 10000>> feet;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<3, 1>>> yards;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<66, 1>>> chains;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<660, 1>>> furlongs;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<5280, 1>>> miles;
  typedef distance<intmax_t, std::ratio_multiply<std::ratio<3048, 10000>, std::ratio<15840, 1>>> leagues;

  // Now this is getting silly
  // Source: SMBC's bookmark "The indispensable list of highly useful unit conversions"
  typedef distance<intmax_t, std::ratio<9, 20>> cubits;
  typedef distance<intmax_t, std::ratio<10000000, 324077927>> attoparsecs;
  // Alas no siriometers, intmax_t cannot hold 1e24
  typedef distance<intmax_t, std::ratio<1, 200000000>> beard_seconds;
  typedef distance<intmax_t, std::ratio<1000000000000000, 3335641>> light_seconds;
}

#endif /* _FRACA7_DISTANCE_HPP */
