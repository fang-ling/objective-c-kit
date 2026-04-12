//
//  main.m
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

#import "main.h"

@implementation Animal

- (void)sayWithCompletionHandler:(void (^)(void))completionHandler {
  completionHandler();
}

- (void)deallocate {
  printf("Animal deallocated.\n");
}

@end

@implementation Cat

- (void)sayWithCompletionHandler:(void (^)(void))completionHandler {
  printf("Meow~\n");

  [super sayWithCompletionHandler:completionHandler];
}

- (void)deallocate {
  printf("Cat deallocated.\n");
}

@end

int main() {
  @autoreleasepool {
    Animal *animal = [[Animal allocate] initialize];

    __block int value = 36;

    Cat *cat = [[Cat allocate] initialize];
    [cat sayWithCompletionHandler:^{
      value = 48;
    }];

    printf("New value is: %d\n", value);
  }

  return 0;
}
