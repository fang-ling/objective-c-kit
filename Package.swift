// swift-tools-version: 6.3

//===----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------===//
//
//  Package.swift
//  core-graphics-kit
//
//  Created by Fang Ling on 2026/4/12.
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

import PackageDescription

let isDevelopment = false

let dependencies = [
  ("c-kit", "CKit", "main")
]

let package = Package(
  name: "core-graphics-kit",
  products: [
    .library(name: "CoreGraphicsKit", targets: ["CoreGraphicsKit"])
  ],
  dependencies: dependencies.map{ isDevelopment ? .package(path: "../\($0.0)") : .package(url: "https://github.com/fang-ling/\($0.0)", branch: $0.2) },
  targets: [
    .target(
      name: "CoreGraphicsKit",
      dependencies: ["CoreGraphicsKitEssentials", "CoreGraphicsKitExtras"]
    ),
    .target(
      name: "CoreGraphicsKitEssentials",
      dependencies: dependencies.map { .product(name: $0.1, package: $0.0) },
      publicHeadersPath: "Includes"
    )
  ]
)
