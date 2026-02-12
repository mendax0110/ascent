#include <gtest/gtest.h>
#include "ascent/core/types.h"

using namespace ascent::core;

TEST(StatusCode, OkIsZero)
{
    EXPECT_EQ(static_cast<uint8_t>(StatusCode::Ok), 0);
}

TEST(ResultT, SuccessHoldsValue)
{
    auto r = Result<int>::success(42);
    EXPECT_TRUE(r.ok());
    EXPECT_EQ(r.value, 42);
    EXPECT_EQ(r.status, StatusCode::Ok);
}

TEST(ResultT, ErrorHoldsCode)
{
    auto r = Result<int>::error(StatusCode::Timeout);
    EXPECT_FALSE(r.ok());
    EXPECT_EQ(r.status, StatusCode::Timeout);
}

TEST(ResultT, DefaultValue)
{
    auto r = Result<float>::error(StatusCode::Error);
    EXPECT_FLOAT_EQ(r.value, 0.0f);
}

TEST(ResultVoid, SuccessIsOk)
{
    auto r = Result<void>::success();
    EXPECT_TRUE(r.ok());
    EXPECT_EQ(r.status, StatusCode::Ok);
}

TEST(ResultVoid, ErrorHoldsCode)
{
    auto r = Result<void>::error(StatusCode::HardwareFault);
    EXPECT_FALSE(r.ok());
    EXPECT_EQ(r.status, StatusCode::HardwareFault);
}

TEST(Vec3f, DefaultConstruction)
{
    Vec3f v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vec3f, Addition)
{
    Vec3f a{1.0f, 2.0f, 3.0f};
    Vec3f b{4.0f, 5.0f, 6.0f};
    auto c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
}

TEST(Vec3f, Subtraction)
{
    Vec3f a{5.0f, 7.0f, 9.0f};
    Vec3f b{1.0f, 2.0f, 3.0f};
    auto c = a - b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 5.0f);
    EXPECT_FLOAT_EQ(c.z, 6.0f);
}

TEST(Vec3f, ScalarMultiplication)
{
    Vec3f v{2.0f, 3.0f, 4.0f};
    auto r = v * 2.0f;
    EXPECT_FLOAT_EQ(r.x, 4.0f);
    EXPECT_FLOAT_EQ(r.y, 6.0f);
    EXPECT_FLOAT_EQ(r.z, 8.0f);
}

TEST(Vec3f, MultiplyByZero)
{
    Vec3f v{1.0f, 2.0f, 3.0f};
    auto r = v * 0.0f;
    EXPECT_FLOAT_EQ(r.x, 0.0f);
    EXPECT_FLOAT_EQ(r.y, 0.0f);
    EXPECT_FLOAT_EQ(r.z, 0.0f);
}

TEST(Quaternion, DefaultIsIdentity)
{
    Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(Quaternion, IdentityFactory)
{
    auto q = Quaternion::identity();
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
