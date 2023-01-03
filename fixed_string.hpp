template<auto N>
struct fixed_string
{
    constexpr fixed_string(const char(&arr)[N])
    {
        for (int i = 0; i < N; i++)
        {
            m_arr[i] = arr[i];
        }
    }

    char m_arr[N]{};
};