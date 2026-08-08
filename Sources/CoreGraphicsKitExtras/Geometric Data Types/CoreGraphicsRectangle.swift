//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  CoreGraphicsRectangle.swift
//  core-graphics-kit
//
//  Created by Fang Ling on 2026/8/8.
//
//  This source file is part of the CoreGraphicsKit open source project
//
//  Copyright (c) 2026 Fang Ling <fangling@fangl.ing>
//  Licensed under Apache License v2.0
//
//  See LICENSE for license information
//
//  SPDX-License-Identifier: Apache-2.0
//
//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//

import CKit
import CoreGraphicsKitEssentials

extension CoreGraphicsRectangle {
  /// Creates a rectangle with the specified coordinate and size values.
  ///
  /// - Parameters:
  ///   - x: The x-coordinate of the rectangle's origin point.
  ///   - y: The y-coordinate of the rectangle's origin point.
  ///   - width: The width of the rectangle.
  ///   - height: The height of the rectangle.
  public init(x: CFloatingPoint64, y: CFloatingPoint64, width: CFloatingPoint64, height: CFloatingPoint64) {
    self.init(origin: CoreGraphicsPoint(x: x, y: y), size: CoreGraphicsSize(width: width, height: height))
  }
}

extension CoreGraphicsRectangle: @retroactive Swift::Equatable {
  public static func == (lhs: Self, rhs: Self) -> CBoolean {
    return CoreGraphicsRectangleIsEqual(lhs, rhs)
  }
}
