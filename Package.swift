// swift-tools-version: 6.2

//
//  Package.swift
//  objective-c-kit
//
//  Created by Fang Ling on 2026/4/12.
//
//  This program is free software: you can redistribute it and/or modify it
//  under the terms of the GNU Lesser General Public License version 3.0 only,
//  as published by the Free Software Foundation.
//
//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
//  version 3.0 for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  version 3.0 along with this program. If not, see
//  <https://www.gnu.org/licenses/>.
//

import PackageDescription

let package = Package(
  name: "objective-c-kit",
  products: [
    .library(name: "ObjectiveCKit", targets: ["ObjectiveCKit"])
  ],
  targets: [
    .target(
      name: "ObjectiveCKit",
      exclude: [
        "ObjFW/lookup-asm/lookup-asm-amd64-elf.S",
        "ObjFW/lookup-asm/lookup-asm-arm64-elf.S",
        "ObjFW/platform/POSIX/OFPlainMutex.m",
        "ObjFW/OFPlainMutex.m",
        "ObjFW/OFOnce.m"
      ],
      publicHeadersPath: "Includes",
      cSettings: [
        .unsafeFlags(["-fobjc-runtime=objfw-1.5"], .when(platforms: [.wasi])),
        .headerSearchPath("ObjFW"),
        .headerSearchPath("ObjFW/runtime")
      ]
    )
  ]
)
