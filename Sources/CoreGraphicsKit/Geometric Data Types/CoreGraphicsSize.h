/*===--------------------------------------------------------------------------------------------------------------------------------------------------------------------------===*
 *
 *  CoreGraphicsSize.h
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

#ifndef CoreGraphicsSize_h
#define CoreGraphicsSize_h

#include <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A structure that contains width and height values.
 *
 * A ``CoreGraphicsSize`` structure is sometimes used to represent a distance vector, rather than a physical size. As a vector, its values can be negative. To normalize a
 * ``CoreGraphicsRectangle`` structure so that its size is represented by positive values, call the ``standardized`` function.
 *
 * ## Topics
 *
 * ### Geometric Properties
 *
 * - ``width``
 * - ``height``
 */
typedef struct CoreGraphicsSize {
  /**
   * A width value.
   */
  CFloatingPoint64 width;

  /**
   * A height value.
   */
  CFloatingPoint64 height;
} CoreGraphicsSize;

C_ASSUME_NONNULL_END

#endif /* CoreGraphicsSize_h */
