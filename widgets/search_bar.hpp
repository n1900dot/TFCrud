template<typename T>
class SearchBar :
public Widget
{
public:

    SearchBar(
        ViewModel<T>& view);

    Component component() override;

private:

    ViewModel<T>& view_;
};
