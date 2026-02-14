#include <gtest/gtest.h>
#include "ascent/core/types.h"

using namespace ascent::core;

TEST(StatusCode, OkIsZero)
{
    EXPECT_EQ(static_cast<uint8_t>(StatusCode::Ok), 0);
}

TEST(ResultT, SuccessHoldsValue)
{
    const auto r = Result<int>::success(42);
    EXPECT_TRUE(r.ok());
    EXPECT_EQ(r.value, 42);
    EXPECT_EQ(r.status, StatusCode::Ok);
}

TEST(ResultT, ErrorHoldsCode)
{
    const auto r = Result<int>::error(StatusCode::Timeout);
    EXPECT_FALSE(r.ok());
    EXPECT_EQ(r.status, StatusCode::Timeout);
}

TEST(ResultT, DefaultValue)
{
    const auto r = Result<float>::error(StatusCode::Error);
    EXPECT_FLOAT_EQ(r.value, 0.0f);
}

TEST(ResultVoid, SuccessIsOk)
{
    const auto r = Result<void>::success();
    EXPECT_TRUE(r.ok());
    EXPECT_EQ(r.status, StatusCode::Ok);
}

TEST(ResultVoid, ErrorHoldsCode)
{
    const auto r = Result<void>::error(StatusCode::HardwareFault);
    EXPECT_FALSE(r.ok());
    EXPECT_EQ(r.status, StatusCode::HardwareFault);
}

TEST(Vec3f, DefaultConstruction)
{
    constexpr Vec3f v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vec3f, Addition)
{
    constexpr Vec3f a{1.0f, 2.0f, 3.0f};
    constexpr Vec3f b{4.0f, 5.0f, 6.0f};
    const auto c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
}

TEST(Vec3f, Subtraction)
{
    constexpr Vec3f a{5.0f, 7.0f, 9.0f};
    constexpr Vec3f b{1.0f, 2.0f, 3.0f};
    const auto c = a - b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 5.0f);
    EXPECT_FLOAT_EQ(c.z, 6.0f);
}

TEST(Vec3f, ScalarMultiplication)
{
    constexpr Vec3f v{2.0f, 3.0f, 4.0f};
    const auto r = v * 2.0f;
    EXPECT_FLOAT_EQ(r.x, 4.0f);
    EXPECT_FLOAT_EQ(r.y, 6.0f);
    EXPECT_FLOAT_EQ(r.z, 8.0f);
}

TEST(Vec3f, MultiplyByZero)
{
    constexpr Vec3f v{1.0f, 2.0f, 3.0f};
    const auto r = v * 0.0f;
    EXPECT_FLOAT_EQ(r.x, 0.0f);
    EXPECT_FLOAT_EQ(r.y, 0.0f);
    EXPECT_FLOAT_EQ(r.z, 0.0f);
}

TEST(Quaternion, DefaultIsIdentity)
{
    constexpr Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(Quaternion, IdentityFactory)
{
    const auto q = Quaternion::identity();
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(Priority, CriticalIsHighest)
{
    EXPECT_LT(static_cast<uint8_t>(Priority::Critical), static_cast<uint8_t>(Priority::Normal));
}

TEST(Priority, Ordering)
{
    EXPECT_LT(static_cast<uint8_t>(Priority::Critical), static_cast<uint8_t>(Priority::High));
    EXPECT_LT(static_cast<uint8_t>(Priority::High), static_cast<uint8_t>(Priority::Normal));
    EXPECT_LT(static_cast<uint8_t>(Priority::Normal), static_cast<uint8_t>(Priority::Low));
    EXPECT_LT(static_cast<uint8_t>(Priority::Low), static_cast<uint8_t>(Priority::Idle));
}
