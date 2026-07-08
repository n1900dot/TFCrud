# TFCrud  Generic Terminal CRUD Framework (c++)

> ⚠️ **Warning**: This project is undergoing major updates and is not ready for production use.

A modern C++ framework for building terminal-based CRUD (Create, Read, Update, Delete) applications with a clean architecture and flexible data storage options.

## Features

- **Terminal UI**: Built with [FTXUI](https://github.com/ArthurSonzogni/FTXUI) for responsive terminal interfaces
- **Multiple Storage Backends**:
  - CSV file storage
  - JSON file storage
  - SQLite database storage
  - In-memory repository
- **Command Pattern**: Full undo/redo support via command manager
- **Metadata System**: Reflection-based field metadata for automatic form generation
- **Validation**: Built-in validators (required fields, range validation)
- **Search & Filter**: Real-time search functionality
- **Pagination**: Efficient handling of large datasets
- **Sorting & Filtering**: Advanced data manipulation capabilities
- **Event Bus**: Observable pattern for decoupled components

## Project Structure

```
TFCrud/
├── Application/      # Application configuration and setup
├── actions/          # Action classes for user interactions
├── commands/         # Command pattern implementation (CRUD operations)
├── core/             # Core utilities (Result, EventBus, Observable, etc.)
├── data/             # Data layer (repositories, CSV parser/serializer)
├── dialogs/          # Dialog components (FormDialog, MessageDialog, etc.)
├── metadata/         # Reflection and metadata system
├── model/            # Data models (ViewModel, FilterModel, SortModel, etc.)
├── storage/          # Storage abstractions (IRepository implementations)
├── ui/               # UI components (CrudScreen, MenuBar, Toolbar, etc.)
└── widgets/          # Reusable widget components
```

## Architecture

### Repository Pattern
The framework uses the repository pattern for data access:
- `IRepository<T>`: Interface for all repository implementations
- `MemoryRepository<T>`: In-memory storage
- `CsvRepository<T>`: CSV file-based storage
- `JsonRepository<T>`: JSON file-based storage
- `SqliteRepository<T>`: SQLite database storage

### Command Pattern
All CRUD operations are wrapped in commands supporting undo/redo:
- `CreateCommand`: Create new records
- `UpdateCommand`: Modify existing records
- `DeleteCommand`: Remove records
- `ImportCommand`: Import data from external sources
- `ExportCommand`: Export data to external formats

### Metadata System
Automatic form generation and validation through metadata:
- Field information (name, type, visibility, editability)
- Validators (required, range)
- Property reflection

## Key Components

### CrudScreen
Main UI component providing:
- Search bar with real-time filtering
- Paginated table view
- Keyboard shortcuts for all operations
- Focus management between components

### FormDialog
Dynamic form generation based on entity metadata with validation support.

### CommandManager
Manages command execution with full undo/redo history.

## Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `TAB` | Switch focus between components |
| `/` | Focus search bar |
| `ESC` | Return to table view |
| `↑/↓` | Navigate rows |
| `PgUp/PgDn` | Navigate pages |
| `D` | Delete selected record |
| `Q` | Quit application |
| `F2` | New record |
| `F3` | Edit record |
| `F4` | Delete record |
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |

## Usage Example

```cpp
#include "CrudScreen.hpp"
#include "CsvRepository.hpp"
#include <ftxui/component/screen_interactive.hpp>

// Define your entity
struct Person {
    std::string name;
    int age;
    std::string email;
};

int main() {
    using namespace ftxui;
    
    // Create repository
    CsvRepository<Person> repo;
    repo.load("people.csv");
    
    // Setup screen
    auto screen = ScreenInteractive::Fullscreen();
    
    // Create CRUD screen
    auto crud_screen = std::make_shared<CrudScreen<Person>>(screen, repo);
    
    // Run application
    screen.Loop(crud_screen->component());
    
    return 0;
}
```

## Dependencies

- **FTXUI**: Functional Terminal User Interface library
- **C++17** or later (for template features and structured bindings)

## Building

```bash
# Clone the repository
git clone <repository-url>
cd TFCrud

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run
./your_application
```

## Extending the Framework

### Custom Repository
```cpp
template<typename T>
class CustomRepository : public IRepository<T> {
    // Implement repository interface
};
```

### Custom Validator
```cpp
class CustomValidator : public Validator {
public:
    bool validate(const FieldInfo& field, const std::any& value) override {
        // Custom validation logic
    }
};
```

### Custom Action
```cpp
class CustomAction : public Action {
public:
    std::string text() const override { return "Custom Action"; }
    void execute() override { /* Action logic */ }
};
```

## License

MIT License - See [LICENSE](LICENSE) for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Acknowledgments

- [FTXUI](https://github.com/ArthurSonzogni/FTXUI) - Terminal UI library
