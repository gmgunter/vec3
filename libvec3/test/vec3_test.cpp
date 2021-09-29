#include <catch2/catch.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>
#include <vec3/vec3.hpp>

namespace {

TEST_CASE("vec3.value_type")
{
    const vec3::Vec3<float> vf;
    const vec3::Vec3<double> vd;

    CHECK((std::is_same<decltype(vf)::value_type, float>{}));
    CHECK((std::is_same<decltype(vd)::value_type, double>{}));
}

TEST_CASE("vec3.vec3")
{
    const vec3::Vec3<float> vf;

    CHECK(vf.x() == 0.0f);
    CHECK(vf.y() == 0.0f);
    CHECK(vf.z() == 0.0f);
}

TEST_CASE("vec3.vec3 (T,T,T)")
{
    const float x = 1.0f;
    const float y = 2.0f;
    const float z = 3.0f;

    const vec3::Vec3<float> v{x, y, z};

    CHECK(v.x() == x);
    CHECK(v.y() == y);
    CHECK(v.z() == z);
}

TEST_CASE("vec3.vec (Vec3<U>)")
{
    const auto vf = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};

    const vec3::Vec3<double> vd{vf};

    CHECK(vd.x() == static_cast<double>(vf.x()));
    CHECK(vd.y() == static_cast<double>(vf.y()));
    CHECK(vd.z() == static_cast<double>(vf.z()));
}

TEST_CASE("vec3.operator= (T[3])")
{
    const double x = 1.0;
    const double y = 2.0;
    const double z = 3.0;

    const vec3::Vec3<double> v = {x, y, z};

    CHECK(v.x() == x);
    CHECK(v.y() == y);
    CHECK(v.z() == z);
}

TEST_CASE("vec3.operator= (Vec3<U>)")
{
    const auto vf = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};

    const vec3::Vec3<double> vd = vf;

    CHECK(vd.x() == static_cast<double>(vf.x()));
    CHECK(vd.y() == static_cast<double>(vf.y()));
    CHECK(vd.z() == static_cast<double>(vf.z()));
}

TEST_CASE("vec3.{x|y|z}")
{
    auto v = vec3::Vec3<double>{1.0, 2.0, 3.0};

    const double x = 4.0;
    v.x(x);

    const double y = 5.0;
    v.y(y);

    const double z = 6.0;
    v.z(z);

    CHECK(v.x() == x);
    CHECK(v.y() == y);
    CHECK(v.z() == z);
}

TEST_CASE("vec3.norm")
{
    const auto v = vec3::Vec3<float>{1.0f, 2.0f, -2.0f};
    CHECK(v.norm() == Approx{3.0f});
}

TEST_CASE("vec3.squared_norm")
{
    const auto v = vec3::Vec3<double>{3.0, 4.0, 5.0};
    CHECK(v.squared_norm() == Approx{50.0});
}

TEST_CASE("vec3.operator+ (unary)")
{
    const auto v1 = vec3::Vec3<float>{1.0f, 2.0f, -3.0f};
    const auto v2 = +v1;

    CHECK(v2.x() == 1.0f);
    CHECK(v2.y() == 2.0f);
    CHECK(v2.z() == -3.0f);
}

TEST_CASE("vec3.operator- (unary)")
{
    const auto v1 = vec3::Vec3<float>{1.0f, 2.0f, -3.0f};
    const auto v2 = -v1;

    CHECK(v2.x() == -1.0f);
    CHECK(v2.y() == -2.0f);
    CHECK(v2.z() == 3.0f);
}

TEST_CASE("vec3.operator+=")
{
    auto v1 = vec3::Vec3<double>{1.0, 2.0, 3.0};
    const auto v2 = vec3::Vec3<double>{4.0, 5.0, 6.0};
    v1 += v2;

    CHECK(v1.x() == Approx{5.0});
    CHECK(v1.y() == Approx{7.0});
    CHECK(v1.z() == Approx{9.0});
}

TEST_CASE("vec3.operator-=")
{
    auto v1 = vec3::Vec3<double>{0.0, 2.0, 4.0};
    const auto v2 = vec3::Vec3<double>{1.0, 2.0, 3.0};
    v1 -= v2;

    CHECK(v1.x() == Approx{-1.0});
    CHECK(v1.y() == Approx{0.0});
    CHECK(v1.z() == Approx{1.0});
}

TEST_CASE("vec3.operator*=")
{
    auto v1 = vec3::Vec3<double>{1.0, 2.0, 3.0};
    v1 *= 2.0;

    CHECK(v1.x() == Approx{2.0});
    CHECK(v1.y() == Approx{4.0});
    CHECK(v1.z() == Approx{6.0});
}

TEST_CASE("vec3.operator/=")
{
    auto v1 = vec3::Vec3<double>{2.0, 4.0, 6.0};
    v1 /= 2.0;

    CHECK(v1.x() == Approx{1.0});
    CHECK(v1.y() == Approx{2.0});
    CHECK(v1.z() == Approx{3.0});
}

