namespace ft
{

    struct ApplicationConfig
    {
        std::string title = "FTCRUD";

        size_t pageSize = 30;

        bool autoSave = true;

        bool confirmDelete = true;

        bool enableSearch = true;

        bool enableUndo = true;

        bool enableToolbar = true;

        bool enableStatusBar = true;
    };

}
