// Copyright 2017 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#include "nativeui/gfx/image.h"

#include "base/files/file_path.h"
#include "base/strings/pattern.h"
#include "base/strings/string_util.h"

namespace nu {

namespace {

struct ScaleFactorPair {
  const base::FilePath::CharType* name;
  float scale;
};

ScaleFactorPair kScaleFactorPairs[] = {
  // The "@2x" is put as the first one to make scale matching faster.
  { FILE_PATH_LITERAL("@2x")    , 2.0f },
  { FILE_PATH_LITERAL("@3x")    , 3.0f },
  { FILE_PATH_LITERAL("@1x")    , 1.0f },
  { FILE_PATH_LITERAL("@4x")    , 4.0f },
  { FILE_PATH_LITERAL("@5x")    , 5.0f },
  { FILE_PATH_LITERAL("@1.25x") , 1.25f },
  { FILE_PATH_LITERAL("@1.33x") , 1.33f },
  { FILE_PATH_LITERAL("@1.4x")  , 1.4f },
  { FILE_PATH_LITERAL("@1.5x")  , 1.5f },
  { FILE_PATH_LITERAL("@1.8x")  , 1.8f },
  { FILE_PATH_LITERAL("@2.5x")  , 2.5f },
};

}  // namespace

// static
float Image::GetScaleFactorFromFilePath(const FilePath& path) {
  FilePath filename(base::FilePath(path).BaseName().RemoveExtension().value());
  if (!base::MatchPattern(filename, FILE_PATH_LITERAL("*@*x")))
    return 1.0f;

  // We don't try to convert string to float here because it is very very
  // expensive.
  for (const auto& p : kScaleFactorPairs) {
    if (base::EndsWith(filename, p.name, base::CompareCase::INSENSITIVE_ASCII))
      return p.scale;
  }

  return 1.0f;
}

}  // namespace nu
