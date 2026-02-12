#include "scheduler.h"
#include <string_view>

using namespace ascent::core;

StatusCode Scheduler::addTask(const char* name, TaskFunc func, uint32_t period_ms, Priority priority) noexcept
{
    if (m_task_count >= Config::kMaxTasks)
    {
        return StatusCode::OutOfMemory;
    }
    if (func == nullptr || name == nullptr)
    {
        return StatusCode::InvalidParam;
    }

    auto& task = m_tasks[m_task_count];
    task.name = name;
    task.func = func;
    task.period_ms = period_ms;
    task.priority = priority;
    task.last_run_ms = 0u - period_ms;
    task.enabled = true;
    ++m_task_count;

    return StatusCode::Ok;
}

void Scheduler::tick(uint32_t now_ms) noexcept
{
    for (uint32_t i = 0; i < m_task_count; ++i)
    {
        auto& task = m_tasks[i];
        if (!task.enabled || task.func == nullptr)
        {
            continue;
        }

        const uint32_t elapsed = now_ms - task.last_run_ms;
        if (elapsed >= task.period_ms)
        {
            task.func();
            task.last_run_ms = now_ms;
        }
    }
}

StatusCode Scheduler::setTaskEnabled(const char* name, bool enabled) noexcept
{
    for (uint32_t i = 0; i < m_task_count; ++i)
    {
        if (std::string_view{m_tasks[i].name} == std::string_view{name})
        {
            m_tasks[i].enabled = enabled;
            return StatusCode::Ok;
        }
    }
    return StatusCode::InvalidParam;
}

uint32_t Scheduler::getTaskCount() const noexcept
{
    return m_task_count;
}
