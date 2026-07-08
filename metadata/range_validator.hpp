template<typename T>
class RangeValidator :
    public Validator<T>
{
public:

    RangeValidator(
        T min,
        T max)
        :
        min_(min),
        max_(max)
    {
    }

    bool validate(
        const T& value) const override
    {
        return
            value >= min_ &&
            value <= max_;
    }

    std::string message() const override
    {
        return
            "Out of range.";
    }

private:

    T min_;
    T max_;
};
