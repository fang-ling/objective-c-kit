/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsRectangle.c
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

#include "CoreGraphicsRectangle.h"

C_ASSUME_NONNULL_BEGIN

CBoolean CoreGraphicsRectangleIsEqual(CoreGraphicsRectangle r1, CoreGraphicsRectangle r2) {
  return CoreGraphicsPointIsEqual(r1.origin, r2.origin) && CoreGraphicsSizeIsEqual(r1.size, r2.size);
}

C_ASSUME_NONNULL_END
