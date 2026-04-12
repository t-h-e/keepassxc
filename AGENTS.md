# KeePassXC Agent Guidelines

## Build Commands

### Configure and Build
```bash
# Linux/macOS
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j$(nproc)

# Windows (PowerShell)
cmake --preset x64-debug
cmake --build --preset x64-debug

# With all features enabled
cmake -S . -B build -DWITH_XC_ALL=ON
```

### Code Formatting (REQUIRED before commits)
```bash
cmake --build build --target format
```

### Testing
```bash
# Run all tests
ctest --test-dir build -j$(nproc)

# Run single test (verbose)
ctest --test-dir build -R <TestName> -V

# Run specific test executable directly
./build/tests/test<Name>

# GUI tests (requires -DWITH_GUI_TESTS=ON)
ctest --test-dir build -R testgui -V
```

### Translations (before releases)
```bash
python ./release-tool.py i18n lupdate
```

## Code Style

### General Conventions
- **Language**: C++20 (C++17 if not using Botan3)
- **Indentation**: 4 spaces, no tabs
- **Column limit**: 120 characters
- **Brace style**: Custom - attach opening brace after function/class/enum/namespace/struct
- **Pointer alignment**: Left (`QString* ptr`, `const QString& ref`)
- **Namespace indentation**: Enabled

### Includes
- Sorted alphabetically
- Qt headers: `<QClassName>`
- STL headers: `<vector>`, `<memory>`
- Project headers: `"core/Database.h"` (double quotes)
- Order: related header, Qt headers, STL, project headers

### Naming Conventions
- **Classes**: PascalCase (`DatabaseWidget`, `RemoteHandler`)
- **Functions/Methods**: camelCase (`syncWithRemote()`, `downloadDatabase()`)
- **Variables**: camelCase (`filePath`, `remoteParams`)
- **Member variables**: `m_` prefix (`m_db`, `m_remoteSettings`)
- **Constants**: UPPER_SNAKE_CASE or camelCase for static const
- **Signals**: camelCase, past tense for events (`databaseSyncCompleted`)
- **Slots**: `on<SignalName>` pattern preferred
- **Structs**: PascalCase for struct name, fields are camelCase

### Qt Specifics
- Use Qt signal/slot mechanism extensively
- Prefer Qt containers over STL where Qt integration is needed
- Use `QScopedPointer`, `QSharedPointer` for memory management
- `Q_DISABLE_COPY(Class)` macro to prevent copying
- `Q_DECLARE_METATYPE` for custom types used in QVariant
- Mark QObject-derived classes with `Q_OBJECT` macro

## Project Structure

### Core Directories
- `src/core/`: Core data model (Database, Group, Entry)
- `src/format/`: KDBX readers/writers - SECURITY SENSITIVE
- `src/crypto/`: Cryptographic primitives - SECURITY SENSITIVE
- `src/gui/`: Qt UI layer
- `tests/`: QTest-based unit tests
- `tests/gui/`: GUI tests
- `tests/mock/`: Mock objects for testing

### Key Patterns
- Signal connections: See `src/keeshare/ShareObserver.cpp`
- Database lifecycle: `src/gui/DatabaseTabWidget.*`, `src/gui/DatabaseWidget.*`
- Error handling: `src/format/KdbxReader.cpp`

## Remote Sync Feature

### Architecture Overview
The remote sync feature allows syncing databases with remote storage via custom commands.

**Key Components:**
- `src/gui/remote/RemoteHandler.h/cpp`: Orchestrates download/upload operations
- `src/gui/remote/RemoteProcess.h/cpp`: Abstraction for executing shell commands
- `src/gui/remote/RemoteSettings.h/cpp`: Manages remote configuration per database
- `src/gui/remote/DatabaseSettingsWidgetRemote.h/cpp`: UI for remote settings
- `tests/mock/MockRemoteProcess.h/cpp`: Test mock for remote process

### RemoteParams Structure
```cpp
struct RemoteParams {
    QString name;              // Display name for this remote
    QString downloadCommand;   // Command to download database
    QString downloadInput;     // Stdin for download command
    int downloadTimeoutMsec;   // Download timeout (default: 10000)
    QString uploadCommand;     // Command to upload database
    QString uploadInput;       // Stdin for upload command
    int uploadTimeoutMsec;     // Upload timeout (default: 10000)
};
```

### Template Variables
Commands support `{TEMP_DATABASE}` which resolves to a temporary file path.

### RemoteHandler Usage
```cpp
RemoteHandler handler;
auto result = handler.download(remoteParams);
if (result.success) {
    // result.filePath contains downloaded database path
}
auto uploadResult = handler.upload(localPath, remoteParams);
```

### Testing Remote Components
```cpp
// Set mock process factory before testing
RemoteHandler::setRemoteProcessFunc([](QObject* parent) {
    return QScopedPointer<RemoteProcess>(
        new MockRemoteProcess(parent, testDataPath));
});

// Use QSignalSpy to verify signals
QSignalSpy spy(dbWidget, &DatabaseWidget::databaseSyncCompleted);
```

### GUI Test Patterns
```cpp
void TestGui::testRemoteSyncDatabaseSameKey()
{
    RemoteHandler::setRemoteProcessFunc([](QObject* parent) {
        return QScopedPointer<RemoteProcess>(
            new MockRemoteProcess(parent, testDataPath));
    });
    QSignalSpy dbSyncSpy(m_dbWidget, &DatabaseWidget::databaseSyncCompleted);
    prepareAndTriggerRemoteSync();
    QTRY_COMPARE(dbSyncSpy.count(), 1);
}
```

## Rules for Agents

1. **Security**: Do NOT modify `src/crypto` or `src/format` without explicit request and narrow scope. Always run tests after changes.

2. **Testing**: Create relevant unit tests in `tests/` for new features. All tests must pass before committing.

3. **Formatting**: Always run `cmake --build build --target format` before commits.

4. **Translations**: Run `python ./release-tool.py i18n lupdate` before commits if UI strings changed.

5. **References**: Include file paths in PR/commit descriptions (e.g., "changed src/gui/remote/RemoteHandler.cpp").

6. **Async Operations**: Use `AsyncTask::runAndWaitForFuture()` for blocking async operations (see `RemoteHandler.cpp`).

7. **Mocking**: Use `tests/mock/MockRemoteProcess.h` for testing remote functionality without actual network calls.

8. **Error Handling**: Return `RemoteResult` struct with `success`, `errorMessage`, `filePath` for remote operations.
