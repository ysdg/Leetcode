#include <coroutine>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <thread>
#include <boost/coroutine2/all.hpp>

template<typename T>
struct CGenerator
{
    // 类名 'CGenerator' 只是我们的选择，使用协程魔法不依赖它
    // 编译器通过关键词 'co_yield' 的存在识别协程
    // 你可以使用 'MyGenerator' （或者任何别的名字）作为替代
    // 只要你在类中包括了拥有
    // 'MyGenerator get_return_object()' 方法的嵌套类 promise_type
    // （注意：在重命名时，你还需要调整构造函数/析构函数的名字）
 
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
 
    struct promise_type // 必要
    {
        T value_;
        std::exception_ptr exception_;
 
        CGenerator get_return_object()
        {
            return CGenerator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception_ = std::current_exception(); } // 保存异常
 
        template <std::convertible_to<T> From> // C++20 概念
        std::suspend_always yield_value(From&& from)
        {
            value_ = std::forward<From>(from); // 在承诺中缓存结果
            return {};
        }
		std::suspend_never return_value(T v)
		{
			value_ = v;
			return {};
		}
        // void return_void() {}
    };
 
    handle_type h_;
 
    CGenerator(handle_type h)
        : h_(h)
    {
    }
    ~CGenerator() { h_.destroy(); }
    explicit operator bool()
    {
        fill(); // 获知协程是结束了还是仍能通过 C++ getter（下文的 operator ()）
                // 获得下一个值的唯一方式是执行/恢复协程到下一个 co_yield 节点
                // （或让执行流抵达结尾）
                // 我们在承诺中存储/缓存了执行结果，使得 getter（下文的 operator ()）
                // 可以获得这一结果而不执行协程
        return !h_.done();
    }
    T operator()()
    {
        fill();
        full_ = false;// 我们将移动走先前缓存的结果来重新置空承诺
        return std::move(h_.promise().value_);
    }
 
private:
    bool full_ = false;
 
    void fill()
    {
        if (!full_)
        {
            h_();
            if (h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            // 在调用上下文中传播协程异常
 
            full_ = true;
        }
    }
};

template<>
struct CGenerator<void>
{
    struct promise_type
    {
        CGenerator get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};


auto switch_to_new_thread(std::jthread& out)
{
    struct awaitable
    {
        std::jthread* p_out;
        bool await_ready() { return false; }
        void await_suspend(std::coroutine_handle<> h)
        {
            std::jthread& out = *p_out;
            if (out.joinable())
                throw std::runtime_error("Output jthread parameter not empty");
            out = std::jthread([h] { h.resume(); });
            // Potential undefined behavior: accessing potentially destroyed *this
            // std::cout << "New thread ID: " << p_out->get_id() << '\n';
            std::cout << "New thread ID: " << out.get_id() << '\n';
            // std::cout << "New thread ID: " << std::this_thread::get_id() << '\n'; // this is OK
        }
        void await_resume() {}
    };
    return awaitable{&out};
}

 
CGenerator<void> resuming_on_new_thread(std::jthread& out)
{
    std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
    co_await switch_to_new_thread(out);
    // awaiter destroyed here
    std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}
 
CGenerator<uint64_t> fibonacci_sequence(unsigned n)
{
    if (n == 0)
        co_return {};
 
    if (n > 94)
        throw std::runtime_error("斐波那契序列过大，元素将会溢出。");
 
    co_yield 0;
 
    if (n == 1)
        co_return 1;
 
    co_yield 1;
 
    if (n == 2)
        co_return 2;
 
    uint64_t a = 0;
    uint64_t b = 1;
 
    for (unsigned i = 2; i < n; i++)
    {
        uint64_t s = a + b;
        co_yield s;
        a = b;
        b = s;
    }
}
 
// int main()
// {
//     std::jthread out;
//     resuming_on_new_thread(out);
// }


int main()
{
    std::jthread out;
    resuming_on_new_thread(out);
    // try
    // {
    //     auto gen = fibonacci_sequence(10); // 最大值94，避免 uint64_t 溢出
 
    //     for (int j = 0; gen; j++)
    //         std::cout << "fib(" << j << ")=" << gen() << '\n';
    // }
    // catch (const std::exception& ex)
    // {
    //     std::cerr << "发生了异常：" << ex.what() << '\n';
    // }
    // catch (...)
    // {
    //     std::cerr << "未知异常。\n";
    // }
}