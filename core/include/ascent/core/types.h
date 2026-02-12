#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>

/// @brief Core type definitions and utilities. \namespace ascent::core
namespace ascent::core
{

    /// @brief Standard status codes for function return values. \enum StatusCode
    enum class StatusCode : uint8_t
    {
        Ok = 0,
        Error,
        Timeout,
        Busy,
        InvalidParam,
        NotInitialized,
        HardwareFault,
        OutOfMemory,
        NotSupported
    };

    /**
     * \struct Result
     * @brief Lightweight result type for error handling without exceptions.
     * @tparam T Value type on success.
     */
    template <typename T>
    struct Result
    {
        StatusCode status;
        T value;

        /**
         * @brief Check if result is successful.
         * @return True if status is Ok, false otherwise.
         */
        [[nodiscard]] bool ok() const noexcept
        {
            return status == StatusCode::Ok;
        }

        /**
         * @brief Create a success result.
         * @param val Value to return on success.
         * @return Result with success status and value.
         */
        static Result success(T val) noexcept
        {
            return {StatusCode::Ok, val};
        }

        /**
         * @brief Create an error result.
         * @param code Error status code.
         * @return Result with error status.
         */
        static Result error(StatusCode code) noexcept
        {
            return {code, T{}};
        }
    };

    /**
     * \struct Result<void>
     * @brief Specialization for void results.
     */
    template <>
    struct Result<void>
    {
        StatusCode status;

        /**
         * @brief Check if result is successful.
         * @return True if status is Ok, false otherwise.
         */
        [[nodiscard]] bool ok() const noexcept
        {
            return status == StatusCode::Ok;
        }

        /**
         * @brief Create a success result.
         * @return Result with success status.
         */
        static Result success() noexcept
        {
            return {StatusCode::Ok};
        }

        /**
         * @brief Create an error result.
         * @param code Error status code.
         * @return Result with error status.
         */
        static Result error(StatusCode code) noexcept
        {
            return {code};
        }
    };

    /// @brief 3D vector for position, velocity, etc. \struct Vec3f
    struct Vec3f
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vec3f operator+(const Vec3f& rhs) const noexcept
        {
            return {x + rhs.x, y + rhs.y, z + rhs.z};
        }

        Vec3f operator-(const Vec3f& rhs) const noexcept
        {
            return {x - rhs.x, y - rhs.y, z - rhs.z};
        }

        Vec3f operator*(float s) const noexcept
        {
            return {x * s, y * s, z * s};
        }
    };

    /// @brief Quaternion for orientation representation. \struct Quaternion
    struct Quaternion
    {
        float w = 1.0f;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        /**
         * @brief Return identity quaternion.
         */
        static Quaternion identity() noexcept
        {
            return {1.0f, 0.0f, 0.0f, 0.0f};
        }
    };

    using Timestamp_us = uint64_t;
    using Duration_ms = uint32_t;

    /// @brief Task priority levels for scheduler. \enum Priority
    enum class Priority : uint8_t
    {
        Critical = 0,
        High = 1,
        Normal = 2,
        Low = 3,
        Idle = 4
    };
} // namespace ascent::core
