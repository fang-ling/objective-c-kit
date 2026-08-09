/*===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsRectangle.h
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

#ifndef CoreGraphicsRectangle_h
#define CoreGraphicsRectangle_h

#include <CKit/CKit.h>

#include "CoreGraphicsPoint.h"
#include "CoreGraphicsSize.h"

C_ASSUME_NONNULL_BEGIN

/**
 * A rectangle.
 *
 * ## Topics
 *
 * ### Geometric Properties
 *
 * - ``origin``
 * - ``size``
 *
 * ### Comparing Rectangles
 *
 * - ``CoreGraphicsRectangleIsEqual``
 */
typedef struct CoreGraphicsRectangle {
  /**
   * The rectangle's origin point.
   */
  CoreGraphicsPoint origin;

  /**
   * The size of the rectangle.
   */
  CoreGraphicsSize size;
} CoreGraphicsRectangle;

/**
 * Returns whether two rectangles are equal.
 *
 * - Parameters:
 *  - r1: The first source rectangle.
 *  - r2: The second source rectangle.
 *
 * - Returns: Returns a Boolean value indicating whether two rectangles are equal.
 */
CBoolean CoreGraphicsRectangleIsEqual(CoreGraphicsRectangle r1, CoreGraphicsRectangle r2);

C_ASSUME_NONNULL_END

#endif /* CoreGraphicsRectangle_h */
