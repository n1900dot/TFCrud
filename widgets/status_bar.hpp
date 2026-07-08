template<typename T>
class StatusBar :
public Widget
{
public:

    StatusBar(
        ViewModel<T>& view);

    Component component() override;
};
