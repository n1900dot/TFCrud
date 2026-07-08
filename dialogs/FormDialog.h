template<typename T>
class FormDialog :
public Dialog
{
public:

    FormDialog(
        ScreenInteractive& screen);

    void
    edit(T&);

    bool
    accepted() const;

private:

    FormGenerator<T> form_;

    bool accepted_ = false;
};
