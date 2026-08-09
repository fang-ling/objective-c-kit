//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  CoreGraphicsRectangleTests.swift
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

import Testing

@testable import CoreGraphicsKit

@Suite("CoreGraphicsRectangleTests")
struct CoreGraphicsRectangleTests {
  @Test func testEquatableConformance() {
    let r1 = CoreGraphicsRectangle(x: 36, y: 48, width: 360, height: 480)
    let r2 = CoreGraphicsRectangle(x: 36, y: 58, width: 360, height: 580)
    #expect(r1 == r1)
    #expect(r1 != r2)
  }
}
