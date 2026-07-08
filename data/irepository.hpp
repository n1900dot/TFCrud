template<typename T>
class IRepository
{
public:

    virtual ~IRepository() = default;

    virtual size_t size() const = 0;

    virtual const T& at(size_t index) const = 0;

    virtual T& at(size_t index) = 0;

    virtual void append(const T&) = 0;

    virtual void insert(size_t,const T&) = 0;

    virtual void update(size_t,const T&) = 0;

    virtual void erase(size_t) = 0;

    virtual void clear() = 0;
};
