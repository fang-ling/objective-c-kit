/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsSize.c
 *  core-graphics-kit
 *
 *  Created by Fang Ling on 2026/8/2.
 *
 *  This source file is part of the CoreGraphicsKit open source project
 *
 *  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
 *  Licensed under Apache License v2.0
 *
 *  See LICENSE for license information
 *
 *  SPDX-License-Identifier: Apache-2.0
 *
 *===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#include "CoreGraphicsSize.h"

C_ASSUME_NONNULL_BEGIN

CBoolean CoreGraphicsSizeIsEqual(CoreGraphicsSize s1, CoreGraphicsSize s2) {
  return s1.width == s2.width && s1.height == s2.height;
}

C_ASSUME_NONNULL_END