TEST_CASE("vec3.operator+ (binary)")
{
    const auto v1 = vec3::Vec3<double>{1.0, 2.0, 3.0};
    const auto v2 = vec3::Vec3<double>{4.0, 5.0, 6.0};
    const auto v3 = v1 + v2;

    CHECK(v3.x() == Approx{5.0});
    CHECK(v3.y() == Approx{7.0});
    CHECK(v3.z() == Approx{9.0});
}

TEST_CASE("vec3.operator- (binary)")
{
    const auto v1 = vec3::Vec3<double>{0.0, 2.0, 4.0};
    const auto v2 = vec3::Vec3<double>{1.0, 2.0, 3.0};
    const auto v3 = v1 - v2;

    CHECK(v3.x() == Approx{-1.0});
    CHECK(v3.y() == Approx{0.0});
    CHECK(v3.z() == Approx{1.0});
}

TEST_CASE("vec3.operator*")
{
    const auto v1 = vec3::Vec3<double>{1.0, 2.0, 3.0};

    const auto v2 = 2.0 * v1;
    CHECK(v2.x() == Approx{2.0});
    CHECK(v2.y() == Approx{4.0});
    CHECK(v2.z() == Approx{6.0});

    const auto v3 = v1 * 2.0;
    CHECK(v3.x() == Approx{2.0});
    CHECK(v3.y() == Approx{4.0});
    CHECK(v3.z() == Approx{6.0});
}

TEST_CASE("vec3.operator/")
{
    const auto v1 = vec3::Vec3<double>{2.0, 4.0, 6.0};
    const auto v2 = v1 / 2.0;

    CHECK(v2.x() == Approx{1.0});
    CHECK(v2.y() == Approx{2.0});
    CHECK(v2.z() == Approx{3.0});
}

TEST_CASE("vec3.operator==")
{
    const auto v1 = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};
    const auto v2 = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};

    const auto v3 = vec3::Vec3<float>{1.1f, 2.0f, 3.0f};
    const auto v4 = vec3::Vec3<float>{1.0f, 2.1f, 3.0f};
    const auto v5 = vec3::Vec3<float>{1.0f, 2.0f, 3.1f};

    CHECK(v1 == v2);
    CHECK_FALSE(v1 == v3);
    CHECK_FALSE(v1 == v4);
    CHECK_FALSE(v1 == v5);
}

TEST_CASE("vec3.operator!=")
{
    const auto v1 = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};
    const auto v2 = vec3::Vec3<float>{1.0f, 2.0f, 3.0f};

    const auto v3 = vec3::Vec3<float>{1.1f, 2.0f, 3.0f};
    const auto v4 = vec3::Vec3<float>{1.0f, 2.1f, 3.0f};
    const auto v5 = vec3::Vec3<float>{1.0f, 2.0f, 3.1f};

    CHECK_FALSE(v1 != v2);
    CHECK(v1 != v3);
    CHECK(v1 != v4);
    CHECK(v1 != v5);
}

TEST_CASE("vec3.operator<<")
{
    const auto v = vec3::Vec3<double>{1.0, 2.0, 3.0};
    std::ostringstream s;
    s << std::setprecision(2) << std::showpoint << v;

    CHECK(s.good());
    CHECK(s.str() == "(1.0,2.0,3.0)");
}

TEST_CASE("vec3.operator>>")
{
    {
        auto s = std::istringstream{"(1.0,2.0,3.0)"};
        vec3::Vec3<double> v;
        s >> v;

        CHECK(s.good());
        CHECK(v.x() == Approx{1.0});
        CHECK(v.y() == Approx{2.0});
        CHECK(v.z() == Approx{3.0});
    }

    {
        auto s = std::istringstream{"( 1, 2, 3 )"};
        vec3::Vec3<double> v;
        s >> v;

        CHECK(s.good());
        CHECK(v.x() == Approx{1.0});
        CHECK(v.y() == Approx{2.0});
        CHECK(v.z() == Approx{3.0});
    }

    {
        auto s = std::istringstream{""};
        vec3::Vec3<double> v;
        s >> v;

        CHECK(s.fail());
    }

    {
        auto s = std::istringstream{"(1.0,2.0)"};
        vec3::Vec3<double> v;
        s >> v;

        CHECK(s.fail());
    }

    {
        auto s = std::istringstream{"(a,b,c)"};
        vec3::Vec3<double> v;
        s >> v;

        CHECK(s.fail());
    }
}

TEST_CASE("vec3.dot")
{
    const auto v1 = vec3::Vec3<float>{-1.0f, 0.0f, 1.0f};
    const auto v2 = vec3::Vec3<double>{1.0, 2.0, 3.0};

    auto d12 = vec3::dot(v1, v2);
    CHECK((std::is_same<decltype(d12), double>{}));
    CHECK(d12 == Approx{2.0});

    auto d21 = vec3::dot(v2, v1);
    CHECK((std::is_same<decltype(d21), double>{}));
    CHECK(d21 == Approx{2.0});
}

} // namespace
