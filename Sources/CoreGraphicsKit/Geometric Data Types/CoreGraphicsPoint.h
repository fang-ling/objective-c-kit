/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsPoint.h
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
 *===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*/

#ifndef CoreGraphicsPoint_h
#define CoreGraphicsPoint_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A point in a Cartesian coordinate system.
 *
 * ## Topics
 *
 * ### Geometric Properties
 *
 * - ``x``
 * - ``y``
 */
typedef struct CoreGraphicsPoint {
  /**
   * The x-coordinate value.
   */
  CFloatingPoint64 x;

  /**
   * The y-coordinate value.
   */
  CFloatingPoint64 y;
} CoreGraphicsPoint;

C_ASSUME_NONNULL_END

#endif /* CoreGraphicsPoint_h */
