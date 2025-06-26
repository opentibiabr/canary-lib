#!/usr/bin/env bash

# Usage:
#   ./add-version.sh kapuera resenha anotherlib
# Assumes:
# - You are inside your `canary-lib` repo
# - Overlay ports live in ./ports
# - Local vcpkg clone is in ~/vcpkg
# - Your registry is in ./versions/<first-letter>/<libname>

set -euo pipefail

OVERLAY_DIR="ports"
VCPKG_DIR="$HOME/vcpkg"
VCPKG_BIN="$VCPKG_DIR/vcpkg"

if [ $# -eq 0 ]; then
  echo "❌ Usage: $0 <libname> [<libname> ...]"
  exit 1
fi

for LIBNAME in "$@"; do
  echo "🔧 Processing '$LIBNAME'..."

  # 1. Check port exists
  if [ ! -d "$OVERLAY_DIR/$LIBNAME" ]; then
    echo "❌ Error: Port '$LIBNAME' not found in '$OVERLAY_DIR'"
    continue
  fi

  # 2. Copy port into vcpkg's ports dir
  TMP_PORT_DIR="$VCPKG_DIR/ports/$LIBNAME"
  rm -rf "$TMP_PORT_DIR"
  cp -r "$OVERLAY_DIR/$LIBNAME" "$TMP_PORT_DIR"

  # 3. Add version metadata
  if ! VCPKG_FEATURE_FLAGS=versions "$VCPKG_BIN" x-add-version "$LIBNAME" \
      --vcpkg-root="$VCPKG_DIR" --overwrite-version 2>/dev/null; then
    echo "⚠️  Failed to add version for '$LIBNAME'"
    rm -rf "$TMP_PORT_DIR"
    continue
  fi

  # 4. Move metadata
  VERSION_FILE="$VCPKG_DIR/versions/${LIBNAME:0:1}-/$LIBNAME.json"
  LOCAL_REGISTRY_DIR="versions/${LIBNAME:0:1}-"
  mkdir -p "$LOCAL_REGISTRY_DIR"
  mv "$VERSION_FILE" "$LOCAL_REGISTRY_DIR/" || echo "⚠️  Could not move version file for '$LIBNAME'"

  # 5. Clean up
  rm -rf "$TMP_PORT_DIR"

  echo "✅ '$LIBNAME' processed successfully"
done
