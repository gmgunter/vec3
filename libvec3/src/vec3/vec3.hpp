#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <type_traits>

namespace vec3 {

/**
 * A vector in Cartesian 3-space.
 *
 * @tparam T element type
 */
template<class T>
class Vec3 {
    static_assert(std::numeric_limits<T>::is_specialized,
                  "T must be an arithmetic type");

public:
    using value_type = T;

    /** Default constructor. Value-initializes each element. */
    Vec3() = default;

    /**
     * Construct a new `Vec3` object.
     *
     * @param[in] x - the x component
     * @param[in] y - the y component
     * @param[in] z - the z component
     */
    constexpr Vec3(const T& x, const T& y, const T& z) noexcept
        : x_{x}, y_{y}, z_{z}
    {}

    Vec3(const Vec3&) = default;

    /**
     * Converting constructor. Constructs a new `Vec3` object from a `Vec3` of a
     * different type.
     *
     * @param[in] other - another vector
     */
    template<class U>
    constexpr Vec3(const Vec3<U>& other) noexcept
        : x_{static_cast<T>(other.x())},
          y_{static_cast<T>(other.y())},
          z_{static_cast<T>(other.z())}
    {}

    /** Get the x component. */
    [[nodiscard]] constexpr const T&
    x() const noexcept
    {
        return x_;
    }

    /** Set the x component. */
    constexpr void
    x(const T& x) noexcept
    {
        x_ = x;
    }

    /** Get the y component. */
    [[nodiscard]] constexpr const T&
    y() const noexcept
    {
        return y_;
    }

    /** Set the y component. */
    constexpr void
    y(const T& y) noexcept
    {
        y_ = y;
    }

    /** Get the z component. */
    [[nodiscard]] constexpr const T&
    z() const noexcept
    {
        return z_;
    }

    /** Set the z component. */
    constexpr void
    z(const T& z) noexcept
    {
        z_ = z;
    }

    /**
     * Computes the Euclidean norm of the vector, \f$\sqrt{x^2 + y^2 + z^2}\f$.
     *
     * @note
     * The implementation is intended to avoid undue overflow or underflow at
     * intermediate steps of the computation and therefore may be less efficient
     * than a naive approach.
     */
    [[nodiscard]] T
    norm() const
    {
        return std::hypot(x(), y(), z());
    }

    /** Computes the squared magnitude of the vector, \f$x^2 + y^2 + z^2\f$. */
    [[nodiscard]] constexpr T
    squared_norm() const noexcept
    {
        return x() * x() + y() * y() + z() * z();
    }

    [[nodiscard]] constexpr Vec3
    operator+() const noexcept
    {
        return *this;
    }

    [[nodiscard]] constexpr Vec3
    operator-() const noexcept
    {
        return Vec3{-x(), -y(), -z()};
    }

    constexpr Vec3& operator+=(const Vec3& other) noexcept {

        x_ += other.x();
        y_ += other.y();
        z_ += other.z();
        return *this;
    }

    constexpr Vec3&
    operator-=(const Vec3& other) noexcept
    {
        x_ -= other.x();
        y_ -= other.y();
        z_ -= other.z();
        return *this;
    }

    constexpr Vec3&
    operator*=(const T& other) noexcept
    {
        x_ *= other;
        y_ *= other;
        z_ *= other;
        return *this;
    }

    constexpr Vec3&
    operator/=(const T& other) noexcept
    {
        x_ /= other;
        y_ /= other;
        z_ /= other;
        return *this;
    }

    [[nodiscard]] friend constexpr Vec3
    operator+(const Vec3& lhs, const Vec3& rhs) noexcept
    {
        auto out = lhs;
        out += rhs;
        return out;
    }

    [[nodiscard]] friend constexpr Vec3
    operator-(const Vec3& lhs, const Vec3& rhs) noexcept
    {
        auto out = lhs;
        out -= rhs;
        return out;
    }

    [[nodiscard]] friend constexpr Vec3
    operator*(const Vec3& lhs, const T& rhs) noexcept
    {
        auto out = lhs;
        out *= rhs;
        return out;
    }

    [[nodiscard]] friend constexpr Vec3
    operator*(const T& lhs, const Vec3& rhs) noexcept
    {
        auto out = rhs;
        out *= lhs;
        return out;
    }

    [[nodiscard]] friend constexpr Vec3
    operator/(const Vec3& lhs, const T& rhs) noexcept
    {
        auto out = lhs;
        out /= rhs;
        return out;
    }

    [[nodiscard]] friend constexpr bool
    operator==(const Vec3& lhs, const Vec3& rhs) noexcept
    {
        return (lhs.x() == rhs.x()) and (lhs.y() == rhs.y()) and
               (lhs.z() == rhs.z());
    }

    [[nodiscard]] friend constexpr bool
    operator!=(const Vec3& lhs, const Vec3& rhs) noexcept
    {
        return not(lhs == rhs);
    }

    /**
     * Writes a `Vec3` to an output stream in the form `(x,y,z)`.
     *
     * @param[in,out] os an output stream
     * @param[in] v the vector to be inserted
     */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const Vec3& v)
    {
        std::basic_ostringstream<CharT, Traits> s;
        s.flags(os.flags());
        s.imbue(os.getloc());
        s.precision(os.precision());
        s << '(' << v.x() << ',' << v.y() << ',' << v.z() << ')';
        return os << s.str();
    }

    /**
     * Reads a `Vec3` from an input stream. The expected format is `(x,y,z)`.
     *
     * @param[in,out] is an input stream
     * @param[out] v the vector to be extracted
     */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, Vec3& v)
    {
        if (is.good()) {
            std::ws(is);
            if (is.peek() == CharT{'('}) {
                is.get();
                T x;
                is >> x;
                if (!is.fail()) {
                    std::ws(is);
                    if (is.peek() == CharT{','}) {
                        is.get();
                        T y;
                        is >> y;
                        if (!is.fail()) {
                            std::ws(is);
                            if (is.peek() == CharT{','}) {
                                is.get();
                                T z;
                                is >> z;
                                if (!is.fail()) {
                                    std::ws(is);
                                    if (is.peek() == CharT{')'}) {
                                        is.get();
                                        v = Vec3{x, y, z};
                                        return is;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        is.setstate(std::ios_base::failbit);
        return is;
    }

private:
    T x_ = {};
    T y_ = {};
    T z_ = {};
};

/**
 * Computes the dot product of two vectors.
 *
 * @param[in] a first vector
 * @param[in] b second vector
 * @returns the dot product of `a` and `b`
 */
template<class T, class U>
[[nodiscard]] constexpr std::common_type_t<T, U>
dot(const Vec3<T>& a, const Vec3<U>& b) noexcept
{
    using V = std::common_type_t<T, U>;
    const auto xx = static_cast<V>(a.x()) * static_cast<V>(b.x());
    const auto yy = static_cast<V>(a.y()) * static_cast<V>(b.y());
    const auto zz = static_cast<V>(a.z()) * static_cast<V>(b.z());
    return xx + yy + zz;
}

} // namespace vec3
