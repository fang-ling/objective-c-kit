// swift-tools-version: 6.2

//
//  Package.swift
//  objective-c-kit
//
//  Created by Fang Ling on 2026/4/12.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

import PackageDescription

let dependencies = [
  ("https://github.com/fang-ling/swift-closure.git", "snapshot")
]

let package = Package(
  name: "objective-c-kit",
  products: [
    .library(name: "ObjectiveCKit", targets: ["ObjectiveCKit"])
  ],
  dependencies: dependencies.map({ .package(url: $0.0, branch: $0.1) }),
  targets: [
    .target(
      name: "ObjectiveCKit",
      dependencies: [
        .product(name: "CClosure", package: "swift-closure")
      ],
      publicHeadersPath: "Includes",
      cSettings: [.unsafeFlags(["-fobjc-runtime=objfw-1.5", "-fno-objc-arc"])]
    ),
    .executableTarget(
      name: "ObjectiveCKitExample",
      dependencies: ["ObjectiveCKit"],
      cSettings: [.unsafeFlags(["-fobjc-runtime=objfw-1.5", "-fobjc-arc"])],
      linkerSettings: [
        .unsafeFlags(
          [
            "-Xlinker", "--allow-undefined",
            "-Xclang-linker", "-mexec-model=reactor",
            "-Xlinker", "--export=main"
          ],
          .when(platforms: [.wasi])
        )
      ]
    )
  ]
)
