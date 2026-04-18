/*
 *  OFBlock.h
 *  objective-c-kit
 *
 *  Derived from ObjFW by Fang Ling on 2026/4/18.
 *
 *  Copyright (c) 2008-2026 Jonathan Schleifer <js@nil.im>
 *
 *  All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License version 3.0 only,
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 *  version 3.0 for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  version 3.0 along with this program. If not, see
 *  <https://www.gnu.org/licenses/>.
 */

#ifndef __APPLE__

#import "OFObject.h"

OF_ASSUME_NONNULL_BEGIN

/**
 * @class OFBlock OFBlock.h ObjFW/ObjFW.h
 *
 * @brief The class for all blocks, since all blocks are also objects.
 */
@interface OFBlock: OFObject
+ (instancetype)alloc OF_UNAVAILABLE;
- (instancetype)init OF_UNAVAILABLE;
@end

OF_SUBCLASSING_RESTRICTED
@interface OFStackBlock: OFBlock
@end

OF_SUBCLASSING_RESTRICTED
@interface OFGlobalBlock: OFBlock
@end

OF_SUBCLASSING_RESTRICTED
@interface OFMallocBlock: OFBlock
@end

#ifdef __cplusplus
extern "C" {
#endif
extern void *_Nullable _Block_copy(const void *_Nullable);
extern void _Block_release(const void *_Nullable);

#ifdef __cplusplus
}
#endif

#ifndef Block_copy
# define Block_copy(...) \
    ((__typeof__(__VA_ARGS__))_Block_copy((const void *)(__VA_ARGS__)))
#endif
#ifndef Block_release
# define Block_release(...) _Block_release((const void *)(__VA_ARGS__))
#endif

OF_ASSUME_NONNULL_END

#endif /* !__APPLE__ */
