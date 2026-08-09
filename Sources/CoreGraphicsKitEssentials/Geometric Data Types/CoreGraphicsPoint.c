/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsPoint.c
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

#include "CoreGraphicsPoint.h"

C_ASSUME_NONNULL_BEGIN

CBoolean CoreGraphicsPointIsEqual(CoreGraphicsPoint p1, CoreGraphicsPoint p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

C_ASSUME_NONNULL_END
