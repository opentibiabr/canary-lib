# Canary Lib

An opensource pack of tibia-inspired libraries for building MMORPGs.
This repository is also a private vcpkg registry, which can be used to install the libraries in your projects.

## Structure

The library is split in a few parts:

* `cmake`: CMake modules/macros for building the library and its dependencies.
* `libs`: The source code of the actual libraries.
* `ports`: Vcpkg ports for the libraries, which can be used to install them in your projects.
* `test-project`: An example on how to use the libraries in a vcpkg project.
* `versions`: Auto generated versions of the libraries, which can be used to check for updates.

## Usage

To use the libraries in your project, you can add the repository to your `vcpkg-configuration.json`:
```json
{
  "registries": [
    {
      "kind": "git",
      "repository": "https://github.com/opentibiabr/canary-lib.git",
      "baseline": "f914a86ee99cda914709287b531d147b1415a8af", // latest commit hash
      "packages": ["kapuera", "resenha", "retalho"]
    }
  ],
  "default-registry": {
    "kind": "builtin",
    "baseline": "417119555f155f6044dec7a379cd25466e339873"
  }
}
```

Add the relevant libraries to your `CMakeLists.txt`:
```cmake
find_package(kapuera CONFIG REQUIRED)
target_link_libraries(main PRIVATE kapuera::kapuera)
```

Then you can install the libraries using vcpkg, normally:
```bash
vcpkg install
```

## Updating Versions

Everytime you update the libraries, you should update the `versions` folder with the new versions of the libraries.

Before doing that, make sure that the `portfile.cmake` of your libraries points to the last relevant commit/tag in the repository.
This is important to ensure that the versioning works correctly.

You also need to update the `SHA512` of the content.
You can do this by running the following command in the root of the repository:
```bash
curl -L https://github.com/opentibiabr/canary-lib/archive/${YOUR_COMMIT_OR_TAG}.tar.gz -o source.tar.gz
vcpkg hash source.tar.gz
```

Once you do that, you must update `porfile.cmake`:
```cmake
vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO opentibiabr/canary-lib
        REF ${YOUR_COMMIT_OR_TAG}
        SHA512 ${HASH_RESULT}
        HEAD_REF main
        SOURCE_SUBPATH libs/kapuera
)
```

You can then commit the new portfiles, which will point the vcpkg ports to the new version of the libraries.

After that, you just need to update the versions.
That can be done via vcpkg:
```bash
./add-version.sh kapuera resenha retalho
```

Replace `$LIBNAME` with the name of the library you want to update (e.g., `kapuera`, `resenha`, etc.).
You must do that to all libraries that you want to update.

Commiting the versions will point the vcpkg repo to this version from this commit on.
In your repository you can then update the `baseline` in the `vcpkg-configuration.json` to the new commit hash.

## Development

In development mode we don't want to publish everything all the time, or release new versions of the library.
To locally point to the libraries, you can use the `vcpkg.json` `overlay-ports` feature:
```cmake
vcpkg install --overlay-ports=/path/to/canary-lib/ports
```