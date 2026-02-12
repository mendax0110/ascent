#pragma once

#include <cstdint>
#include <array>
#include "ascent/core/types.h"
#include "ascent/core/config.h"

/// @brief Cooperative time-triggered scheduler. \namespace ascent::core
namespace ascent::core
{
    using TaskFunc = void(*)();

    /// Task descriptor structure for scheduler. \struct TaskDescriptor
    struct TaskDescriptor
    {
        const char* name = nullptr;
        TaskFunc func = nullptr;
        Priority priority = Priority::Normal;
        uint32_t period_ms = 0;
        uint32_t last_run_ms = 0;
        bool enabled = false;
    };

    /**
     * \class Scheduler
     * @brief Cooperative time-triggered scheduler.
     *
     * Runs tasks based on their period and priority.
     * Fixed capacity, no dynamic allocation.
     */
    class Scheduler
    {
    public:
        Scheduler() = default;
        ~Scheduler() = default;

        Scheduler(const Scheduler&) = delete;
        Scheduler& operator=(const Scheduler&) = delete;
        Scheduler(Scheduler&&) = delete;
        Scheduler& operator=(Scheduler&&) = delete;

        /**
         * @brief Register a periodic task.
         * @param name Human-readable task name.
         * @param func Task function pointer.
         * @param period_ms Execution period in milliseconds.
         * @param priority Task priority.
         * @return Ok on success, OutOfMemory if task limit reached.
         */
        StatusCode addTask(const char* name, TaskFunc func, uint32_t period_ms, Priority priority = Priority::Normal) noexcept;

        /**
         * @brief Run one scheduler tick. Executes all due tasks.
         * @param now_ms Current system time in milliseconds.
         */
        void tick(uint32_t now_ms) noexcept;

        /**
         * @brief Enable or disable a task by name.
         * @param name Task name.
         * @param enabled True to enable, false to disable.
         * @return Ok if task found, Error if not found.
         */
        StatusCode setTaskEnabled(const char* name, bool enabled) noexcept;

        /**
         * @brief Get number of registered tasks.
         * @return Number of registered tasks.
         */
        uint32_t getTaskCount() const noexcept;

    private:
        std::array<TaskDescriptor, Config::kMaxTasks> m_tasks = {};
        uint32_t m_task_count = 0;
    };
} // namespace ascent::core
