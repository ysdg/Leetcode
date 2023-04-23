#include <coroutine>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <thread>
#include <boost/coroutine2/all.hpp>

template<typename T>
struct CGenerator
{
    // ���� 'CGenerator' ֻ�����ǵ�ѡ��ʹ��Э��ħ����������
    // ������ͨ���ؼ��� 'co_yield' �Ĵ���ʶ��Э��
    // �����ʹ�� 'MyGenerator' �������κα�����֣���Ϊ���
    // ֻҪ�������а�����ӵ��
    // 'MyGenerator get_return_object()' ������Ƕ���� promise_type
    // ��ע�⣺��������ʱ���㻹��Ҫ�������캯��/�������������֣�
 
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
 
    struct promise_type // ��Ҫ
    {
        T value_;
        std::exception_ptr exception_;
 
        CGenerator get_return_object()
        {
            return CGenerator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { exception_ = std::current_exception(); } // �����쳣
 
        template <std::convertible_to<T> From> // C++20 ����
        std::suspend_always yield_value(From&& from)
        {
            value_ = std::forward<From>(from); // �ڳ�ŵ�л�����
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
        fill(); // ��֪Э���ǽ����˻�������ͨ�� C++ getter�����ĵ� operator ()��
                // �����һ��ֵ��Ψһ��ʽ��ִ��/�ָ�Э�̵���һ�� co_yield �ڵ�
                // ������ִ�����ִ��β��
                // �����ڳ�ŵ�д洢/������ִ�н����ʹ�� getter�����ĵ� operator ()��
                // ���Ի����һ�������ִ��Э��
        return !h_.done();
    }
    T operator()()
    {
        fill();
        full_ = false;// ���ǽ��ƶ�����ǰ����Ľ���������ÿճ�ŵ
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
            // �ڵ����������д���Э���쳣
 
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
        throw std::runtime_error("쳲��������й���Ԫ�ؽ��������");
 
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
    //     auto gen = fibonacci_sequence(10); // ���ֵ94������ uint64_t ���
 
    //     for (int j = 0; gen; j++)
    //         std::cout << "fib(" << j << ")=" << gen() << '\n';
    // }
    // catch (const std::exception& ex)
    // {
    //     std::cerr << "�������쳣��" << ex.what() << '\n';
    // }
    // catch (...)
    // {
    //     std::cerr << "δ֪�쳣��\n";
    // }
}