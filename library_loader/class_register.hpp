/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include "library_manifest.hpp"
#include "log.hpp"

extern "C" LibraryManifest *getLibraryManifest();

#define BEGIN_MANIFEST()                    \
    LibraryManifest *getLibraryManifest() { \
        LibraryManifest *manifest_ = new LibraryManifest();

#define EXPORT_CLASS(BaseClass, DerivedClass) \
    manifest_->RegisterClass<BaseClass, DerivedClass>(#DerivedClass);

#define END_MANIFEST() \
    return manifest_;  \
    }