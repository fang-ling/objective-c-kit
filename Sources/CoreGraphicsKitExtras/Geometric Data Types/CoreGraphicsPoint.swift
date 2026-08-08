//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  CoreGraphicsPoint.swift
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

extension CoreGraphicsPoint: @retroactive Swift::Equatable {
  public static func == (lhs: Self, rhs: Self) -> CBoolean {
    return CoreGraphicsPointIsEqual(lhs, rhs)
  }
}
