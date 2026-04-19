#!/bin/zsh

##
##  preview-documentation.zsh
##  objective-c-kit
##
##  Created by Fang Ling on 2026/4/19.
##
##  This program is free software: you can redistribute it and/or modify it
##  under the terms of the GNU Lesser General Public License version 3.0 only,
##  as published by the Free Software Foundation.
##
##  This program is distributed in the hope that it will be useful, but WITHOUT
##  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
##  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
##  version 3.0 for more details.
##
##  You should have received a copy of the GNU Lesser General Public License
##  version 3.0 along with this program. If not, see
##  <https://www.gnu.org/licenses/>.
##

FRAMEWORK_NAME="ObjectiveCKit"
SYMBOLS_FOLDER=".build/symbol-graphs"

# Extract the symbols
clang \
  -extract-api \
  --product-name=$FRAMEWORK_NAME \
  -o .build/symbol-graphs/$FRAMEWORK_NAME.symbols.json \
  -x objective-c-header Sources/$FRAMEWORK_NAME/*.h \
  -I . \
  -isysroot $(xcrun --show-sdk-path) \
  -F $(xcrun --show-sdk-path)/System/Library/Frameworks

# Preview the documentation
$(xcrun --find docc) \
  preview \
  Sources/$FRAMEWORK_NAME/Documentation.docc \
  -o .build/.docc-build \
  --additional-symbol-graph-dir .build/symbol-graphs
