template<typename T>
class RequiredValidator :
    public Validator<T>
{
public:

    bool validate(
        const T& value) const override
    {
        return !value.empty();
    }

    std::string message() const override
    {
        return "Required field.";
    }
};
